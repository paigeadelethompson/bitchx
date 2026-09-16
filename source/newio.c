/*
 * newio.c: This is some handy stuff to deal with file descriptors in a way
 * much like stdio's FILE pointers
 *
 * IMPORTANT NOTE:  If you use the routines here-in, you shouldn't switch to
 * using normal reads() on the descriptors cause that will cause bad things
 * to happen.  If using any of these routines, use them all
 *
 * Copyright 1990 Michael Sandrof
 * Copyright 1995 Matthew Green
 * Copyright 1997 EPIC Software Labs
 * See the COPYRIGHT file, or do a HELP IRCII COPYRIGHT
 */

#include "irc.h"
static char cvsrevision[] = "$Id$";
CVS_REVISION(newio_c)
#include "ircaux.h"
#include "output.h"

#include <sys/ioctl.h>

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif
#ifdef WIN32
#endif

/*
 * Polling backends.  epoll on Linux and kqueue on the BSD/macOS family
 * replace select() to scale past FD_SETSIZE; everything else continues
 * to use the traditional select() path.
 */
#ifdef HAVE_SYS_EPOLL_H
#define BX_POLL_EPOLL
#endif
#ifdef HAVE_SYS_EVENT_H
#define BX_POLL_KQUEUE
#endif
#ifdef BX_POLL_EPOLL
#include <sys/epoll.h>
#endif
#ifdef BX_POLL_KQUEUE
#include <sys/event.h>
#endif

#define MAIN_SOURCE
#include "modval.h"

#if defined(HAVE_SYSCONF) && defined(_SC_OPEN_MAX) && !defined(__EMX__)
#define IO_ARRAYLEN sysconf(_SC_OPEN_MAX)
#else
#ifdef FD_SETSIZE
#define IO_ARRAYLEN FD_SETSIZE
#else
#define IO_ARRAYLEN NFDBITS
#endif
#endif

#ifdef __GNU__
#undef IO_ARRAYLEN
#define IO_ARRAYLEN 65535
#endif

#define MAX_SEGMENTS 16

typedef struct myio_struct {
  char *buffer;
  size_t buffer_size;
  unsigned read_pos, write_pos;
  int segments;
  int error;
} MyIO;

static MyIO **io_rec = NULL;
int dgets_errno = 0;

/*
 * Get_pending_bytes: What do you think it does?
 */
size_t get_pending_bytes(int fd) {
  if (fd >= 0 && io_rec[fd] && io_rec[fd]->buffer)
    return strlen(io_rec[fd]->buffer);

  return 0;
}

static void init_io(void) {
  static int first = 1;

  if (first) {
    int c, max_fd = IO_ARRAYLEN;

    io_rec = (MyIO **)new_malloc(sizeof(MyIO *) * max_fd);
    for (c = 0; c < max_fd; c++)
      io_rec[c] = (MyIO *)0;
    first = 0;
  }
}

#ifdef HAVE_LIBSSL
void SSL_show_errors(void) {
  char buf[1000];
  int sslerr;

  while ((sslerr = ERR_get_error())) {
    ERR_error_string(sslerr, buf);
    say("%s", buf);
  }
}
#endif

/* Wrapper around strerror() for dgets_errno.
 */
const char *dgets_strerror(int dgets_errno) {
  switch (dgets_errno) {
  case -1:
    return "Remote end closed connection";

  default:
    return strerror(dgets_errno);
  }
}

/*
 * All new dgets -- no more trap doors!
 *
 * There are at least four ways to look at this function.
 * The most important variable is 'buffer', which determines if
 * we force line buffering.  If it is on, then we will sit on any
 * incomplete lines until they get a newline.  This is the default
 * behavior for server connections, because they *must* be line
 * delineated.  However, when are getting input from an untrusted
 * source (eg, dcc chat, /exec'd process), we cannot assume that every
 * line will be newline delinated.  So in those cases, 'buffer' is 0,
 * and we force a flush on whatever we can slurp, without waiting for
 * a newline.
 *
 * Return values:
 *
 *	-1 -- something really died.  Either a read error occurred, the
 *	      fildesc wasn't really ready for reading, or the input buffer
 *	      for the filedesc filled up (8192 bytes)
 *	 0 -- If the data read in from the file descriptor did not form a
 *	      complete line, then zero is always returned.  This should be
 *	      considered a stopping condition.  Do not call dgets() again
 *	      after it returns 0, because unless more data is available on
 *	      the fd, it will return -1, which you would misinterpret as an
 *	      error condition.
 *	      If "buffer" is 0, then whatever we have available will be
 *	      returned in "str".
 *	      If "buffer" is not 0, then we will retain whatever we have
 *	      available, waiting for the newline to occur perhaps next time.
 *	>0 -- If a full, newline terminated line was available, the length
 *	      of the line is returned.
 */
