cmake_minimum_required(VERSION 3.16)

# BitchX - text-mode IRC client (ircII/EPIC lineage)
# CMake build system (replaces the legacy autotools setup).

project(BitchX C)

set(BITCHX_MAJOR 1)
set(BITCHX_MINOR 2)
set(BITCHX_MICRO 1)
set(RELEASE_TAG "bitchx-${BITCHX_MAJOR}.${BITCHX_MINOR}.${BITCHX_MICRO}")

if(NOT DEFINED VERSION_NUMBER)
  set(VERSION_NUMBER "${BITCHX_MAJOR}.${BITCHX_MINOR}.${BITCHX_MICRO}")
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    execute_process(
      COMMAND git describe --match "${RELEASE_TAG}" --always --dirty
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE _git_desc
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET)
    if(_git_desc AND NOT _git_desc STREQUAL RELEASE_TAG)
      string(REGEX REPLACE "^${RELEASE_TAG}" "" _git_suffix "${_git_desc}")
      set(VERSION_NUMBER "${VERSION_NUMBER}${_git_suffix}")
    endif()
  endif()
endif()
set(VERSION "BitchX-${VERSION_NUMBER}")
set(_VERSION_ "BitchX")

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(BITCHX_SSL       "Enable SSL/TLS support (auto-detected if built-in OpenSSL is found)" ON)
option(BITCHX_TCL       "Enable Tcl scripting support" OFF)
option(BITCHX_PLUGINS   "Build the BitchX plugins (dlopen modules)" OFF)
option(BITCHX_IPV6      "Enable IPv6 support" ON)
option(BITCHX_CDROM     "Enable CD-ROM support (Linux only)" OFF)
option(BITCHX_SOCKS4    "Build with SOCKS4 support" OFF)
option(BITCHX_SOCKS5    "Build with SOCKS5 support" OFF)
set(BITCHX_PLUGIN_LIST "all" CACHE STRING
    "Semicolon/comma separated list of plugins to build, or \"all\" (default)")
set(BITCHX_MAILDIR "" CACHE STRING
    "Enable QMAIL support with the given maildir path")
set(BITCHX_DEFAULT_SERVER "" CACHE STRING
    "Comma-separated list of default servers (SERVER[:PORT[:PASSWORD[:NICK]]])")
set(BITCHX_TERMCAP OFF CACHE BOOL "Use termcap in preference to terminfo")

if(UNIX)
  set(RETSIGTYPE "void")
else()
  set(RETSIGTYPE "int")
endif()

# Default install locations follow the old autotools layout.
include(GNUInstallDirs)
if(NOT DEFINED BITCHX_IRCLIB_INSTALL)
  set(BITCHX_IRCLIB_INSTALL "${CMAKE_INSTALL_LIBDIR}/bx")
endif()
set(IRCLIB      "${CMAKE_INSTALL_PREFIX}/${BITCHX_IRCLIB_INSTALL}")
set(HELPDIR     "${IRCLIB}/help")
set(INSTALL_SCRIPT "${IRCLIB}/script")
set(PLUGINDIR   "${IRCLIB}/plugins")
set(TRANSLATION_PATH "${IRCLIB}/translation")
set(WSERV_PATH  "${IRCLIB}/wserv")
set(IRCPATH     "${CMAKE_INSTALL_PREFIX}/share/bx:${CMAKE_INSTALL_PREFIX}/${BITCHX_IRCLIB_INSTALL}:.:${IRCLIB}/plugins:${INSTALL_SCRIPT}:${IRCLIB}")
set(DEFAULT_CTOOLZ_DIR "~/.BitchX")

set(DEFAULT_MSGLOGFILE "BitchX.away")
set(DEFAULT_BITCHX_HELP_FILE "BitchX.help")
set(DEFAULT_SCRIPT_HELP_FILE "BitchX.help")
set(DEFAULT_BITCHX_KICK_FILE "BitchX.kick")
set(DEFAULT_BITCHX_KILL_FILE "BitchX.kill")
set(DEFAULT_BITCHX_QUIT_FILE "BitchX.quit")
set(DEFAULT_BITCHX_IRCNAME_FILE "BitchX.ircnames")

