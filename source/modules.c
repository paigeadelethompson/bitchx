
/*
 * Routines within this files are Copyright Colten Edwards 1996
 * Aka panasync on irc.
 * Thanks to Shiek and Flier for helpful hints and suggestions. As well
 * as code in some cases.
 */

#define __modules_c

#include "irc.h"
static char cvsrevision[] = "$Id$";
CVS_REVISION(modules_c)
#include "struct.h"
#include "alias.h"
#include "encrypt.h"
#include "commands.h"
#include "dcc.h"
#include "input.h"
#include "ircaux.h"
#include "flood.h"
#include "hook.h"
#include "list.h"
#include "output.h"
#include "log.h"
#include "ctcp.h"
#include "cdcc.h"
#include "misc.h"
#include "module.h"
#include "names.h"
#include "hash2.h"
#include "vars.h"
#include "screen.h"
#include "parse.h"
#include "server.h"
#include "timer.h"
#include "status.h"
#include "window.h"
#include "tcl_bx.h"
#define MAIN_SOURCE
#include "modval.h"

IrcCommandDll *dll_commands = NULL;
IrcVariableDll *dll_variable = NULL;
extern void (*default_output_function)(Window *, const char *);
extern void *default_status_output_function;

BXGlobalEntry global_table[NUMBER_OF_GLOBAL_FUNCTIONS] = {{NULL}};
BXGlobalEntry *global = global_table;
char *_modname_ = NULL;

#ifdef WANT_DLL

#ifdef NO_DLFCN_H
#include "../include/dlfcn.h"
#else
#if defined(HPUX)
#include <dl.h>
#else
#include <dlfcn.h>
#endif
#endif

#ifndef RTLD_NOW
#define RTLD_NOW 1
#endif

#ifndef RTLD_GLOBAL
#define RTLD_GLOBAL 0
#endif

Packages *install_pack = NULL;
#endif /* WANT_DLL */

extern int BX_read_sockets();
extern int identd;
extern int doing_notice;

extern int (*serv_open_func)(int, unsigned long, int);
extern int (*serv_output_func)(int, int, char *, int);
extern int (*serv_input_func)(int, char *, int, int, int);
extern int (*serv_close_func)(int, unsigned long, int);

int BX_check_module_version(unsigned long);

#ifdef GUI
extern char *lastclicklinedata;
extern int contextx, contexty;
extern int guiipc[2];
#endif

void null_function(void) {}

