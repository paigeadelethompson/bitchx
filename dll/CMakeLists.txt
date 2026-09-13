# dll/CMakeLists.txt
#
# Builds the optional dlopen() plugins. Each plugin becomes a shared
# library whose filename must match what the /loaddll command resolves:
# modules.c takes the argument (e.g. "blowfish"), uppercases the first
# letter, and appends "_Init", so "blowfish.so" must export Blowfish_Init.
# The single exception is the abot module, which lives in the abot/
# directory but builds autobot.so to match Autobot_Init.
#
# The old build also compiled dllinit.c into every module, but on ELF and
# Mach-O systems it is an empty translation unit (it only provides the
# Windows DLL entry point), so it is not needed here.

include(CheckIncludeFile)

function(bitchx_plugin name outname)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs ALL_DEFINES)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(sources ${ARG_UNPARSED_ARGUMENTS})
  add_library(${name} MODULE ${sources})
  set_target_properties(${name} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "${outname}"
  )
  target_include_directories(${name} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/include"
  )
  if(NCURSES_INCLUDE_DIR)
    target_include_directories(${name} PRIVATE "${NCURSES_INCLUDE_DIR}")
  endif()
  if(ARG_ALL_DEFINES)
    target_compile_definitions(${name} PRIVATE ${ARG_ALL_DEFINES})
  endif()
  target_link_libraries(${name} PRIVATE ${NCURSES_LIBRARIES})
  if(UNIX)
    target_link_libraries(${name} PRIVATE m)
  endif()
  install(TARGETS ${name}
    LIBRARY DESTINATION "${PLUGINDIR}")
endfunction()

set(_plugin_sources
  abot      "abot/autobot.c"
  acro      "acro/acro.c"
  amp       "amp/audio.c;amp/audioIO.c;amp/audioIO_Linux.c;amp/buffer.c;amp/getbits.c;amp/getdata.c;amp/huffman.c;amp/layer2.c;amp/layer3.c;amp/misc2.c;amp/position.c;amp/transform.c;amp/util.c"
  arcfour   "arcfour/arcfour.c;arcfour/md5.c"
  autocycle "autocycle/autocycle.c"
  blowfish  "blowfish/blowfish.c"
  cavlink   "cavlink/cavlink.c"
  cdrom     "cdrom/cdrom.c"
  encrypt   "encrypt/encrypt.c"
  europa    "europa/europa.c"
  fserv     "fserv/fserv.c"
  hint      "hint/hint.c"
  identd    "identd/identd.c"
  nap       "nap/md5.c;nap/nap.c;nap/nap_file.c;nap/napfunc.c;nap/napother.c;nap/napsend.c"
  nicklist  "nicklist/nicklist.c"
  pkga      "pkga/pkga.c"
  possum    "possum/head.c;possum/llist.c;possum/possum.c"
  qbx       "qbx/qbx.c"
  qmail     "qmail/qmail.c"
  wavplay   "wavplay/wavplay.c"
  xmms      "xmms/xmms.c"
)

set(_plugin_names
  abot acro amp arcfour autocycle blowfish cavlink cdrom encrypt europa
  fserv hint identd nap nicklist pkga possum qbx qmail wavplay xmms)

if(BITCHX_PLUGIN_LIST STREQUAL "all")
  set(_to_build ${_plugin_names})
else()
  string(REPLACE "," ";" BITCHX_PLUGIN_LIST "${BITCHX_PLUGIN_LIST}")
  set(_to_build ${BITCHX_PLUGIN_LIST})
endif()

foreach(_p IN LISTS _to_build)
  list(FIND _plugin_names "${_p}" _idx)
  if(_idx EQUAL -1)
    message(FATAL_ERROR
      "Unknown plugin: ${_p}. Valid plugins: ${_plugin_names}")
  endif()

  if(_p STREQUAL "xmms")
    check_include_file("xmms/xmmsctrl.h" HAVE_XMMS_CTRL_H)
    if(NOT HAVE_XMMS_CTRL_H)
      message(WARNING "Skipping xmms plugin: <xmms/xmmsctrl.h> not found.")
      continue()
    endif()
  endif()

  if(_p STREQUAL "europa")
    check_include_file("mysql/mysql.h" HAVE_MYSQL_H)
    if(NOT HAVE_MYSQL_H)
      message(WARNING "Skipping europa plugin: <mysql/mysql.h> not found.")
      continue()
    endif()
  endif()

  # abot builds as autobot.so to match Autobot_Init.
  if(_p STREQUAL "abot")
    set(_out autobot)
  else()
    set(_out ${_p})
  endif()

  # amp picks its audio backend through OS_* macros in audioIO.c.
  if(_p STREQUAL "amp")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
      set(_defs OS_Linux)
    elseif(CMAKE_SYSTEM_NAME MATCHES "BSD|DragonFly")
      set(_defs OS_BSD)
    else()
      set(_defs)
    endif()
  else()
    set(_defs)
  endif()

  list(FIND _plugin_sources "${_p}" _src_idx)
  math(EXPR _src_idx "${_src_idx} + 1")
  list(GET _plugin_sources ${_src_idx} _src_string)

  if(_defs)
    bitchx_plugin(${_p} ${_out} ${_src_string} ALL_DEFINES ${_defs})
  else()
    bitchx_plugin(${_p} ${_out} ${_src_string})
  endif()
endforeach()