if(BITCHX_DEFAULT_SERVER)
  string(REPLACE "," " " DEFAULT_SERVER "${BITCHX_DEFAULT_SERVER}")
else()
  set(DEFAULT_SERVER "")
endif()

if(BITCHX_MAILDIR)
  set(HAVE_QMAIL 1)
  set(UNIX_MAIL "${BITCHX_MAILDIR}")
else()
  set(UNIX_MAIL "")
endif()

if(WIN32)
  set(SHLIB_SUFFIX ".dll")
else()
  set(SHLIB_SUFFIX ".so")
endif()

if(BITCHX_IPV6 AND NOT WIN32)
  set(IPV6 1)
endif()

# ---------------------------------------------------------------------------
# Compiler setup
# ---------------------------------------------------------------------------
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckTypeSize)
include(CheckSymbolExists)
include(CheckCSourceCompiles)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -fno-strict-aliasing)
endif()

# ---------------------------------------------------------------------------
# Header checks
# ---------------------------------------------------------------------------
check_include_file("sys/socket.h"    HAVE_SYS_SOCKET_H)
check_include_file("sys/sockio.h"    HAVE_SYS_SOCKIO_H)
check_include_file("sys/time.h"      HAVE_SYS_TIME_H)
check_include_file("sys/fcntl.h"     HAVE_SYS_FCNTL_H)
check_include_file("fcntl.h"         HAVE_FCNTL_H)
check_include_file("sys/file.h"      HAVE_SYS_FILE_H)
check_include_file("netinet/in.h"    HAVE_NETINET_IN_H)
check_include_file("netdb.h"         HAVE_NETDB_H)
check_include_file("sys/un.h"        HAVE_SYS_UN_H)
check_include_file("sys/filio.h"     HAVE_SYS_FILIO_H)
check_include_file("regex.h"         HAVE_REGEX_H)
check_include_file("arpa/nameser.h"  HAVE_ARPA_NAMESER_H)
check_include_file("dirent.h"        HAVE_DIRENT_H)
check_include_file("sys/ndir.h"      HAVE_SYS_NDIR_H)
check_include_file("sys/dir.h"       HAVE_SYS_DIR_H)
check_include_file("ndir.h"          HAVE_NDIR_H)
check_include_file("termios.h"       HAVE_TERMIOS_H)
check_include_file("stdint.h"        HAVE_STDINT_H)
check_include_file("inttypes.h"      HAVE_INTTYPES_H)
check_include_file("memory.h"        HAVE_MEMORY_H)
check_include_file("strings.h"       HAVE_STRINGS_H)
check_include_file("string.h"        HAVE_STRING_H)
check_include_file("stdlib.h"        HAVE_STDLIB_H)
check_include_file("unistd.h"        HAVE_UNISTD_H)
check_include_file("sys/stat.h"      HAVE_SYS_STAT_H)
check_include_file("sys/types.h"     HAVE_SYS_TYPES_H)
check_include_file("alloca.h"        HAVE_ALLOCA_H)
check_include_file("linux/soundcard.h"  HAVE_LINUX_SOUNDCARD_H)
check_include_file("machine/soundcard.h" HAVE_MACHINE_SOUNDCARD_H)
check_include_file("sys/soundcard.h" HAVE_SYS_SOUNDCARD_H)
check_include_file("dlfcn.h" HAVE_DLFCN_H)
check_symbol_exists(dlopen "dlfcn.h" HAVE_DLOPEN)
if(HAVE_DLOPEN)
  set(HAVE_DLLIB 1)
endif()

# Polling backends: epoll on Linux, kqueue on BSD/macOS.
check_include_file("sys/epoll.h" HAVE_SYS_EPOLL_H)
check_include_file("sys/event.h" HAVE_SYS_EVENT_H)

if(HAVE_SYS_SOCKET_H)
  set(CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES};${CMAKE_SOURCE_DIR}/include")
  check_include_file("net/if.h" HAVE_NET_IF_H)
  check_include_file("arpa/inet.h" HAVE_ARPA_INET_H)
  check_include_file("resolv.h" HAVE_RESOLV_H)
endif()