void init_global_functions(void) {
  static int already_done = 0;

  if (already_done)
    return;
  already_done++;

  /* ircaux.c */
  global_table[MODULE_VERSION_CHECK].module_version_check_slot =
      BX_check_module_version;
  global_table[VSNPRINTF].vsnprintf_slot = vsnprintf;
  global_table[SNPRINTF].snprintf_slot = snprintf;
  global_table[NEW_MALLOC].new_malloc_slot = n_malloc;
  global_table[NEW_FREE].new_free_slot = n_free;
  global_table[NEW_REALLOC].new_realloc_slot = n_realloc;
  global_table[MALLOC_STRCPY].malloc_strcpy_slot = n_malloc_strcpy;
  global_table[MALLOC_STR2CPY].malloc_str2cpy_slot = BX_malloc_str2cpy;
  global_table[M_3DUP].m_3dup_slot = BX_m_3dup;
  global_table[M_OPENDUP].m_opendup_slot = BX_m_opendup;
  global_table[M_S3CAT].m_s3cat_slot = BX_m_s3cat;
  global_table[M_S3CAT_S].m_s3cat_s_slot = BX_m_s3cat_s;
  global_table[M_3CAT].m_3cat_slot = BX_m_3cat;
  global_table[UPPER].upper_slot = BX_upper;
  global_table[LOWER].lower_slot = BX_lower;
  global_table[STRISTR].stristr_slot = BX_stristr;
  global_table[RSTRISTR].rstristr_slot = BX_rstristr;
  global_table[WORD_COUNT].word_count_slot = BX_word_count;
  global_table[REMOVE_TRAILING_SPACES].remove_trailing_spaces_slot =
      BX_remove_trailing_spaces;

  global_table[MY_STRICMP].my_stricmp_slot = BX_my_stricmp;
  global_table[MY_STRNICMP].my_strnicmp_slot = BX_my_strnicmp;

  global_table[MY_STRNSTR].my_strnstr_slot = BX_my_strnstr;
  global_table[CHOP].chop_slot = BX_chop;
  global_table[STRMCPY].strmcpy_slot = BX_strmcpy;
  global_table[STRMCAT].strmcat_slot = BX_strmcat;
  global_table[SCANSTR].scanstr_slot = BX_scanstr;
  global_table[EXPAND_TWIDDLE].expand_twiddle_slot = BX_expand_twiddle;
  global_table[CHECK_NICKNAME].check_nickname_slot = BX_check_nickname;
  global_table[SINDEX].sindex_slot = BX_sindex;
  global_table[RSINDEX].rsindex_slot = BX_rsindex;
  global_table[ISNUMBER].isnumber_slot = BX_is_number;
  global_table[RFGETS].rfgets_slot = BX_rfgets;
  global_table[PATH_SEARCH].path_search_slot = BX_path_search;
  global_table[DOUBLE_QUOTE].double_quote_slot = BX_double_quote;
  global_table[IRCPANIC].ircpanic_slot = BX_ircpanic;
  global_table[END_STRCMP].end_strcmp_slot = BX_end_strcmp;
  global_table[BEEP_EM].beep_em_slot = BX_beep_em;
  global_table[UZFOPEN].uzfopen_slot = BX_uzfopen;
  global_table[FUNC_GET_TIME].func_get_time_slot = BX_get_time;
  global_table[TIME_DIFF].time_diff_slot = BX_time_diff;
  global_table[TIME_TO_NEXT_MINUTE].time_to_next_minute_slot =
      BX_time_to_next_minute;
  global_table[PLURAL].plural_slot = BX_plural;
  global_table[MY_CTIME].my_ctime_slot = BX_my_ctime;
  global_table[LTOA].ltoa_slot = BX_my_ltoa;
  global_table[STRFORMAT].strformat_slot = BX_strformat;
  global_table[MATCHINGBRACKET].matchingbracket_slot = BX_MatchingBracket;
  global_table[PARSE_NUMBER].parse_number_slot = BX_parse_number;
  global_table[SPLITW].splitw_slot = BX_splitw;
  global_table[UNSPLITW].unsplitw_slot = BX_unsplitw;
  global_table[M_2DUP].m_2dup_slot = BX_m_2dup;
  global_table[M_E3CAT].m_e3cat_slot = BX_m_e3cat;
  global_table[CHECK_VAL].check_val_slot = BX_check_val;
  global_table[ON_OFF].on_off_slot = BX_on_off;
  global_table[STREXTEND].strextend_slot = BX_strextend;
  global_table[STRFILL].strfill_slot = BX_strfill;
  global_table[EMPTY_FUNC].empty_func_slot = BX_empty;
  global_table[REMOVE_BRACKETS].remove_brackets_slot = BX_remove_brackets;
  global_table[MY_ATOL].my_atol_slot = BX_my_atol;
  global_table[M_DUPCHAR].m_dupchar_slot = BX_m_dupchar;
  global_table[STREQ].streq_slot = BX_streq;
  global_table[STRIEQ].strieq_slot = BX_strieq;
  global_table[STRMOPENCAT].strmopencat_slot = BX_strmopencat;
  global_table[OV_STRCPY].ov_strcpy_slot = BX_ov_strcpy;
  global_table[STRIP_CONTROL].strip_control_slot = BX_strip_control;
  global_table[FIGURE_OUT_ADDRESS].figure_out_address_slot =
      BX_figure_out_address;
  global_table[STRNRCHR].strnrchr_slot = BX_strnrchr;
  global_table[MASK_DIGITS].mask_digits_slot = BX_mask_digits;
  global_table[CCSPAN].ccspan_slot = BX_ccspan;
  global_table[CHARCOUNT].charcount_slot = BX_charcount;
  global_table[STRPCAT].strpcat_slot = BX_strpcat;
  global_table[STRCPY_NOCOLORCODES].strcpy_nocolorcodes_slot =
      BX_strcpy_nocolorcodes;
  global_table[CRYPTIT].cryptit_slot = BX_cryptit;
  global_table[STRIPDEV].stripdev_slot = BX_stripdev;
  global_table[MANGLE_LINE].mangle_line_slot = BX_mangle_line;
  global_table[MALLOC_STRCAT].malloc_strcat_slot = n_malloc_strcat;
  global_table[M_STRDUP].m_strdup_slot = n_m_strdup;
  global_table[M_STRCAT_UES].m_strcat_ues_slot = n_m_strcat_ues;
  global_table[M_STRNDUP].m_strndup_slot = n_m_strndup;
  global_table[MALLOC_SPRINTF].malloc_sprintf_slot = BX_malloc_sprintf;
  global_table[M_SPRINTF].m_sprintf_slot = BX_m_sprintf;
  global_table[NEXT_ARG].next_arg_slot = BX_next_arg;
  global_table[NEW_NEXT_ARG].new_next_arg_slot = BX_new_next_arg;
  global_table[NEW_NEW_NEXT_ARG].new_new_next_arg_slot = BX_new_new_next_arg;
  global_table[LAST_ARG].last_arg_slot = BX_last_arg;
  global_table[NEXT_IN_COMMA_LIST].next_in_comma_list_slot =
      BX_next_in_comma_list;
  global_table[RANDOM_NUMBER].random_number_slot = BX_random_number;

  /* words.c reg.c */
  global_table[STRSEARCH].strsearch_slot = BX_strsearch;
  global_table[MOVE_TO_WORD].move_to_word_slot = BX_move_to_word;
  global_table[MOVE_WORD_REL].move_word_rel_slot = BX_move_word_rel;
  global_table[EXTRACT].extract_slot = BX_extract;
  global_table[EXTRACT2].extract2_slot = BX_extract2;
  global_table[WILD_MATCH].wild_match_slot = BX_wild_match;

  /* list.c */
  global_table[ADD_TO_LIST].add_to_list_slot = BX_add_to_list;
  global_table[ADD_TO_LIST_EXT].add_to_list_ext_slot = BX_add_to_list_ext;
  global_table[FIND_IN_LIST].find_in_list_slot = BX_find_in_list;
  global_table[FIND_IN_LIST_EXT].find_in_list_ext_slot = BX_find_in_list_ext;
  global_table[REMOVE_FROM_LIST_].remove_from_list__slot = BX_remove_from_list;
  global_table[REMOVE_FROM_LIST_EXT].remove_from_list_ext_slot =
      BX_remove_from_list_ext;
  global_table[REMOVEWILD_FROM_LIST].removewild_from_list_slot =
      BX_removewild_from_list;
  global_table[LIST_LOOKUP].list_lookup_slot = BX_list_lookup;
  global_table[LIST_LOOKUP_EXT].list_lookup_ext_slot = BX_list_lookup_ext;

  /* alist.c */
  global_table[ADD_TO_ARRAY].add_to_array_slot = BX_add_to_array;
  global_table[REMOVE_FROM_ARRAY].remove_from_array_slot = BX_remove_from_array;
  global_table[ARRAY_POP].array_pop_slot = BX_array_pop;
  global_table[REMOVE_ALL_FROM_ARRAY].remove_all_from_array_slot =
      BX_remove_all_from_array;
  global_table[ARRAY_LOOKUP].array_lookup_slot = BX_array_lookup;
  global_table[FIND_ARRAY_ITEM].find_array_item_slot = BX_find_array_item;
  global_table[FIND_FIXED_ARRAY_ITEM].find_fixed_array_item_slot =
      BX_find_fixed_array_item;

  /* server.c */
  global_table[SEND_TO_SERVER].send_to_server_slot = BX_send_to_server;
  global_table[QUEUE_SEND_TO_SERVER].queue_send_to_server_slot =
      BX_queue_send_to_server;
  global_table[MY_SEND_TO_SERVER].my_send_to_server_slot = BX_my_send_to_server;

  /* connecting to the server */
  global_table[GET_CONNECTED].get_connected_slot = BX_get_connected;
  global_table[CONNECT_TO_SERVER_BY_REFNUM].connect_to_server_by_refnum_slot =
      BX_connect_to_server_by_refnum;
  global_table[CLOSE_SERVER].close_server_slot = BX_close_server;
  global_table[IS_SERVER_CONNECTED].is_server_connected_slot =
      BX_is_server_connected;
  global_table[FLUSH_SERVER].flush_server_slot = BX_flush_server;
  global_table[SERVER_IS_CONNECTED].server_is_connected_slot =
      BX_server_is_connected;
  global_table[IS_SERVER_OPEN].is_server_open_slot = BX_is_server_open;
  global_table[CLOSE_ALL_SERVER].close_all_server_slot = BX_close_all_server;
  /* server file reading */
  global_table[READ_SERVER_FILE].read_server_file_slot = BX_read_server_file;
  global_table[ADD_TO_SERVER_LIST].add_to_server_list_slot =
      BX_add_to_server_list;
  global_table[BUILD_SERVER_LIST].build_server_list_slot = BX_build_server_list;
  global_table[DISPLAY_SERVER_LIST].display_server_list_slot =
      BX_display_server_list;
  global_table[PARSE_SERVER_INFO].parse_server_info_slot = BX_parse_server_info;
  global_table[SERVER_LIST_SIZE].server_list_size_slot = BX_server_list_size;
  /* misc server/nickname functions */
  global_table[FIND_SERVER_REFNUM].find_server_refnum_slot =
      BX_find_server_refnum;
  global_table[FIND_IN_SERVER_LIST].find_in_server_list_slot =
      BX_find_in_server_list;
  global_table[PARSE_SERVER_INDEX].parse_server_index_slot =
      BX_parse_server_index;
  global_table[GET_SERVER_REDIRECT].get_server_redirect_slot =
      BX_get_server_redirect;
  global_table[SET_SERVER_REDIRECT].set_server_redirect_slot =
      BX_set_server_redirect;
  global_table[CHECK_SERVER_REDIRECT].check_server_redirect_slot =
      BX_check_server_redirect;
  global_table[FUDGE_NICKNAME].fudge_nickname_slot = BX_fudge_nickname;
  global_table[RESET_NICKNAME].reset_nickname_slot = BX_reset_nickname;
  /* various set server struct functions */
  global_table[SET_SERVER_COOKIE].set_server_cookie_slot = BX_set_server_cookie;
  global_table[UPDATE_SERVER_UMODE].update_server_umode_slot =
      BX_update_server_umode;
  global_table[SET_SERVER_MOTD].set_server_motd_slot = BX_set_server_motd;
  global_table[SET_SERVER_OPERATOR].set_server_operator_slot =
      BX_set_server_operator;
  global_table[SET_SERVER_ITSNAME].set_server_itsname_slot =
      BX_set_server_itsname;
  global_table[SET_SERVER_VERSION].set_server_version_slot =
      BX_set_server_version;
  global_table[SET_SERVER_LAG].set_server_lag_slot = BX_set_server_lag;
  global_table[SET_SERVER_PASSWORD].set_server_password_slot =
      BX_set_server_password;
  global_table[SET_SERVER_NICKNAME].set_server_nickname_slot =
      BX_set_server_nickname;
  global_table[SET_SERVER2_8].set_server2_8_slot = BX_set_server2_8;
  global_table[SET_SERVER_AWAY].set_server_away_slot = BX_set_server_away;

  /* various get server struct functions */
  global_table[GET_SERVER_COOKIE].get_server_cookie_slot = BX_get_server_cookie;
  global_table[GET_SERVER_NICKNAME].get_server_nickname_slot =
      BX_get_server_nickname;
  global_table[GET_SERVER_NAME].get_server_name_slot = BX_get_server_name;
  global_table[GET_SERVER_ITSNAME].get_server_itsname_slot =
      BX_get_server_itsname;
  global_table[GET_SERVER_MOTD].get_server_motd_slot = BX_get_server_motd;
  global_table[GET_SERVER_OPERATOR].get_server_operator_slot =
      BX_get_server_operator;
  global_table[GET_SERVER_VERSION].get_server_version_slot =
      BX_get_server_version;
  global_table[GET_SERVER_UMODE].get_server_umode_slot = BX_get_server_umode;
  global_table[GET_SERVER_PORT].get_server_port_slot = BX_get_server_port;
  global_table[GET_SERVER_LAG].get_server_lag_slot = BX_get_server_lag;
  global_table[GET_SERVER2_8].get_server2_8_slot = BX_get_server2_8;
  global_table[GET_UMODE].get_umode_slot = BX_get_umode;
  global_table[GET_SERVER_AWAY].get_server_away_slot = BX_get_server_away;
  global_table[GET_SERVER_NETWORK].get_server_network_slot =
      BX_get_server_network;
  global_table[GET_PENDING_NICKNAME].get_pending_nickname_slot =
      BX_get_pending_nickname;
  global_table[SERVER_DISCONNECT].server_disconnect_slot = BX_server_disconnect;

  global_table[GET_SERVER_LIST].get_server_list_slot = BX_get_server_list;
  global_table[GET_SERVER_CHANNELS].get_server_channels_slot =
      BX_get_server_channels;
  global_table[SET_SERVER_LAST_CTCP_TIME].set_server_last_ctcp_time_slot =
      BX_set_server_last_ctcp_time;
  global_table[GET_SERVER_LAST_CTCP_TIME].get_server_last_ctcp_time_slot =
      BX_get_server_last_ctcp_time;
  global_table[SET_SERVER_TRACE_FLAG].set_server_trace_flag_slot =
      BX_set_server_trace_flag;
  global_table[GET_SERVER_TRACE_FLAG].get_server_trace_flag_slot =
      BX_get_server_trace_flag;
  global_table[SET_SERVER_STAT_FLAG].set_server_stat_flag_slot =
      BX_set_server_stat_flag;
  global_table[GET_SERVER_STAT_FLAG].get_server_stat_flag_slot =
      BX_get_server_stat_flag;
  global_table[GET_SERVER_READ].get_server_read_slot = BX_get_server_read;
  global_table[GET_SERVER_LINKLOOK].get_server_linklook_slot =
      BX_get_server_linklook;
  global_table[SET_SERVER_LINKLOOK].set_server_linklook_slot =
      BX_set_server_linklook;
  global_table[GET_SERVER_LINKLOOK_TIME].get_server_linklook_time_slot =
      BX_get_server_linklook_time;
  global_table[SET_SERVER_LINKLOOK_TIME].set_server_linklook_time_slot =
      BX_set_server_linklook_time;
  global_table[GET_SERVER_TRACE_KILL].get_server_trace_kill_slot =
      BX_get_server_trace_kill;
  global_table[SET_SERVER_TRACE_KILL].set_server_trace_kill_slot =
      BX_set_server_trace_kill;
  global_table[ADD_SERVER_CHANNELS].add_server_channels_slot =
      BX_add_server_channels;
  global_table[SET_SERVER_CHANNELS].set_server_channels_slot =
      BX_set_server_channels;
  global_table[SEND_MSG_TO_CHANNELS].send_msg_to_channels_slot =
      BX_send_msg_to_channels;
  global_table[SEND_MSG_TO_NICKS].send_msg_to_nicks_slot = BX_send_msg_to_nicks;
  global_table[IS_SERVER_QUEUE].is_server_queue_slot = BX_is_server_queue;

  /* glob.c */
  global_table[BSD_GLOB].bsd_glob_slot = BX_bsd_glob;
  global_table[BSD_GLOBFREE].bsd_globfree_slot = BX_bsd_globfree;

  /* output.c */
  global_table[PUT_IT].put_it_slot = BX_put_it;
  global_table[BITCHSAY].bitchsay_slot = BX_bitchsay;
  global_table[YELL].yell_slot = BX_yell;

  /* screen.c */
  global_table[ADD_TO_SCREEN].add_to_screen_slot = BX_add_to_screen;
  global_table[XTERM_SETTITLE].xterm_settitle_slot = BX_xterm_settitle;
  global_table[PREPARE_DISPLAY].prepare_display_slot = BX_prepare_display;
  global_table[ADD_TO_WINDOW].add_to_window_slot = BX_add_to_window;
  global_table[SKIP_INCOMING_MIRC].skip_incoming_mirc_slot =
      BX_skip_incoming_mirc;
  global_table[SPLIT_UP_LINE].split_up_line_slot = BX_split_up_line;
  global_table[OUTPUT_LINE].output_line_slot = BX_output_line;
  global_table[OUTPUT_WITH_COUNT].output_with_count_slot = BX_output_with_count;
  global_table[SCROLL_WINDOW].scroll_window_slot = BX_scroll_window;
  global_table[CURSOR_NOT_IN_DISPLAY].cursor_not_in_display_slot =
      BX_cursor_not_in_display;
  global_table[CURSOR_IN_DISPLAY].cursor_in_display_slot = BX_cursor_in_display;
  global_table[IS_CURSOR_IN_DISPLAY].is_cursor_in_display_slot =
      BX_is_cursor_in_display;
  global_table[REPAINT_WINDOW].repaint_window_slot = BX_repaint_window;
  global_table[CREATE_NEW_SCREEN].create_new_screen_slot = BX_create_new_screen;
#ifdef WINDOW_CREATE
  global_table[CREATE_ADDITIONAL_SCREEN].create_additional_screen_slot =
      BX_create_additional_screen;
  global_table[KILL_SCREEN].kill_screen_slot = BX_kill_screen;
#endif
  global_table[ADD_WAIT_PROMPT].add_wait_prompt_slot = BX_add_wait_prompt;
  global_table[SKIP_CTL_C_SEQ].skip_ctl_c_seq_slot = BX_skip_ctl_c_seq;
  global_table[STRIP_ANSI].strip_ansi_slot = BX_strip_ansi;

  /* status.c */
  global_table[BUILD_STATUS].build_status_slot = BX_build_status;

  /* window.c */
  global_table[GET_WINDOW_BY_NAME].get_window_by_name_slot =
      BX_get_window_by_name;
  global_table[GET_CURRENT_CHANNEL_BY_REFNUM]
      .get_current_channel_by_refnum_slot = BX_get_current_channel_by_refnum;
  global_table[NEW_WINDOW].new_window_slot = BX_new_window;
  global_table[GET_WINDOW_SERVER].get_window_server_slot = BX_get_window_server;
  global_table[RESIZE_WINDOW].resize_window_slot = BX_resize_window;
  global_table[UPDATE_ALL_WINDOWS].update_all_windows_slot =
      BX_update_all_windows;
  global_table[SET_SCREENS_CURRENT_WINDOW].set_screens_current_window_slot =
      BX_set_screens_current_window;
  global_table[DELETE_WINDOW].delete_window_slot = BX_delete_window;
  global_table[FREE_FORMATS].free_formats_slot = BX_free_formats;
  global_table[REMOVE_WINDOW_FROM_SCREEN].remove_window_from_screen_slot =
      BX_remove_window_from_screen;
  global_table[TRAVERSE_ALL_WINDOWS].traverse_all_windows_slot =
      BX_traverse_all_windows;
  global_table[ADD_TO_INVISIBLE_LIST].add_to_invisible_list_slot =
      BX_add_to_invisible_list;
  global_table[ADD_TO_WINDOW_LIST].add_to_window_list_slot =
      BX_add_to_window_list;
  global_table[RECALCULATE_WINDOW_POSITIONS].recalculate_window_positions_slot =
      BX_recalculate_window_positions;
  global_table[MOVE_WINDOW].move_window_slot = BX_move_window;
  global_table[REDRAW_ALL_WINDOWS].redraw_all_windows_slot =
      BX_redraw_all_windows;
  global_table[REBALANCE_WINDOWS].rebalance_windows_slot = BX_rebalance_windows;
  global_table[RECALCULATE_WINDOWS].recalculate_windows_slot =
      BX_recalculate_windows;
  global_table[GOTO_WINDOW].goto_window_slot = BX_goto_window;
  global_table[HIDE_BX_WINDOW].hide_bx_window_slot = BX_hide_window;
  global_table[FUNC_SWAP_LAST_WINDOW].func_swap_last_window_slot =
      BX_swap_last_window;
  global_table[FUNC_SWAP_NEXT_WINDOW].func_swap_next_window_slot =
      BX_swap_next_window;
  global_table[FUNC_SWAP_PREVIOUS_WINDOW].func_swap_previous_window_slot =
      BX_swap_previous_window;
  global_table[SHOW_WINDOW].show_window_slot = BX_show_window;
  global_table[GET_STATUS_BY_REFNUM].get_status_by_refnum_slot =
      BX_get_status_by_refnum;
  global_table[GET_WINDOW_BY_DESC].get_window_by_desc_slot =
      BX_get_window_by_desc;
  global_table[GET_WINDOW_BY_REFNUM].get_window_by_refnum_slot =
      BX_get_window_by_refnum;
  global_table[GET_VISIBLE_BY_REFNUM].get_visible_by_refnum_slot =
      BX_get_visible_by_refnum;
  global_table[FUNC_NEXT_WINDOW].func_next_window_slot = BX_next_window;
  global_table[FUNC_PREVIOUS_WINDOW].func_previous_window_slot =
      BX_previous_window;
  global_table[UPDATE_WINDOW_STATUS].update_window_status_slot =
      BX_update_window_status;
  global_table[UPDATE_ALL_STATUS].update_all_status_slot = BX_update_all_status;
  global_table[UPDATE_WINDOW_STATUS_ALL].update_window_status_all_slot =
      BX_update_window_status_all;
  global_table[STATUS_UPDATE].status_update_slot = BX_status_update;
  global_table[SET_PROMPT_BY_REFNUM].set_prompt_by_refnum_slot =
      BX_set_prompt_by_refnum;
  global_table[GET_PROMPT_BY_REFNUM].get_prompt_by_refnum_slot =
      BX_get_prompt_by_refnum;
  global_table[QUERY_NICK].generic = (void *)null_function; /* DEFUNCT */
  global_table[QUERY_HOST].generic = (void *)null_function; /* DEFUNCT */
  global_table[QUERY_CMD].generic = (void *)null_function;  /* DEFUNCT */
  global_table[GET_TARGET_BY_REFNUM].get_target_by_refnum_slot =
      BX_get_target_by_refnum;
  global_table[GET_TARGET_CMD_BY_REFNUM].get_target_cmd_by_refnum_slot =
      BX_get_target_cmd_by_refnum;
  global_table[GET_WINDOW_TARGET_BY_DESC].get_window_target_by_desc_slot =
      BX_get_window_target_by_desc;
  global_table[IS_CURRENT_CHANNEL].is_current_channel_slot =
      BX_is_current_channel;
  global_table[SET_CURRENT_CHANNEL_BY_REFNUM]
      .set_current_channel_by_refnum_slot = BX_set_current_channel_by_refnum;
  global_table[GET_REFNUM_BY_WINDOW].get_refnum_by_window_slot =
      BX_get_refnum_by_window;
  global_table[IS_BOUND_TO_WINDOW].is_bound_to_window_slot =
      BX_is_bound_to_window;
  global_table[GET_WINDOW_BOUND_CHANNEL].get_window_bound_channel_slot =
      BX_get_window_bound_channel;
  global_table[IS_BOUND_ANYWHERE].is_bound_anywhere_slot = BX_is_bound_anywhere;
  global_table[IS_BOUND].is_bound_slot = BX_is_bound;
  global_table[UNBIND_CHANNEL].unbind_channel_slot = BX_unbind_channel;
  global_table[GET_BOUND_CHANNEL].get_bound_channel_slot = BX_get_bound_channel;
  global_table[SET_WINDOW_SERVER].set_window_server_slot = BX_set_window_server;
  global_table[WINDOW_CHECK_SERVERS].window_check_servers_slot =
      BX_window_check_servers;
  global_table[CHANGE_WINDOW_SERVER].change_window_server_slot =
      BX_change_window_server;
  global_table[SET_LEVEL_BY_REFNUM].set_level_by_refnum_slot =
      BX_set_level_by_refnum;
  global_table[MESSAGE_TO].message_to_slot = BX_message_to;
  global_table[CLEAR_WINDOW].clear_window_slot = BX_clear_window;
  global_table[CLEAR_ALL_WINDOWS].clear_all_windows_slot = BX_clear_all_windows;
  global_table[CLEAR_WINDOW_BY_REFNUM].clear_window_by_refnum_slot =
      BX_clear_window_by_refnum;
  global_table[UNCLEAR_WINDOW_BY_REFNUM].unclear_window_by_refnum_slot =
      BX_unclear_window_by_refnum;
  global_table[SET_SCROLL_LINES].set_scroll_lines_slot = BX_set_scroll_lines;
  global_table[SET_CONTINUED_LINES].set_continued_lines_slot =
      BX_set_continued_lines;
  global_table[CURRENT_REFNUM].current_refnum_slot = BX_current_refnum;
  global_table[NUMBER_OF_WINDOWS_ON_SCREEN].number_of_windows_on_screen_slot =
      BX_number_of_windows_on_screen;
  global_table[SET_SCROLLBACK_SIZE].set_scrollback_size_slot =
      BX_set_scrollback_size;
  global_table[IS_WINDOW_NAME_UNIQUE].is_window_name_unique_slot =
      BX_is_window_name_unique;
  global_table[GET_NICKLIST_BY_WINDOW].get_nicklist_by_window_slot =
      BX_get_nicklist_by_window;
  global_table[SCROLLBACK_BACKWARDS_LINES].scrollback_backwards_lines_slot =
      BX_scrollback_backwards_lines;
  global_table[SCROLLBACK_FORWARDS_LINES].scrollback_forwards_lines_slot =
      BX_scrollback_forwards_lines;
  global_table[SCROLLBACK_FORWARDS].scrollback_forwards_slot =
      BX_scrollback_forwards;
  global_table[SCROLLBACK_BACKWARDS].scrollback_backwards_slot =
      BX_scrollback_backwards;
  global_table[SCROLLBACK_END].scrollback_end_slot = BX_scrollback_end;
  global_table[SCROLLBACK_START].scrollback_start_slot = BX_scrollback_start;
  global_table[SET_HOLD_MODE].set_hold_mode_slot = BX_set_hold_mode;
  global_table[UNHOLD_WINDOWS].unhold_windows_slot = BX_unhold_windows;
  global_table[FUNC_UNSTOP_ALL_WINDOWS].func_unstop_all_windows_slot =
      BX_unstop_all_windows;
  global_table[RESET_LINE_CNT].reset_line_cnt_slot = BX_reset_line_cnt;
  global_table[FUNC_TOGGLE_STOP_SCREEN].func_toggle_stop_screen_slot =
      BX_toggle_stop_screen;
  global_table[FLUSH_EVERYTHING_BEING_HELD].flush_everything_being_held_slot =
      BX_flush_everything_being_held;
  global_table[UNHOLD_A_WINDOW].unhold_a_window_slot = BX_unhold_a_window;
  global_table[RECALCULATE_WINDOW_CURSOR].recalculate_window_cursor_slot =
      BX_recalculate_window_cursor;
  global_table[MAKE_WINDOW_CURRENT].make_window_current_slot =
      BX_make_window_current;
  global_table[CLEAR_SCROLLBACK].clear_scrollback_slot = BX_clear_scrollback;

  global_table[RESET_DISPLAY_TARGET].reset_display_target_slot =
      BX_reset_display_target;
  global_table[SET_DISPLAY_TARGET].set_display_target_slot =
      BX_set_display_target;
  global_table[SAVE_DISPLAY_TARGET].save_display_target_slot =
      BX_save_display_target;
  global_table[RESTORE_DISPLAY_TARGET].restore_display_target_slot =
      BX_restore_display_target;

  global_table[MY_ENCRYPT].my_encrypt_slot = BX_my_encrypt;
  global_table[MY_DECRYPT].my_decrypt_slot = BX_my_decrypt;
  global_table[PREPARE_COMMAND].prepare_command_slot = BX_prepare_command;
  global_table[CONVERT_OUTPUT_FORMAT].convert_output_format_slot =
      BX_convert_output_format;
  global_table[BREAKARGS].breakargs_slot = BX_BreakArgs;
  global_table[PASTEARGS].pasteargs_slot = BX_PasteArgs;
  global_table[USERAGE].userage_slot = BX_userage;
  global_table[SEND_TEXT].send_text_slot = BX_send_text;
  global_table[SPLIT_CTCP].split_ctcp_slot = BX_split_CTCP;
  global_table[RANDOM_STR].random_str_slot = BX_random_str;
  global_table[DCC_PRINTF].dcc_printf_slot = BX_dcc_printf;
  global_table[ADD_TO_LOG].add_to_log_slot = BX_add_to_log;
  global_table[SET_LASTLOG_MSG_LEVEL].set_lastlog_msg_level_slot =
      BX_set_lastlog_msg_level;

/* module.c */
#ifdef WANT_DLL
  global_table[REMOVE_MODULE_PROC].remove_module_proc_slot =
      BX_remove_module_proc;
  global_table[ADD_MODULE_PROC].add_module_proc_slot = BX_add_module_proc;
#else
  global_table[REMOVE_MODULE_PROC].remove_module_proc_slot = null_function;
  global_table[ADD_MODULE_PROC].add_module_proc_slot = null_function;
#endif

  /* this one should be differant. */
  global_table[FUNC_LOAD].func_load_slot = BX_load;

  global_table[HOOK].hook_slot = BX_do_hook;

  /* irc.c */
  global_table[UPDATE_CLOCK].update_clock_slot = BX_update_clock;
  global_table[IRC_IO_FUNC].irc_io_func_slot = BX_io;
  global_table[IRC_EXIT_FUNC].irc_exit_func_slot = BX_irc_exit;

  /* alias.c */
  global_table[LOCK_STACK_FRAME].lock_stack_frame_slot = BX_lock_stack_frame;
  global_table[UNLOCK_STACK_FRAME].unlock_stack_frame_slot =
      BX_unlock_stack_frame;

  /* input.c */
  global_table[FUNC_UPDATE_INPUT].func_update_input_slot = BX_update_input;
  global_table[CURSOR_TO_INPUT].cursor_to_input_slot = BX_cursor_to_input;
  global_table[SET_INPUT].set_input_slot = BX_set_input;
  global_table[GET_INPUT].get_input_slot = BX_get_input;
  global_table[SET_INPUT_PROMPT].set_input_prompt_slot = BX_set_input_prompt;
  global_table[GET_INPUT_PROMPT].get_input_prompt_slot = BX_get_input_prompt;
  global_table[ADDTABKEY].addtabkey_slot = BX_addtabkey;
  global_table[GETTABKEY].gettabkey_slot = BX_gettabkey;
  global_table[GETNEXTNICK].getnextnick_slot = BX_getnextnick;
  global_table[GETCHANNICK].getchannick_slot = BX_getchannick;
  global_table[LOOKUP_NICKCOMPLETION].lookup_nickcompletion_slot =
      BX_lookup_nickcompletion;
  global_table[ADD_COMPLETION_TYPE].add_completion_type_slot =
      BX_add_completion_type;

  /* names.c */
  global_table[IS_CHANOP].is_chanop_slot = BX_is_chanop;
  global_table[IS_HALFOP].is_halfop_slot = BX_is_halfop;
  global_table[IS_CHANNEL].is_channel_slot = BX_is_channel;
  global_table[MAKE_CHANNEL].generic =
      (void *)BX_make_channel; /* this is really in misc.c */
  global_table[IM_ON_CHANNEL].im_on_channel_slot = BX_im_on_channel;
  global_table[IS_ON_CHANNEL].is_on_channel_slot = BX_is_on_channel;
  global_table[ADD_CHANNEL].add_channel_slot = BX_add_channel;
  global_table[ADD_TO_CHANNEL].add_to_channel_slot = BX_add_to_channel;
  global_table[GET_CHANNEL_KEY].get_channel_key_slot = BX_get_channel_key;
  global_table[FUNC_RECREATE_MODE].func_recreate_mode_slot = BX_recreate_mode;
#ifdef COMPRESS_MODES
  global_table[FUNC_COMPRESS_MODES].func_compress_modes_slot =
      BX_do_compress_modes;
#endif
  global_table[FUNC_GOT_OPS].func_got_ops_slot = BX_got_ops;
  global_table[GET_CHANNEL_BANS].get_channel_bans_slot = BX_get_channel_bans;
  global_table[GET_CHANNEL_MODE].get_channel_mode_slot = BX_get_channel_mode;
  global_table[CLEAR_BANS].clear_bans_slot = BX_clear_bans;
  global_table[REMOVE_CHANNEL].remove_channel_slot = BX_remove_channel;
  global_table[REMOVE_FROM_CHANNEL].remove_from_channel_slot =
      BX_remove_from_channel;
  global_table[RENAME_NICK].rename_nick_slot = BX_rename_nick;
  global_table[GET_CHANNEL_OPER].get_channel_oper_slot = BX_get_channel_oper;
  global_table[GET_CHANNEL_HALFOP].get_channel_halfop_slot =
      BX_get_channel_halfop;
  global_table[FETCH_USERHOST].fetch_userhost_slot = BX_fetch_userhost;
  global_table[GET_CHANNEL_VOICE].get_channel_voice_slot = BX_get_channel_voice;
  global_table[CREATE_CHANNEL_LIST].create_channel_list_slot =
      BX_create_channel_list;
  global_table[FLUSH_CHANNEL_STATS].flush_channel_stats_slot =
      BX_flush_channel_stats;
  global_table[LOOKUP_CHANNEL].lookup_channel_slot = BX_lookup_channel;

  /* hash.c */
  global_table[FIND_NICKLIST_IN_CHANNELLIST].find_nicklist_in_channellist_slot =
      BX_find_nicklist_in_channellist;
  global_table[ADD_NICKLIST_TO_CHANNELLIST].add_nicklist_to_channellist_slot =
      BX_add_nicklist_to_channellist;
  global_table[NEXT_NICKLIST].next_nicklist_slot = BX_next_nicklist;
  global_table[NEXT_NAMELIST].next_namelist_slot = BX_next_namelist;
  global_table[ADD_NAME_TO_GENERICLIST].add_name_to_genericlist_slot =
      BX_add_name_to_genericlist;
  global_table[FIND_NAME_IN_GENERICLIST].find_name_in_genericlist_slot =
      BX_find_name_in_genericlist;
  global_table[ADD_WHOWAS_USERHOST_CHANNEL].add_whowas_userhost_channel_slot =
      BX_add_whowas_userhost_channel;
  global_table[FIND_USERHOST_CHANNEL].find_userhost_channel_slot =
      BX_find_userhost_channel;
  global_table[NEXT_USERHOST].next_userhost_slot = BX_next_userhost;
  global_table[SORTED_NICKLIST].sorted_nicklist_slot = BX_sorted_nicklist;
  global_table[CLEAR_SORTED_NICKLIST].clear_sorted_nicklist_slot =
      BX_clear_sorted_nicklist;
  global_table[ADD_NAME_TO_FLOODLIST].add_name_to_floodlist_slot =
      BX_add_name_to_floodlist;
  global_table[FIND_NAME_IN_FLOODLIST].find_name_in_floodlist_slot =
      BX_find_name_in_floodlist;
  global_table[REMOVE_OLDEST_WHOWAS_HASHLIST]
      .remove_oldest_whowas_hashlist_slot = BX_remove_oldest_whowas_hashlist;

  /* vars.h cset.c fset.c */
  global_table[FGET_STRING_VAR].fget_string_var_slot = BX_fget_string_var;
  global_table[FSET_STRING_VAR].fset_string_var_slot = BX_fset_string_var;
  global_table[GET_WSET_STRING_VAR].get_wset_string_var_slot =
      BX_get_wset_string_var;
  global_table[SET_WSET_STRING_VAR].set_wset_string_var_slot =
      BX_set_wset_string_var;
  global_table[SET_CSET_INT_VAR].set_cset_int_var_slot = BX_set_cset_int_var;
  global_table[GET_CSET_INT_VAR].get_cset_int_var_slot = BX_get_cset_int_var;
  global_table[SET_CSET_STR_VAR].set_cset_str_var_slot = BX_set_cset_str_var;
  global_table[GET_CSET_STR_VAR].get_cset_str_var_slot = BX_get_cset_str_var;
#ifdef WANT_DLL
  global_table[GET_DLLINT_VAR].get_dllint_var_slot = BX_get_dllint_var;
  global_table[SET_DLLINT_VAR].set_dllint_var_slot = BX_set_dllint_var;
  global_table[GET_DLLSTRING_VAR].get_dllstring_var_slot = BX_get_dllstring_var;
  global_table[SET_DLLSTRING_VAR].set_dllstring_var_slot = BX_set_dllstring_var;
  global_table[SAVE_DLLVAR].save_dllvar_slot = BX_save_dllvar;
#else
  global_table[GET_DLLINT_VAR].get_dllint_var_slot = null_function;
  global_table[SET_DLLINT_VAR].set_dllint_var_slot = null_function;
  global_table[GET_DLLSTRING_VAR].get_dllstring_var_slot = null_function;
  global_table[SET_DLLSTRING_VAR].set_dllstring_var_slot = null_function;
  global_table[SAVE_DLLVAR].save_dllvar_slot = null_function;
#endif
  global_table[GET_INT_VAR].get_int_var_slot = BX_get_int_var;
  global_table[SET_INT_VAR].set_int_var_slot = BX_set_int_var;
  global_table[GET_STRING_VAR].get_string_var_slot = BX_get_string_var;
  global_table[SET_STRING_VAR].set_string_var_slot = BX_set_string_var;

  /* timer.c */
  global_table[ADD_TIMER].add_timer_slot = BX_add_timer;
  global_table[DELETE_TIMER].delete_timer_slot = BX_delete_timer;
  global_table[DELETE_ALL_TIMERS].delete_all_timers_slot = BX_delete_all_timers;

  /* socket functions */
  global_table[ADD_SOCKETREAD].add_socketread_slot = BX_add_socketread;
  global_table[ADD_SOCKETTIMEOUT].add_sockettimeout_slot = BX_add_sockettimeout;
  global_table[CLOSE_SOCKETREAD].close_socketread_slot = BX_close_socketread;
  global_table[GET_SOCKET].get_socket_slot = BX_get_socket;
  global_table[SET_SOCKETFLAGS].set_socketflags_slot = BX_set_socketflags;
  global_table[GET_SOCKETFLAGS].get_socketflags_slot = BX_get_socketflags;
  global_table[GET_SOCKETINFO].get_socketinfo_slot = BX_get_socketinfo;
  global_table[SET_SOCKETINFO].set_socketinfo_slot = BX_set_socketinfo;
  global_table[SET_SOCKETWRITE].set_socketwrite_slot = BX_set_socketwrite;
  global_table[CHECK_SOCKET].check_socket_slot = BX_check_socket;
  global_table[READ_SOCKETS].read_sockets_slot = BX_read_sockets;
  global_table[WRITE_SOCKETS].write_sockets_slot = BX_write_sockets;
  global_table[GET_MAX_FD].get_max_fd_slot = BX_get_max_fd;
  global_table[NEW_CLOSE].new_close_slot = BX_new_close;
  global_table[NEW_OPEN].new_open_slot = BX_new_open;
  global_table[DGETS].dgets_slot = BX_dgets;

  /* network.c */
  global_table[CONNECT_BY_NUMBER].connect_by_number_slot = BX_connect_by_number;
  global_table[RESOLV].resolv_slot = BX_lookup_host;
  global_table[LOOKUP_HOST].lookup_host_slot = BX_lookup_host;
  global_table[LOOKUP_IP].lookup_ip_slot = BX_host_to_ip;
  global_table[HOST_TO_IP].host_to_ip_slot = BX_host_to_ip;
  global_table[IP_TO_HOST].ip_to_host_slot = BX_ip_to_host;
  global_table[ONE_TO_ANOTHER].one_to_another_slot = BX_one_to_another;
  global_table[SET_BLOCKING].set_blocking_slot = BX_set_blocking;
  global_table[SET_NON_BLOCKING].set_non_blocking_slot = BX_set_non_blocking;

  /* flood.c */
  global_table[IS_OTHER_FLOOD].is_other_flood_slot = BX_is_other_flood;
  global_table[CHECK_FLOODING].check_flooding_slot = BX_check_flooding;
  global_table[FLOOD_PROT].flood_prot_slot = BX_flood_prot;

  /* alias.c */
  global_table[NEXT_UNIT].next_unit_slot = BX_next_unit;
  global_table[EXPAND_ALIAS].expand_alias_slot = BX_expand_alias;
  global_table[PARSE_INLINE].parse_inline_slot = BX_parse_inline;
  global_table[ALIAS_SPECIAL_CHAR].alias_special_char_slot =
      BX_alias_special_char;
  global_table[PARSE_LINE].parse_line_slot = BX_parse_line;
  global_table[PARSE_COMMAND_FUNC].parse_command_func_slot = BX_parse_command;
  global_table[MAKE_LOCAL_STACK].make_local_stack_slot = BX_make_local_stack;
  global_table[DESTROY_LOCAL_STACK].destroy_local_stack_slot =
      BX_destroy_local_stack;

  /* dcc.c */
  global_table[DCC_CREATE_FUNC].dcc_create_func_slot = BX_dcc_create;
  global_table[FIND_DCC_FUNC].find_dcc_func_slot = BX_find_dcc;
  global_table[ERASE_DCC_INFO].erase_dcc_info_slot = BX_erase_dcc_info;
  global_table[ADD_DCC_BIND].add_dcc_bind_slot = BX_add_dcc_bind;
  global_table[REMOVE_DCC_BIND].remove_dcc_bind_slot = BX_remove_dcc_bind;
  global_table[REMOVE_ALL_DCC_BINDS].remove_all_dcc_binds_slot =
      BX_remove_all_dcc_binds;
  global_table[GET_ACTIVE_COUNT].get_active_count_slot = BX_get_active_count;
  global_table[DCC_FILESEND].dcc_filesend_slot = BX_dcc_filesend;
  global_table[DCC_RESEND].dcc_resend_slot = BX_dcc_resend;
  global_table[DCC_CHAT_SOCKETREAD].dcc_chat_socketread_slot =
      BX_dcc_chat_socketread;
  global_table[DCC_SEND_SOCKETREAD].dcc_send_socketread_slot =
      BX_dcc_send_socketread;

  /* cdcc.c */
  global_table[GET_NUM_QUEUE].get_num_queue_slot = BX_get_num_queue;
  global_table[ADD_TO_QUEUE].add_to_queue_slot = BX_add_to_queue;

  /* who.c */
  global_table[WHOBASE].whobase_slot = BX_whobase;
  global_table[ISONBASE].isonbase_slot = BX_isonbase;
  global_table[USERHOSTBASE].userhostbase_slot = BX_userhostbase;

  global_table[SERV_OPEN_FUNC].serv_open_func_slot = &serv_open_func;
  global_table[SERV_OUTPUT_FUNC].serv_output_func_slot = &serv_output_func;
  global_table[SERV_INPUT_FUNC].serv_input_func_slot = &serv_input_func;
  global_table[SERV_CLOSE_FUNC].serv_close_func_slot = &serv_close_func;
  global_table[DEFAULT_OUTPUT_FUNCTION].default_output_function_slot =
      default_output_function;
  global_table[DEFAULT_STATUS_OUTPUT_FUNCTION]
      .default_status_output_function_slot = &default_status_output_function;

  /* important variables */
  static char *nickname_ptr = nickname;
  static const char *irc_version_ptr = irc_version;
  global_table[NICKNAME].nickname_slot = &nickname_ptr;
  global_table[IRC_VERSION].irc_version_slot = (char **)&irc_version_ptr;
  global_table[FROM_SERVER].from_server_slot = &from_server;
  global_table[CONNECTED_TO_SERVER].connected_to_server_slot =
      &connected_to_server;
  global_table[PRIMARY_SERVER].primary_server_slot = &primary_server;
  global_table[PARSING_SERVER_INDEX].parsing_server_index_slot =
      &parsing_server_index;
  global_table[NOW].now_slot = &now;
  global_table[START_TIME].start_time_slot = &start_time;
  global_table[IDLE_TIME].idle_time_slot = &idle_time;

  global_table[LOADING_GLOBAL].loading_global_slot = &loading_global;

  global_table[TARGET_WINDOW].target_window_slot = &target_window;
  global_table[CURRENT_WINDOW].current_window_slot = &current_window;
  global_table[INVISIBLE_LIST].invisible_list_slot = &invisible_list;
  global_table[MAIN_SCREEN].main_screen_slot = &main_screen;
  global_table[LAST_INPUT_SCREEN].last_input_screen_slot = &last_input_screen;
  global_table[OUTPUT_SCREEN].output_screen_slot = &output_screen;
  global_table[SCREEN_LIST].screen_list_slot = &screen_list;
  global_table[DOING_NOTICE].doing_notice_slot = &doing_notice;

  global_table[IRCLOG_FP].irclog_fp_slot = &irclog_fp;
  global_table[WINDOW_DISPLAY].window_display_slot = (int *)&window_display;
  global_table[STATUS_UPDATE_FLAG].status_update_flag_slot =
      &status_update_flag;
  global_table[TABKEY_ARRAY].tabkey_array_slot = &tabkey_array;
  global_table[AUTOREPLY_ARRAY].autoreply_array_slot = &autoreply_array;
  global_table[IDENTD_SOCKET].identd_socket_slot = &identd;

#ifdef WANT_TCL
  global_table[VAR_TCL_INTERP].var_tcl_interp_slot = tcl_interp;
#endif

#ifdef GUI
  global_table[LASTCLICKLINEDATA].lastclicklinedata_slot = &lastclicklinedata;
  global_table[CONTEXTX].contextx_slot = &contextx;
  global_table[CONTEXTY].contexty_slot = &contexty;
  global_table[GUIIPC].guiipc_slot = &(guiipc[1]);
  global_table[GUI_MUTEX_LOCK].gui_mutex_lock_slot = BX_gui_mutex_lock;
  global_table[GUI_MUTEX_UNLOCK].gui_mutex_unlock_slot = BX_gui_mutex_unlock;
#else
  global_table[GUI_MUTEX_LOCK].gui_mutex_lock_slot = null_function;
  global_table[GUI_MUTEX_UNLOCK].gui_mutex_unlock_slot = null_function;
#endif
  /* commands.c */
  global_table[FIND_COMMAND_FUNC].find_command_func_slot = BX_find_command;

#ifdef MEM_DEBUG
  {
    int i;
    for (i = 0; i < NUMBER_OF_GLOBAL_FUNCTIONS; i++)
      if (global_table[i].generic == NULL)
        put_it("global table %d is NULL", i);
  }
#endif
}