int BX_dgets(char *str, int des, int buffer, int buffersize, void *ssl_fd) {
  int cnt = 0, c;
  MyIO *ioe;
  int nbytes;

  if (!io_rec)
    init_io();

  ioe = io_rec[des];

  if (ioe == NULL) {
    ioe = io_rec[des] = (MyIO *)new_malloc(sizeof(MyIO));
    ioe->buffer_size = IO_BUFFER_SIZE;
    ioe->buffer = (char *)new_malloc(ioe->buffer_size + 2);
    ioe->read_pos = ioe->write_pos = 0;
  }

  if (ioe->read_pos == ioe->write_pos) {
    ioe->read_pos = ioe->write_pos = 0;
    ioe->buffer[0] = 0;
    ioe->segments = 0;
  }

  if (!strchr(ioe->buffer + ioe->read_pos, '\n')) {
    if (ioe->read_pos) {
      ov_strcpy(ioe->buffer, ioe->buffer + ioe->read_pos);
      ioe->read_pos = 0;
      ioe->write_pos = strlen(ioe->buffer);
      ioe->segments = 1;
    }

    /*
     * Don't try to read into a full buffer.
     */
    if (ioe->write_pos >= ioe->buffer_size) {
      yell("***XXX*** Buffer for des [%d] is filled!", des);
      dgets_errno = ENOMEM; /* Cough */
      return -1;
    }
    /*
     * Check to see if any bytes are ready.  If this fails,
     * then it's almost always due to the filedesc being
     * bogus.  That's a fatal error.
     */
    if (ioctl(des, FIONREAD, &nbytes) == -1) {
      *str = 0;
      dgets_errno = errno;
      return -1;
    }

    /*
     * Check for a quasi-EOF condition.  If we get to this
     * point, then new_select() indicated that this fd is ready.
     * The fd is ready if either:
     *	1) A newline is in the buffer
     *	2) select(2) returned ready for the fd.
     *
     * If 1) is true, then write_pos will not be zero.  So we can
     * use that as a cheap way to check for #1.  If #1 is false,
     * then #2 must have been true, and if nbytes is 0, then
     * that indicates an EOF condition.
     *
     * The "EOF" condition might actually be a socket error, so check
     * for that and return it to the caller.
     */
    else if (!nbytes && ioe->write_pos == 0) {
      int so_error;
      socklen_t len = sizeof so_error;

      *str = 0;
      if (getsockopt(des, SOL_SOCKET, SO_ERROR, &so_error, &len) == 0 &&
          so_error != 0)
        dgets_errno = so_error;
      else
        dgets_errno = -1;
      return -1;
    }

    else if (nbytes) {
#ifdef HAVE_LIBSSL
      int rc = 0;
#endif

      if (nbytes >= IO_BUFFER_SIZE)
        nbytes = IO_BUFFER_SIZE - 1;
#ifdef HAVE_LIBSSL
      if (ssl_fd) {
        c = SSL_read((SSL *)ssl_fd, ioe->buffer + ioe->write_pos,
                     ioe->buffer_size - ioe->write_pos);

        if (c == -1 &&
            (rc = SSL_get_error((SSL *)ssl_fd, c)) == SSL_ERROR_WANT_READ) {
          /* If SSL needs more data, then we need to call SSL_read again,
           * so we'll return with 0 bytes read, and hope we get called
           * again. :)
           */
          return 0;
        }
      } else
#endif
        c = read(des, ioe->buffer + ioe->write_pos,
                 ioe->buffer_size - ioe->write_pos);

      if (x_debug & DEBUG_INBOUND)
        yell("FD [%d], should [%d] did [%d]", des, nbytes, c);

      if (c <= 0) {
#ifdef HAVE_LIBSSL
        if (ssl_fd) {
          say("SSL_read() failed, SSL error %d", rc);
          SSL_show_errors();
        }
#endif
        *str = 0;
        dgets_errno = (c == 0) ? -1 : errno;
        return -1;
      }
      ioe->buffer[ioe->write_pos + c] = 0;
      ioe->write_pos += c;
      ioe->segments++;
    } else {
      /*
       * At this point nbytes is 0, and it doesn't
       * appear the socket is at EOF or ready to read.
       * Very little to do at this point but force the
       * issue and figure out what the heck went wrong.
       */
      struct timeval t = {0, 0};
      fd_set testing;

      FD_ZERO(&testing);
      FD_SET(des, &testing);
      switch (select(des + 1, &testing, NULL, NULL, &t)) {
      case -1: {
        yell("Aberrant condition for des [%d], closing down the connection out "
             "of desperation.",
             des);
        *str = 0;
        dgets_errno = errno;
        return -1;
      }
      case 0: {
        yell("des [%d] passed to dgets(), but it isn't ready.", des);
        if (ioe->write_pos == 0) {
          yell("X*X*X*X*X*X*X*X*X ABANDON SHIP! X*X*X*X*X*X*X*X*X*X");
          ircpanic("write_pos is zero when it can't be.");
        } else {
          yell("But something is buffered.  Flushing it to see if that helps.");
          ioe->buffer[ioe->write_pos++] = '\n';
          break;
        }
        break;
      }
      case 1: {
        errno = ECONNABORTED;
        *str = 0;
        dgets_errno = errno;
        return -1;
      }
      }
    }
  }

  dgets_errno = 0;

  /*
   * If the caller wants us to force line buffering, and if there
   * is no complete line, just stop right here.
   */
  if (buffer && !strchr(ioe->buffer + ioe->read_pos, '\n')) {
    if (ioe->segments > MAX_SEGMENTS) {
      yell("*** Too many read()s on des [%d] without a newline!", des);
      *str = 0;
      dgets_errno = ECONNABORTED;
      return -1;
    }
    return 0;
  }
  /*
   * Slurp up the data that is available into 'str'.
   */
  while (ioe->read_pos < ioe->write_pos && cnt < (buffersize - 1)) {
    if ((str[cnt++] = ioe->buffer[ioe->read_pos++]) == '\n')
      break;
  }

  /*
   * Terminate it
   */
  str[cnt] = 0;

  /*
   * If we end in a newline, then all is well.
   * Otherwise, we're unbuffered, tell the caller.
   * The caller then would need to do a strlen() to get
   * the amount of data.
   */
  if (cnt > 0 && str[cnt - 1] == '\n')
    return cnt - 1;
  else
    return 0;
}