check_include_file("ncurses/curses.h" HAVE_NCURSES_CURSES_H)
check_c_source_compiles(
  "#include <sys/types.h>
   #include <sys/socket.h>
   socklen_t bx_socklen;
   int main(void) { return (int)bx_socklen; }"
  HAVE_SOCKLEN_T_COMPILE)
if(HAVE_SOCKLEN_T_COMPILE)
  set(HAVE_SOCKLEN_T 1)
endif()

if(HAVE_SYS_SOCKET_H)
  set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES})
endif()

# ---------------------------------------------------------------------------
# Function checks
# ---------------------------------------------------------------------------
foreach(_fn
    socket gethostname gettimeofday strtoul strlcpy strlcat stpcpy
    vsnprintf snprintf setsid strerror uname getrusage sysconf getpgid
    killpg getlogin realpath fchdir getpass fpathconf getpwent setvbuf
    select mkstemp memmove setenv strftime inet_aton tparm getpgrp setpgrp)
  string(TOUPPER "HAVE_${_fn}" _var)
  check_function_exists("${_fn}" "${_var}")
endforeach()

if(HAVE_GETPGRP)
  set(CMAKE_REQUIRED_FLAGS "")   # silence; getpgrp() takes no args on POSIX
endif()

if(UNIX)
  set(HAVE_GETPGRP_VOID 1)
  set(GETPGRP_VOID 1)
endif()

# Modern systems always declare these.
set(ERRNO_DECLARED 1)
set(GETPASS_DECLARED 1)
set(GETPGID_DECLARED 1)
set(KILLPG_DECLARED 1)
set(STPCPY_DECLARED 1)
set(STRUCT_LINGER_DECLARED 1)
set(TIME_WITH_SYS_TIME 1)

# Signal-name arrays and strsignal(). These must be numeric (0/1) because
# the code tests them with preprocessor arithmetic. strsignal() is the
# preferred interface on modern systems.
check_symbol_exists(strsignal "string.h" _decl_strsignal)
if(_decl_strsignal)
  set(HAVE_DECL_STRSIGNAL 1)
else()
  set(HAVE_DECL_STRSIGNAL 0)
endif()
check_symbol_exists(sys_siglist "signal.h" _decl_sys_siglist)
if(_decl_sys_siglist)
  set(HAVE_DECL_SYS_SIGLIST 1)
else()
  set(HAVE_DECL_SYS_SIGLIST 0)
endif()
check_symbol_exists(_sys_siglist "signal.h" _decl_sys_siglist2)
if(_decl_sys_siglist2)
  set(HAVE_DECL__SYS_SIGLIST 1)
else()
  set(HAVE_DECL__SYS_SIGLIST 0)
endif()

# Non-blocking connect support (POSIX O_NONBLOCK).
if(UNIX)
  set(NBLOCK_POSIX 1)
endif()

# 32-bit typedef used by the DCC checksum.
check_type_size("unsigned int" SIZEOF_UNSIGNED_INT LANGUAGE C)
check_type_size("unsigned long" SIZEOF_UNSIGNED_LONG LANGUAGE C)
if(SIZEOF_UNSIGNED_INT EQUAL 4)
  set(UNSIGNED_INT32 1)
elseif(SIZEOF_UNSIGNED_LONG EQUAL 4)
  set(UNSIGNED_LONG32 1)
else()
  set(UNKNOWN_32INT 1)
endif()
if(NOT SIZEOF_UNSIGNED_INT)
  set(SIZEOF_UNSIGNED_INT 4)
endif()
if(NOT SIZEOF_UNSIGNED_LONG)
  set(SIZEOF_UNSIGNED_LONG 8)
endif()

# ---------------------------------------------------------------------------
# External libraries
# ---------------------------------------------------------------------------
# terminfo / termcap for terminal handling (ncurses).
find_package(PkgConfig QUIET)
set(NCURSES_LIBRARIES)
set(NCURSES_INCLUDE_DIR)
if(PkgConfig_FOUND)
  if(NOT BITCHX_TERMCAP)
    pkg_check_modules(CURSES_PKG QUIET ncursesw)
    if(NOT CURSES_PKG_FOUND)
      pkg_check_modules(CURSES_PKG QUIET ncurses)
    endif()
  else()
    pkg_check_modules(CURSES_PKG QUIET ncursesw)
  endif()
endif()