int BX_check_module_version(unsigned long number) {
  if (number != MODULE_VERSION)
    return 0;
  return 1;
}

#ifdef WANT_DLL
IrcCommandDll *find_dll_command(const char *com, int *cnt) {
  const size_t len = com ? strlen(com) : 0;
  IrcCommandDll *first_match = NULL;

  *cnt = 0;

  if (len) {
    IrcCommandDll *cmd;

    for (cmd = dll_commands; cmd; cmd = cmd->next) {
      if (!my_strnicmp(com, cmd->name, len)) {
        if (!first_match)
          first_match = cmd;
        (*cnt)++;
      }
    }

    if (first_match && strlen(first_match->name) == len)
      *cnt *= -1;
  }

  return first_match;
}

static IrcVariableDll *lookup_dllvar(char *name) {
  IrcVariableDll *dll = NULL;

  if (name)
    dll = (IrcVariableDll *)find_in_list((List **)&dll_variable, name, 0);

  return dll;
}

char *BX_get_dllstring_var(char *typestr) {
  IrcVariableDll *dll = lookup_dllvar(typestr);
  return dll ? dll->string : NULL;
}

int BX_get_dllint_var(char *typestr) {
  IrcVariableDll *dll = lookup_dllvar(typestr);
  return dll ? dll->integer : -1;
}