static int global_max_fd = -1;

#if defined(BX_POLL_EPOLL) || defined(BX_POLL_KQUEUE)
#define MAX_POLL_EVENTS 256
static int io_poll_fd = -1;
static fd_set poll_reads, poll_writes;

/*
 * Lazily create the epoll/kqueue descriptor and reset our mirror of
 * what interest we have registered.
 */
static void io_poll_ensure(void) {
  if (io_poll_fd >= 0)
    return;

  FD_ZERO(&poll_reads);
  FD_ZERO(&poll_writes);

#ifdef BX_POLL_EPOLL
#ifdef EPOLL_CLOEXEC
  io_poll_fd = epoll_create1(EPOLL_CLOEXEC);
#endif
  if (io_poll_fd < 0)
    io_poll_fd = epoll_create(MAX_POLL_EVENTS);
#else
  io_poll_fd = kqueue();
#endif
}

/*
 * Bring the epoll/kqueue interest list in line with what the caller
 * wants for a single fd.  This is level-triggered on both backends, so
 * the semantics match select() exactly: an fd reports ready whenever it
 * is ready to read/write, not just on the next transition.
 */
static void io_poll_sync_one(int fd, int want_read, int want_write) {
  int have_read, have_write;

  if (fd < 0 || fd >= FD_SETSIZE)
    return;

  io_poll_ensure();
  if (io_poll_fd < 0)
    return;

  have_read = FD_ISSET(fd, &poll_reads) ? 1 : 0;
  have_write = FD_ISSET(fd, &poll_writes) ? 1 : 0;
  if (have_read == want_read && have_write == want_write)
    return;

#ifdef BX_POLL_EPOLL
  {
    struct epoll_event ev;

    memset(&ev, 0, sizeof(ev));
    ev.events = (want_read ? EPOLLIN : 0) | (want_write ? EPOLLOUT : 0) |
                EPOLLERR | EPOLLHUP;
    ev.data.fd = fd;

    if (!have_read && !have_write) {
      if (epoll_ctl(io_poll_fd, EPOLL_CTL_ADD, fd, &ev) == -1)
        return; /* closed, or not pollable */
    } else if (!want_read && !want_write) {
      if (epoll_ctl(io_poll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
        return;
    } else {
      if (epoll_ctl(io_poll_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
        return;
    }
  }
#else
  {
    struct kevent changes[2];
    int n = 0;

    if (want_read && !have_read)
      EV_SET(&changes[n++], fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    else if (!want_read && have_read)
      EV_SET(&changes[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    if (want_write && !have_write)
      EV_SET(&changes[n++], fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
    else if (!want_write && have_write)
      EV_SET(&changes[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);

    if (n && kevent(io_poll_fd, changes, n, NULL, 0, NULL) == -1)
      return;
  }
#endif

  if (want_read)
    FD_SET(fd, &poll_reads);
  else
    FD_CLR(fd, &poll_reads);
  if (want_write)
    FD_SET(fd, &poll_writes);
  else
    FD_CLR(fd, &poll_writes);
}

/*
 * Drop all interest for a freshly closed fd.
 */
static void io_poll_remove(int fd) {
  if (io_poll_fd < 0)
    return;
  io_poll_sync_one(fd, 0, 0);
}

/*
 * Wait for readiness, stamping the ready bits into *rd and *wd exactly
 * the way select() used to.
 */
static int io_poll_wait(fd_set *rd, fd_set *wd, const struct timeval *timeout) {
  int i, n, cnt = 0;

  io_poll_ensure();
  if (io_poll_fd < 0)
    return -1;

#ifdef BX_POLL_EPOLL
  {
    struct epoll_event events[MAX_POLL_EVENTS];
    int msec =
        timeout ? (timeout->tv_sec * 1000 + timeout->tv_usec / 1000) : -1;

    n = epoll_wait(io_poll_fd, events, MAX_POLL_EVENTS, msec);
    if (n < 0)
      return -1;

    for (i = 0; i < n; i++) {
      int fd = events[i].data.fd;
      u_32int_t flags = events[i].events;

      if (fd < 0 || fd >= FD_SETSIZE)
        continue;
      if ((flags & (EPOLLIN | EPOLLERR | EPOLLHUP)) && !FD_ISSET(fd, rd)) {
        FD_SET(fd, rd);
        cnt++;
      }
      if (wd && (flags & EPOLLOUT) && !FD_ISSET(fd, wd)) {
        FD_SET(fd, wd);
        cnt++;
      }
    }
  }
#else
  {
    struct kevent events[MAX_POLL_EVENTS];
    struct timespec ts, *tsp = NULL;

    if (timeout) {
      ts.tv_sec = timeout->tv_sec;
      ts.tv_nsec = timeout->tv_usec * 1000;
      tsp = &ts;
    }

    n = kevent(io_poll_fd, NULL, 0, events, MAX_POLL_EVENTS, tsp);
    if (n < 0)
      return -1;

    for (i = 0; i < n; i++) {
      int fd = events[i].ident;

      if (fd < 0 || fd >= FD_SETSIZE)
        continue;
      if (wd && events[i].filter == EVFILT_WRITE && !FD_ISSET(fd, wd)) {
        FD_SET(fd, wd);
        cnt++;
      }
      if (events[i].filter == EVFILT_READ && !FD_ISSET(fd, rd)) {
        FD_SET(fd, rd);
        cnt++;
      }
    }
  }
#endif
  return cnt;
}
#endif /* BX_POLL_EPOLL || BX_POLL_KQUEUE */

/*
 * new_select: works just like select(), execpt I trimmed out the excess
 * parameters I didn't need.
 */
int new_select(fd_set *rd, fd_set *wd, struct timeval *timeout) {
  int i, set = 0;
  fd_set new;
  struct timeval thetimeout;
  struct timeval *newtimeout = &thetimeout;

  if (timeout)
    thetimeout = *timeout;
  else
    newtimeout = NULL;

  if (!io_rec)
    ircpanic("new select called before io_rec init");
  if (newtimeout && newtimeout->tv_usec < 0)
    ircpanic("new select with < -1");

  FD_ZERO(&new);
  for (i = 0; i <= global_max_fd; i++) {
    if (io_rec[i]) {
      if ((io_rec[i]->read_pos < io_rec[i]->write_pos) &&
          strchr(io_rec[i]->buffer + io_rec[i]->read_pos, '\n')) {
        FD_SET(i, &new);
        set++;
      }
    }
  }

  if (set) {
    *rd = new;
    return set;
  }
#ifdef WIN32
  memset(&thetimeout, 0, sizeof(struct timeval));
  thetimeout.tv_usec = 500;
  i = select(global_max_fd + 1, rd, wd, NULL, &thetimeout);
  {
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return i;
#elif defined(BX_POLL_EPOLL) || defined(BX_POLL_KQUEUE)
  {
    int fd;

    /* Reconcile the interest list with what the caller wants. */
    for (fd = 0; fd < FD_SETSIZE; fd++)
      io_poll_sync_one(fd, FD_ISSET(fd, rd), (wd && FD_ISSET(fd, wd)) ? 1 : 0);

    return io_poll_wait(rd, wd, newtimeout);
  }
#else
  return (select(global_max_fd + 1, rd, wd, NULL, newtimeout));
#endif
}

/*
 * Register a filedesc for readable events
 * Set up its input buffer
 */
int BX_new_open(int des) {
  if (des < 0)
    return des; /* Invalid */

  if (!io_rec)
    init_io();

  if (!FD_ISSET(des, &readables))
    FD_SET(des, &readables);
  if (des > global_max_fd)
    global_max_fd = des;

  return des;
}

int new_open_write(int des) {
  if (des < 0)
    return des; /* Invalid */

  if (!io_rec)
    init_io();

  if (!FD_ISSET(des, &writables))
    FD_SET(des, &writables);
#if 0
	if (des > global_max_fd)
		global_max_fd = des;
#endif
  return des;
}

/*
 * Unregister a filedesc for readable events
 * and close it down and free its input buffer
 */
int BX_new_close(int des) {
  if (des < 0)
    return -1;

  if (FD_ISSET(des, &readables))
    FD_CLR(des, &readables);

  if (io_rec && io_rec[des]) {
    new_free(&(io_rec[des]->buffer));
    new_free((char **)&(io_rec[des]));
  }
#if defined(BX_POLL_EPOLL) || defined(BX_POLL_KQUEUE)
  io_poll_remove(des);
#endif
  close(des);

  /*
   * If we're closing the highest fd in use, then we
   * want to adjust global_max_fd downward to the next highest fd.
   */
  if (des == global_max_fd) {
    do
      des--;
    while (des >= 0 && !FD_ISSET(des, &readables));

    global_max_fd = des;
  }
  return -1;
}

int new_close_write(int des) {
  if (des < 0)
    return -1;

  if (FD_ISSET(des, &writables))
    FD_CLR(des, &writables);

  if (io_rec && io_rec[des]) {
    new_free(&(io_rec[des]->buffer));
    new_free((char **)&(io_rec[des]));
  }
#if defined(BX_POLL_EPOLL) || defined(BX_POLL_KQUEUE)
  io_poll_remove(des);
#endif
  close(des);

#if 0
	/*
	 * If we're closing the highest fd in use, then we
	 * want to adjust global_max_fd downward to the next highest fd.
	 */
	if (des == global_max_fd)
	{
		do
			des--;
		while (!FD_ISSET(des, &writables));

		global_max_fd = des;
	}
#endif
  return -1;
}

/* set's socket options */
void set_socket_options(int s) {
  int opt = 1;
#ifndef NO_STRUCT_LINGER
  struct linger lin;

  lin.l_onoff = lin.l_linger = 0;
  setsockopt(s, SOL_SOCKET, SO_LINGER, (char *)&lin, sizeof(struct linger));
#endif

  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
  opt = 1;
  setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char *)&opt, sizeof(opt));

#if notyet
  /* This is waiting for nonblock-aware code */
  info = fcntl(fd, F_GETFL, 0);
  info |= O_NONBLOCK;
  fcntl(fd, F_SETFL, info);
#endif
}