find_library(NCURSES_LIB NAMES ncursesw ncurses)
if(NCURSES_LIB)
  list(APPEND NCURSES_LIBRARIES "${NCURSES_LIB}")
else()
  find_library(NCURSES_LIB NAMES tinfow tinfo)
  if(NCURSES_LIB)
    list(APPEND NCURSES_LIBRARIES "${NCURSES_LIB}")
  endif()
endif()

if(CURSES_PKG_INCLUDE_DIRS)
  set(NCURSES_INCLUDE_DIR "${CURSES_PKG_INCLUDE_DIRS}")
endif()
if(NOT NCURSES_LIBRARIES AND PkgConfig_FOUND)
  # pkg-config gave us the library flags but find_library missed it.
  list(APPEND NCURSES_LIBRARIES ${CURSES_PKG_LIBRARIES})
endif()
if(NOT NCURSES_LIBRARIES)
  message(FATAL_ERROR
    "Could not find the ncurses library. "
    "Install the ncurses development package (libncurses-dev).")
endif()

# Actually probe that we can compile and link a terminfo program, using the
# same include/lib paths pkg-config reported (they carry important feature
# macros and extra link flags).
set(_old_requires_libs ${CMAKE_REQUIRED_LIBRARIES})
set(_old_requires_incl ${CMAKE_REQUIRED_INCLUDES})
set(_old_requires_flags ${CMAKE_REQUIRED_FLAGS})
set(CMAKE_REQUIRED_LIBRARIES ${NCURSES_LIBRARIES})
set(CMAKE_REQUIRED_INCLUDES ${CURSES_PKG_INCLUDE_DIRS})
set(CMAKE_REQUIRED_FLAGS "${CURSES_PKG_CFLAGS_OTHER}")

if(NOT BITCHX_TERMCAP)
  check_c_source_compiles(
    "#include <term.h>
     int main(void) { int errret = 0; setupterm((char *)0, 1, &errret); return 0; }"
    HAVE_TERMINFO_COMPILE)
endif()
if(NOT HAVE_TERMINFO_COMPILE)
  check_c_source_compiles(
    "#include <term.h>
     int main(void) { return tgetent((char *)0, (char *)0); }"
    HAVE_TERMCAP_COMPILE)
endif()
set(CMAKE_REQUIRED_LIBRARIES ${_old_requires_libs})
set(CMAKE_REQUIRED_INCLUDES ${_old_requires_incl})
set(CMAKE_REQUIRED_FLAGS ${_old_requires_flags})

if(BITCHX_TERMCAP)
  if(NOT HAVE_TERMCAP_COMPILE)
    message(FATAL_ERROR
      "termcap mode requested but tgetent() is not available in ncurses.")
  endif()
  set(HAVE_TERMCAP 1)
else()
  if(HAVE_TERMINFO_COMPILE)
    set(HAVE_TERMINFO 1)
  elseif(HAVE_TERMCAP_COMPILE)
    # ncurses compiled without terminfo; fall back to termcap.
    set(HAVE_TERMCAP 1)
  else()
    message(FATAL_ERROR
      "Could not find a working terminfo/termcap implementation. "
      "Please install the ncurses development package (libncurses-dev).")
  endif()
endif()

foreach(_h ncurses.h ncurses/ncurses.h curses.h ncurses/termcap.h termcap.h ncurses/term.h term.h ncursesw/ncurses.h ncursesw/term.h)
  string(TOUPPER "HAVE_${_h}" _var)
  string(REGEX REPLACE "/" "_" _var "${_var}")
  string(REGEX REPLACE "\\." "_" _var "${_var}")
  check_include_file("${_h}" "${_var}")
endforeach()

if(NOT HAVE_TERMINFO AND NOT HAVE_TERMCAP)
  message(FATAL_ERROR "Neither terminfo nor termcap is available.")
endif()

# ncursesw headers need the feature macros that pkg-config reports.
if(CURSES_PKG_CFLAGS_OTHER)
  add_compile_options(${CURSES_PKG_CFLAGS_OTHER})
endif()