void BX_set_dllstring_var(char *typestr, char *string) {
  IrcVariableDll *dll = lookup_dllvar(typestr);

  if (dll) {
    if (string)
      malloc_strcpy(&dll->string, string);
    else
      new_free(&dll->string);
  }
}

void BX_set_dllint_var(char *typestr, unsigned int value) {
  IrcVariableDll *dll = lookup_dllvar(typestr);

  if (dll) {
    dll->integer = value;
  }
}

void BX_save_dllvar(FILE *fp, char *var) {
  IrcVariableDll *dll = lookup_dllvar(var);

  if (dll) {
    switch (dll->type) {
    case BOOL_TYPE_VAR:
      fprintf(fp, "SET %s %s\n", dll->name, dll->integer ? "ON" : "OFF");
      break;
    case CHAR_TYPE_VAR:
      fprintf(fp, "SET %s %c\n", dll->name, dll->integer);
      break;
    case INT_TYPE_VAR:
      fprintf(fp, "SET %s %d\n", dll->name, dll->integer);
      break;
    case STR_TYPE_VAR:
      if (dll->string)
        fprintf(fp, "SET %s %s\n", dll->name, dll->string);
      else
        fprintf(fp, "SET -%s\n", dll->name);
      break;
    }
  }
}

BUILT_IN_COMMAND(dll_load) {
#if defined(HPUX) /* 	HP machines */
  shl_t handle = NULL;
#elif defined(__EMX__)
  ULONG ulerror;
  HMODULE handle;
#elif defined(WINNT)
  HINSTANCE handle;
#else /*		linux SunOS AIX etc */
  void *handle = NULL;
#endif

  char *filename = NULL;
  Irc_PackageInitProc *proc1Ptr;
  Irc_PackageVersionProc *proc2Ptr;
  char *f, *p, *procname = NULL;
  int code = 0;

  if (command) {
    if (install_pack) {
      Packages *pkg = install_pack;
      List *pk;
      for (; pkg; pkg = pkg->next)
        put_it("DLL [%s%s%s] installed", pkg->name,
               pkg->version ? space : empty_string,
               pkg->version ? pkg->version : empty_string);
      for (pk = (List *)dll_commands; pk; pk = pk->next)
        put_it("\t%10s\t%s", "Command", pk->name);
      for (pk = (List *)dll_functions; pk; pk = pk->next)
        put_it("\t%10s\t%s", "Alias", pk->name);
      for (pk = (List *)dll_ctcp; pk; pk = pk->next)
        put_it("\t%10s\t%s", "Ctcp", pk->name);
      for (pk = (List *)dll_variable; pk; pk = pk->next)
        put_it("\t%10s\t%s", "Variable", pk->name);
      for (pk = (List *)dll_window; pk; pk = pk->next)
        put_it("\t%10s\t %s", "Window", pk->name);
    } else
      bitchsay("No modules loaded");
    return;
  }
  if (!args || !*args)
    return;

  filename = next_arg(args, &args);
  f = expand_twiddle(filename);

  if ((p = strrchr(filename, '/')))
    p++;
  else {
    new_free(&f);
    if (!(p = path_search(filename, PLUGINDIR)))
      if (!(p = path_search(filename, get_string_var(LOAD_PATH_VAR)))) {
        char file_buf[BIG_BUFFER_SIZE];
        strcpy(file_buf, filename);
        strcat(file_buf, SHLIB_SUFFIX);
        if (!(p = path_search(file_buf, get_string_var(LOAD_PATH_VAR))))
          if (!(p = path_search(file_buf, PLUGINDIR)))
            p = filename;
      }
    f = expand_twiddle(p);
    p = filename;
  }

  procname = m_strdup(p);
  if ((p = strchr(procname, '.')))
    *p = 0;

  p = procname;
  *p = toupper((unsigned char)*p);
  p++;
  while (*p) {
    *p = tolower((unsigned char)*p);
    p++;
  }

  if (find_in_list((List **)&install_pack, procname, 0)) {
    bitchsay("Module [%s] Already installed", procname);
    new_free(&f);
    new_free(&procname);
    return;
  }
  malloc_strcat(&procname, "_Init");

#if defined(HPUX)
  handle = shl_load(f, BIND_IMMEDIATE, 0L);
#elif defined(__osf1__)
  handle = dlopen(f, RTLD_NOW);
#elif defined(__EMX__)
  malloc_strcat(&f, ".dll");
  convert_dos(f);
  ulerror = DosLoadModule(NULL, 0, f, &handle);
#elif defined(WINNT)
  malloc_strcat(&f, ".dll");
  convert_dos(f);
  handle = LoadLibrary(f);
#else
  handle = dlopen(f, RTLD_NOW | RTLD_GLOBAL);
#endif
#if defined(__EMX__)
  if (ulerror)
#else
  if (handle == NULL)
#endif
  {
#if defined(__EMX__)
    bitchsay("couldn't load file: DosLoadModule() failed %d", ulerror);
#elif defined(WINNT)
    bitchsay("could't load file %s", f);
#else
    bitchsay("couldn't load file: %s", dlerror());
#endif
    new_free(&procname);
    new_free(&f);
    return;
  }

#if defined(HPUX)
  if (!shl_findsym(&handle, procname, (short)TYPE_PROCEDURE, (void *)proc1Ptr))
#elif defined(__EMX__)
  if (DosQueryProcAddr(handle, 0, procname, (PFN *)&proc1Ptr))
#elif defined(WINNT)
  if (!(proc1Ptr = (Irc_PackageInitProc *)GetProcAddress(handle, procname)))
#else
  if (!(proc1Ptr = (Irc_PackageInitProc *)dlsym(handle, (char *)procname)))
#endif
    bitchsay("Unsuccessful module load [%s]", procname);
  else
    code = (proc1Ptr)(&dll_commands, global_table);

  if (!code && proc1Ptr) {
    Packages *new;
    new = (Packages *)new_malloc(sizeof(Packages));
    new->name = m_strdup(procname);
    new->handle = handle;
    new->major = bitchx_numver / 10000;
    new->minor = (bitchx_numver / 100) % 100;

    if ((p = strrchr(new->name, '_')))
      *p = 0;
    p = m_sprintf("%s_Version", new->name);
#if defined(__EMX__)
    if (!DosQueryProcAddr(handle, 0, p, (PFN *)&proc2Ptr))
#elif defined(WINNT)
    if ((proc2Ptr = (Irc_PackageVersionProc *)GetProcAddress(handle, p)))
#elif defined(HPUX)
    if (shl_findsym(&handle, p, (short)TYPE_PROCEDURE, (void *)proc2Ptr))
#else
    if ((proc2Ptr = (Irc_PackageVersionProc *)dlsym(handle, p)))
#endif
      new->version = m_strdup(((proc2Ptr)(&dll_commands)));
    new_free(&p);

    if ((p = strrchr(new->name, '_')))
      *p = 0;
    p = m_sprintf("%s_Cleanup", new->name);
#if defined(__EMX__)
    if (!DosQueryProcAddr(handle, 0, p, (PFN *)&proc1Ptr))
#elif defined(WINNT)
    if ((proc1Ptr = (Irc_PackageInitProc *)GetProcAddress(handle, p)))
#elif defined(HPUX)
    if (shl_findsym(&handle, p, (short)TYPE_PROCEDURE, (void *)proc1Ptr))
#else
    if ((proc1Ptr = (Irc_PackageInitProc *)dlsym(handle, p)))
#endif
      new->cleanup = proc1Ptr;

    new_free(&p);
    if ((p = strrchr(new->name, '_')))
      *p = 0;
    p = m_sprintf("%s_Lock", new->name);
#if defined(__EMX__)
    if (!DosQueryProcAddr(handle, 0, p, (PFN *)&proc1Ptr))
#elif defined(WINNT)
    if ((proc1Ptr = (Irc_PackageInitProc *)GetProcAddress(handle, p)))
#elif defined(HPUX)
    if (shl_findsym(&handle, p, (short)TYPE_PROCEDURE, (void *)proc1Ptr))
#else
    if ((proc1Ptr = (Irc_PackageInitProc *)dlsym(handle, p)))
#endif
      new->lock = 1;
    new_free(&p);
    add_to_list((List **)&install_pack, (List *)new);
  } else {
    if (code == INVALID_MODVERSION)
      bitchsay("Module ABI version is wrong for [%s].  This likely means that "
               "the module needs to be recompiled.",
               procname);
    else
      bitchsay("Error initializing module [%s:%d]", procname, code);
    if (handle)
#if defined(__EMX__)
      DosFreeModule(handle);
#elif defined(WINNT)
      FreeLibrary(handle);
#elif defined(HPUX)
      shl_unload(handle);
#else
      dlclose(handle);
#endif
  }
  new_free(&procname);
  new_free(&f);
}

