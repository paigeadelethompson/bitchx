# source/CMakeLists.txt
#
# Builds the main BitchX client plus the wserv and scr-bx helper binaries.

set(BITCHX_CORE_SOURCES
  alias.c
  alist.c
  array.c
  art.c
  banlist.c
  bot_link.c
  cdcc.c
  cdns.c
  chelp.c
  commands.c
  commands2.c
  compat.c
  cset.c
  ctcp.c
  dcc.c
  debug.c
  encrypt.c
  exec.c
  files.c
  flood.c
  fset.c
  functions.c
  funny.c
  glob.c
  hash.c
  hebrew.c
  help.c
  history.c
  hook.c
  if.c
  ignore.c
  input.c
  irc.c
  ircaux.c
  ircsig.c
  keys.c
  lastlog.c
  list.c
  log.c
  mail.c
  misc.c
  modules.c
  names.c
  network.c
  newio.c
  notice.c
  notify.c
  numbers.c
  output.c
  parse.c
  queue.c
  readlog.c
  reg.c
  screen.c
  server.c
  stack.c
  status.c
  struct.c
  tcl_public.c
  term.c
  timer.c
  translat.c
  user.c
  userlist.c
  vars.c
  who.c
  whowas.c
  window.c
  words.c
)

if(BITCHX_CDROM)
  list(APPEND BITCHX_CORE_SOURCES cdrom.c)
endif()
if(BITCHX_TCL)
  list(APPEND BITCHX_CORE_SOURCES tcl.c)
endif()

set(BITCHX_PUBLIC_INCLUDES
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_BINARY_DIR}/include"
)
if(NCURSES_INCLUDE_DIR)
  list(APPEND BITCHX_PUBLIC_INCLUDES "${NCURSES_INCLUDE_DIR}")
endif()
if(OPENSSL_INCLUDE_DIRS)
  list(APPEND BITCHX_PUBLIC_INCLUDES ${OPENSSL_INCLUDE_DIRS})
endif()
if(TCL_INCLUDE_DIRS)
  list(APPEND BITCHX_PUBLIC_INCLUDES ${TCL_INCLUDE_DIRS})
endif()

# ---------------------------------------------------------------------------
# Main client
# ---------------------------------------------------------------------------
add_executable(BitchX ${BITCHX_CORE_SOURCES})
set_target_properties(BitchX PROPERTIES
  OUTPUT_NAME "BitchX-${VERSION_NUMBER}")
target_include_directories(BitchX PRIVATE ${BITCHX_PUBLIC_INCLUDES})

target_compile_definitions(BitchX PRIVATE
  "IRCLIB=\"${IRCLIB}\""
  "IRCPATH=\"${IRCPATH}\""
  "SHLIB_SUFFIX=\"${SHLIB_SUFFIX}\""
  "PLUGINDIR=\"${PLUGINDIR}\""
  "SCRIPT_PATH=\"${INSTALL_SCRIPT}\""
  "WSERV_PATH=\"${WSERV_PATH}\""
  "TRANSLATION_PATH=\"${TRANSLATION_PATH}\""
)

if(SHLIB_SUFFIX STREQUAL ".dll")
  target_compile_definitions(BitchX PRIVATE WINNT)
endif()

target_link_libraries(BitchX PRIVATE ${NCURSES_LIBRARIES})
if(OPENSSL_FOUND)
  target_link_libraries(BitchX PRIVATE ${OPENSSL_LIBRARIES})
endif()
if(BITCHX_TCL)
  target_link_libraries(BitchX PRIVATE ${TCL_LIBRARIES})
endif()
if(BITCHX_SOCKS4)
  target_link_libraries(BitchX PRIVATE ${SOCKS4_LIB})
endif()
if(BITCHX_SOCKS5)
  target_link_libraries(BitchX PRIVATE ${SOCKS5_LIB})
endif()
if(BITCHX_CRYPT_LIB)
  target_link_libraries(BitchX PRIVATE ${CRYPT_LIB})
endif()
if(UNIX)
  target_link_libraries(BitchX PRIVATE m)
endif()

# ---------------------------------------------------------------------------
# wserv - spawns BitchX windows in new terminal windows
# ---------------------------------------------------------------------------
add_library(wserv_core OBJECT term.c network.c)
set_target_properties(wserv_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(wserv_core PRIVATE WTERM_C)
target_include_directories(wserv_core PRIVATE ${BITCHX_PUBLIC_INCLUDES})

add_executable(wserv wserv.c ircsig.c compat.c $<TARGET_OBJECTS:wserv_core>)
target_include_directories(wserv PRIVATE ${BITCHX_PUBLIC_INCLUDES})
target_link_libraries(wserv PRIVATE ${NCURSES_LIBRARIES})
if(UNIX)
  target_link_libraries(wserv PRIVATE m)
endif()

# ---------------------------------------------------------------------------
# scr-bx - screen-based detachable BitchX
# ---------------------------------------------------------------------------
add_library(scr_bx_core OBJECT term.c)
set_target_properties(scr_bx_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(scr_bx_core PRIVATE STERM_C)
target_include_directories(scr_bx_core PRIVATE ${BITCHX_PUBLIC_INCLUDES})

add_executable(scr-bx scr-bx.c ircsig.c compat.c $<TARGET_OBJECTS:scr_bx_core>)
target_include_directories(scr-bx PRIVATE ${BITCHX_PUBLIC_INCLUDES})
target_link_libraries(scr-bx PRIVATE ${NCURSES_LIBRARIES})
if(UNIX)
  target_link_libraries(scr-bx PRIVATE m)
endif()

# ---------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------
install(TARGETS BitchX
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(CODE "
  execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink
    \"BitchX-${VERSION_NUMBER}\" \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/BitchX\")
  ")

install(TARGETS wserv
  RUNTIME DESTINATION "${BITCHX_IRCLIB_INSTALL}/wserv")
install(TARGETS scr-bx
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")