# OpenSSL (SSL/TLS for server connections and DCC).
if(BITCHX_SSL)
  find_package(OpenSSL QUIET)
  if(OPENSSL_FOUND)
    set(HAVE_LIBSSL 1)
    set(HAVE_LIBCRYPTO 1)
  elseif(BITCHX_SSL AND NOT BUILD_SHARED_LIBS)
    # --with-ssl was explicitly requested; fail loudly instead of silently
    # proceeding without TLS.
    message(FATAL_ERROR "OpenSSL development files not found. Install libssl-dev or pass -DBITCHX_SSL=OFF.")
  endif()
endif()

# Tcl scripting.
if(BITCHX_TCL)
  if(PkgConfig_FOUND)
    pkg_check_modules(TCL_PKG QUIET tcl)
  endif()
  if(TCL_PKG_FOUND)
    set(HAVE_TCL_H 1)
    set(WANT_TCL 1)
    set(TCL_INCLUDE_DIRS "${TCL_PKG_INCLUDE_DIRS}")
    set(TCL_LIBRARIES "${TCL_PKG_LIBRARIES}")
  else()
    find_path(TCL_INCLUDE_DIR tcl.h PATH_SUFFIXES tcl8.6 tcl8.5 tcl9.0)
    find_library(TCL_LIBRARY NAMES tcl8.6 tcl8.5 tcl tcl86 tcl85)
    if(TCL_INCLUDE_DIR AND TCL_LIBRARY)
      set(HAVE_TCL_H 1)
      set(WANT_TCL 1)
      set(TCL_INCLUDE_DIRS "${TCL_INCLUDE_DIR}")
      set(TCL_LIBRARIES "${TCL_LIBRARY}")
    endif()
  endif()
  if(NOT WANT_TCL)
    message(FATAL_ERROR "Tcl libraries not found. Install tcl-dev or pass -DBITCHX_TCL=OFF.")
  endif()
endif()

# SOCKS proxies.
if(BITCHX_SOCKS4)
  set(SOCKS 1)
  find_library(SOCKS4_LIB Rconnect NAMES socks4 socks)
  if(NOT SOCKS4_LIB)
    message(FATAL_ERROR "SOCKS4 library not found (--with-socks=4).")
  endif()
endif()
if(BITCHX_SOCKS5)
  set(SOCKS 1)
  find_library(SOCKS5_LIB SOCKSconnect NAMES socks5)
  if(NOT SOCKS5_LIB)
    message(FATAL_ERROR "SOCKS5 library not found (--with-socks=5).")
  endif()
endif()

# CD-ROM support (Linux only).
if(BITCHX_CDROM)
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(WANT_CD 1)
  else()
    message(WARNING "CD-ROM support is only enabled on Linux; ignoring.")
  endif()
endif()

# crypt() for password hashing. Split out of libc on modern glibc.
find_library(CRYPT_LIB NAMES crypt)
if(CRYPT_LIB)
  set(HAVE_CRYPT 1)
  set(BITCHX_CRYPT_LIB "${CRYPT_LIB}")
endif()

# ---------------------------------------------------------------------------
# Generate the configuration header
# ---------------------------------------------------------------------------
set(CMAKE_REQUIRED_INCLUDES)
set(BITCHX_CONFIG_DIR "${CMAKE_BINARY_DIR}/include")
file(MAKE_DIRECTORY "${BITCHX_CONFIG_DIR}")
configure_file(
  "${CMAKE_SOURCE_DIR}/include/defs.h.in"
  "${BITCHX_CONFIG_DIR}/defs.h"
  @ONLY)

# ---------------------------------------------------------------------------
# Subdirectories
# ---------------------------------------------------------------------------
add_subdirectory(source)

if(BITCHX_PLUGINS)
  add_subdirectory(dll)
endif()

# ---------------------------------------------------------------------------
# Install data files
# ---------------------------------------------------------------------------
install(FILES
  BitchX.help
  BitchX.ircnames
  BitchX.quit
  BitchX.reasons
  BitchX.kill
  DESTINATION "${IRCLIB}")

install(DIRECTORY translation/
  DESTINATION "${TRANSLATION_PATH}")
install(DIRECTORY script/
  DESTINATION "${INSTALL_SCRIPT}")
install(DIRECTORY bitchx-docs/
  DESTINATION "${HELPDIR}")
install(FILES doc/BitchX.1
  DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")