Packages *find_module(char *name) {
  Packages *new = NULL;
  if (name)
    new = (Packages *)find_in_list((List **)&install_pack, name, 0);
  return new;
}

#define RAWHASH_SIZE 20

HashEntry RawHash[RAWHASH_SIZE] = {{NULL, 0, 0}};

RawDll *find_raw_proc(char *comm, char **ArgList __attribute__((unused))) {
  RawDll *tmp = NULL;
  if ((tmp =
           (RawDll *)find_name_in_genericlist(comm, RawHash, RAWHASH_SIZE, 0)))
    return tmp;
  return NULL;
}

int BX_add_module_proc(unsigned int mod_type, char *modname, char *procname,
                       char *desc, int id, int flag, void *func1, void *func2) {
  switch (mod_type) {
  case COMMAND_PROC: {
    IrcCommandDll *new;
    new = (IrcCommandDll *)new_malloc(sizeof(IrcCommandDll));
    new->name = m_strdup(procname);
    if (desc)
      new->server_func = m_strdup(desc);
    new->func = func1;
    if (func2)
      new->help = m_strdup((char *)func2);
    new->module = m_strdup(modname);
    add_to_list((List **)&dll_commands, (List *)new);
    break;
  }
  case WINDOW_PROC: {
    WindowDll *new;
    new = (WindowDll *)new_malloc(sizeof(WindowDll));
    new->name = m_strdup(procname);
    if (desc)
      new->help = m_strdup(desc);
    new->func = func1;
    new->module = m_strdup(modname);
    add_to_list((List **)&dll_window, (List *)new);
    break;
  }
  case OUTPUT_PROC: {
    Screen *screen;
    Window *window;
    if (func1) {
      default_output_function = func1;
      for (screen = screen_list; screen; screen = screen->next) {
        for (window = screen->window_list; window; window = window->next)
          window->output_func = func1;
      }
    }
    if (func2) {
      default_status_output_function = func2;
      for (screen = screen_list; screen; screen = screen->next) {
        for (window = screen->window_list; window; window = window->next)
          window->status_output_func = func2;
      }
    }
    break;
  }
  case ALIAS_PROC: {
    BuiltInDllFunctions *new = NULL;
    new = (BuiltInDllFunctions *)new_malloc(sizeof(BuiltInDllFunctions));
    new->name = m_strdup(procname);
    new->func = func1;
    new->module = m_strdup(modname);
    add_to_list((List **)&dll_functions, (List *)new);
    break;
  }
  case CTCP_PROC: {
    CtcpEntryDll *new = NULL;
    new = (CtcpEntryDll *)new_malloc(sizeof(CtcpEntryDll));
    new->name = m_strdup(procname);
    new->desc = m_strdup(desc);
    new->id = id;
    new->flag = flag;
    new->func = func1;
    new->repl = func2;
    new->module = m_strdup(modname);
    add_to_list((List **)&dll_ctcp, (List *)new);
    break;
  }
  case VAR_PROC: {
    IrcVariableDll *new = NULL;
    new = (IrcVariableDll *)new_malloc(sizeof(IrcVariableDll));
    new->type = id;
    new->integer = flag;
    new->name = m_strdup(procname);
    if (desc)
      new->string = m_strdup(desc);
    new->module = m_strdup(modname);
    new->func = func1;
    add_to_list((List **)&dll_variable, (List *)new);
    break;
  }
  case RAW_PROC: {
    RawDll *raw;
    unsigned long hvalue = hash_nickname(procname, RAWHASH_SIZE);
    raw = (RawDll *)new_malloc(sizeof(RawDll));
    raw->next = (RawDll *)RawHash[hvalue].list;
    RawHash[hvalue].list = (void *)raw;
    RawHash[hvalue].links++;
    RawHash[hvalue].hits++;
    raw->name = m_strdup(procname);
    raw->module = m_strdup(modname);
    raw->func = func1;
    break;
  }
  case HOOK_PROC: {
    extern void add_dll_hook(int, int, char *, char *,
                             int (*func1)(int, char *, char **),
                             int (*func2)(char *, char *, char **));
    add_dll_hook(id, flag, desc ? desc : "*", modname, func1, func2);
    break;
  }
  case DCC_PROC: {
    DCC_dllcommands *new = NULL;
    new = (DCC_dllcommands *)new_malloc(sizeof(DCC_dllcommands));
    new->name = m_strdup(procname);
    new->help = m_strdup(desc);
    new->module = m_strdup(modname);
    new->function = func1;
    add_to_list((List **)&dcc_dllcommands, (List *)new);
    break;
  }
  default: {
    if ((mod_type & ~TABLE_PROC) > 0 &&
        (mod_type & ~TABLE_PROC) < NUMBER_OF_GLOBAL_FUNCTIONS)
      global_table[mod_type & ~TABLE_PROC].generic = (void *)func1;
  }
  }
  return 0;
}

