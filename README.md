# BitchX

BitchX is a free, text-mode IRC (Internet Relay Chat) client for UNIX-like
systems. It descends from the ircII client and is heavily influenced by EPIC,
and has been a fixture of many a shell account, BBS, and console since the
mid-1990s. This tree is a modern continuation of that lineage, rebuilt on a
CMake-based build system, with the classic bitmapped ASCII art restored and
rendered correctly on today's UTF-8 terminals.

## Features

- Full ircII/EPIC-style scripting language with aliases, variables, and a
  large library of built-in commands
- Multiple server and channel windows with activity monitoring
- Tab-completion on nicks, commands, and channels
- DCC send/recv/chat, plus a DCC server (`wserv`)
- Plugin system with loadable modules (chat scripts, file servers,
  encryption, NickServ automation, and more)
- Default visibility into a classic BitchX-isms: auto-join, nick tracking,
  userlist, kill/quit/part tracking, flood protection, and away support
- SSL/TLS for server connections and DCC (optional)
- IPv6 support (optional)
- Mail notification via QMAIL support (optional)
- Terms of the EPIC software license apply (see `COPYRIGHT`)

## Dependencies

- A C compiler (GCC or Clang) and CMake >= 3.16
- ncursesw (wide-character ncurses preferred; ncurses acceptable)
- OpenSSL development files (optional; disable with `-DBITCHX_SSL=OFF`)
- Tcl (optional; enable with `-DBITCHX_TCL=ON`)
- `dlopen` for plugin support on platforms that provide it

## Building

```sh
cmake -S . -B build
cmake --build build -j
```

The resulting binary is `build/source/BitchX`.

### Build options

| Option                | Default | Description                                        |
|-----------------------|---------|----------------------------------------------------|
| `BITCHX_SSL`          | ON      | SSL/TLS support via OpenSSL                        |
| `BITCHX_TCL`          | OFF     | Tcl scripting support                              |
| `BITCHX_PLUGINS`      | OFF     | Build the dlopen plugin modules                    |
| `BITCHX_IPV6`         | ON      | IPv6 support                                       |
| `BITCHX_CDROM`        | OFF     | CD-ROM support (Linux only)                        |
| `BITCHX_SOCKS4/5`     | OFF     | SOCKS proxy support                                |
| `BITCHX_TERMCAP`      | OFF     | Use termcap instead of terminfo                    |
| `BITCHX_MAILDIR`      | ""      | Enable QMAIL support for the given maildir         |
| `BITCHX_DEFAULT_SERVER` | ""   | Comma-separated default server list pre-loaded     |

Example:

```sh
cmake -S . -B build -DBITCHX_TCL=ON -DBITCHX_PLUGINS=ON
cmake --build build -j
```

## Running

```sh
build/source/BitchX [irc.server.example] [port]
```

Configuration and scripts live in `~/.BitchX/`. `BitchX -h` shows the startup
switches (e.g. `-n nickname`, `-a` to add the default and command-line servers
to the server list, `-c #channel` to auto-join); the bundled manual
(`doc/BitchX.1`) and on-line help cover the rest.

## Installing

```sh
cmake --install build
```

## Layout

- `source/` — the client, including the restored CP437 artwork
- `dll/` — optional plugin modules (e.g. `blowfish`, `fserv`, `nap`)
- `script/` — bundled scripts
- `translation/` — translation tables
- `bitchx-docs/` — on-line help data
- `doc/` — manual pages and documentation

## History

BitchX began in the early 1990s as an ircII derivative and grew into one of
the most widely deployed IRC clients on shell accounts. The 2.0 line
revives that codebase on a modern toolchain while preserving its
look-and-feel: the original block-graphics startup logo and `/about` screen
are rendered from the restored CP437 artwork via a UTF-8 transliteration
layer, and the display pipeline is width-aware so multibyte glyphs wrap
cleanly on modern terminals.