typedef struct _list2 {
  struct _list2 *next;
  char *command;
  char *name;
} List2;

static List2 *remove_module(List2 **list, char *name) {
  register List2 *tmp;
  List2 *last;

  last = NULL;
  for (tmp = *list; tmp; tmp = tmp->next) {
    if (tmp->name && !strcasecmp(tmp->name, name)) {
      if (last)
        last->next = tmp->next;
      else
        *list = tmp->next;
      return (tmp);
    }
    last = tmp;
  }
  return NULL;
}

static int cmp_dcc_dllcmd_module(List *node, char *name) {
  const DCC_dllcommands *dllcmd = (DCC_dllcommands *)node;
  return strcasecmp(dllcmd->module, name);
}

int BX_remove_module_proc(unsigned int mod_type, char *modname, char *procname __attribute__((unused)),
                          char *desc __attribute__((unused))) {
  int count = 0;
  switch (mod_type) {
  case COMMAND_PROC: {
    IrcCommandDll *ptr;
    while ((ptr = (IrcCommandDll *)remove_module((List2 **)&dll_commands,
                                                 modname))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free(&ptr->server_func);
      new_free(&ptr->result);
      new_free(&ptr->help);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  case WINDOW_PROC: {
    WindowDll *ptr;
    while ((ptr = (WindowDll *)remove_module((List2 **)&dll_window, modname))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free(&ptr->help);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  case OUTPUT_PROC: {
    Screen *screen;
    Window *window;
    default_output_function = BX_add_to_window;
    for (screen = screen_list; screen; screen = screen->next) {
      for (window = screen->window_list; window; window = window->next)
        window->output_func = BX_add_to_window;
    }
    default_status_output_function = make_status;
    for (screen = screen_list; screen; screen = screen->next) {
      for (window = screen->window_list; window; window = window->next)
        window->status_output_func = make_status;
    }
    count++;
    break;
  }
  case ALIAS_PROC: {
    BuiltInDllFunctions *ptr;
    while ((ptr = (BuiltInDllFunctions *)remove_module((List2 **)&dll_functions,
                                                       modname))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  case CTCP_PROC: {
    CtcpEntryDll *ptr;
    while (
        (ptr = (CtcpEntryDll *)remove_module((List2 **)&dll_ctcp, modname))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free(&ptr->desc);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  case VAR_PROC: {
    IrcVariableDll *ptr;
    while ((ptr = (IrcVariableDll *)remove_module((List2 **)&dll_variable,
                                                  modname))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free(&ptr->string);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  case RAW_PROC: {
    int i;
    RawDll *ptr = NULL;
    for (i = 0; i < RAWHASH_SIZE; i++) {
      while ((ptr = (RawDll *)remove_module((List2 **)&(RawHash[i].list),
                                            modname))) {
        new_free(&ptr->module);
        new_free(&ptr->name);
        new_free((char **)&ptr);
        count++;
      }
    }
    break;
  }
  case HOOK_PROC: {
    extern int remove_dll_hook(char *);
    count = remove_dll_hook(modname);
    break;
  }
  case DCC_PROC: {
    DCC_dllcommands *ptr;
    while ((ptr = (DCC_dllcommands *)remove_from_list_ext(
                (List **)&dcc_dllcommands, modname, cmp_dcc_dllcmd_module))) {
      new_free(&ptr->name);
      new_free(&ptr->module);
      new_free(&ptr->help);
      new_free((char **)&ptr);
      count++;
    }
    break;
  }
  default: {
    if ((mod_type & ~TABLE_PROC) > 0 &&
        (mod_type & ~TABLE_PROC) < NUMBER_OF_GLOBAL_FUNCTIONS) {
      global_table[mod_type & ~TABLE_PROC].generic = NULL;
      count++;
    }
  }
  }
  return count;
}

int remove_package(char *name) {
  Packages *new = NULL;
  if ((new = (Packages *)remove_from_list((List **)&install_pack, name))) {
#if defined(__EMX__)
    DosFreeModule(new->handle);
#elif defined(WINNT)
    FreeLibrary(new->handle);
#elif defined(HPUX)
    shl_unload(new->handle);
#else
    dlclose(new->handle);
#endif
    new_free(&new->name);
    new_free(&new->version);
    new_free((char **)&new);
    return 1;
  }
  return 0;
}

int check_version(unsigned long required) {
  unsigned long major, minor, need_major, need_minor;
  major = bitchx_numver / 10000;
  minor = (bitchx_numver / 100) % 100;
  need_major = required / 10000;
  need_minor = (required / 100) % 100;
  if ((major > need_major) || (major == need_major && minor >= need_minor))
    return 1;
  return INVALID_MODVERSION;
}

BUILT_IN_COMMAND(unload_dll) {
  Packages *new = NULL;
  int success = 0;
  char *name;
  name = next_arg(args, &args);
  if (name && (new = find_module(name))) {
    if (new->cleanup)
      success = (new->cleanup)(&dll_commands, global_table);
    else {
      if (new->lock) {
        bitchsay("Module is locked");
        return;
      }
      success += remove_module_proc(COMMAND_PROC, name, NULL, NULL);
      success += remove_module_proc(ALIAS_PROC, name, NULL, NULL);
      success += remove_module_proc(CTCP_PROC, name, NULL, NULL);
      success += remove_module_proc(VAR_PROC, name, NULL, NULL);
      success += remove_module_proc(HOOK_PROC, name, NULL, NULL);
      success += remove_module_proc(RAW_PROC, name, NULL, NULL);
      success += remove_module_proc(WINDOW_PROC, name, NULL, NULL);
      success += remove_module_proc(OUTPUT_PROC, name, NULL, NULL);
      success += remove_module_proc(DCC_PROC, name, NULL, NULL);
      success += remove_all_dcc_binds(name);
    }
    if (success) {
      remove_package(name);
      put_it("%s", convert_output_format("$G Successfully removed [$0 ($1)]",
                                         "%s %d", name, success));
    } else
      put_it("%s", convert_output_format("$G Unsuccessful module unload", NULL,
                                         NULL));
  } else
    bitchsay("No such module loaded");
}

int add_module(unsigned int mod_type, Function *table, char *modname) {
  Function *p = table;
  int count = 0;

  while (p) {
    add_module_proc(mod_type, modname, p->name, p->desc, p->id, p->flag,
                    p->func1, p->func2);
    p++;
    count++;
  }
  return count;
}
#endif
