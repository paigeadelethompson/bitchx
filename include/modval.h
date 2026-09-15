#ifndef MODVAL_H_
#define MODVAL_H_

/* include this so we have the enum table just in case someone forgets. */

#include "module.h"

#define check_ext_mail_status (global[CHECK_EXT_MAIL_STATUS].check_ext_mail_status_slot)
#define check_ext_mail (global[CHECK_EXT_MAIL].check_ext_mail_slot)





/* 
 * this is a method first used in eggdrop modules.. 
 * A global table of functions is passed into the init function of module,
 * which is then assigned to the value global. This table is then indexed,
 * to access the various functions. What this means to us, is that we no 
 * longer require -rdynamic on the LDFLAGS line, which reduces the size 
 * of the client. This also makes this less compiler/environment dependant,
 * allowing modules to work on more platforms.
 * A Function_ptr *global is required in the module. The second arg to 
 * the init function is used to initialize this table. The table itself is
 * initialized in modules.c. This file should only be included once in the
 * module and also should be the last file included. It should never be 
 * included in the source itself. 
 * As long as we add new functions to the END of the list in module.h then
 * currently compiled modules will continue to function fine. If we change
 * the order of the list however, then BAD things will occur.
 * Copyright Colten Edwards July 1998.
 */

#ifndef BUILT_IN_DLL
#define BUILT_IN_DLL(x) \
	void x (IrcCommandDll *intp __attribute__((unused)), char *command __attribute__((unused)), char *args __attribute__((unused)), char *subargs __attribute__((unused)), char *helparg __attribute__((unused)))
#endif

#if defined(WTERM_C) || defined(STERM_C)
/* If we are building wserv or scr-bx we can't use
 * the global table so we forward to the actual
 * functions instead of throught the global table.
 */
#define set_non_blocking(x) BX_set_non_blocking(x)
#define set_blocking(x) BX_set_blocking(x)
#define ip_to_host(x) BX_ip_to_host(x)
#define host_to_ip(x) BX_host_to_ip(x)
#define connect_by_number(a, b, c, d, e) BX_connect_by_number(a, b, c, d, e)
#define get_int_var(v) BX_get_int_var(v)
#define ircpanic BX_ircpanic
#define my_stricmp strcasecmp
#define my_strnicmp strncasecmp
char *my_ltoa (long);
#else

/*
 * need to undefine these particular defines. Otherwise we can't include
 * them in the table.
 */
#undef new_malloc
#undef new_free
#undef RESIZE
#undef malloc_strcat
#undef malloc_strcpy
#undef m_strdup
#undef m_strcat_ues
#undef m_strndup

#undef MODULENAME

#ifdef MAIN_SOURCE
void init_global_functions(void);
#ifndef __modules_c
extern char *_modname_;
extern BXGlobalEntry *global;
#endif
#else

#ifdef INIT_MODULE
/* only in the first c file do we #define INIT_MODULE */
char *_modname_ = NULL;
BXGlobalEntry *global = NULL;
#undef INIT_MODULE
#else
extern char *_modname_;
extern BXGlobalEntry *global;
#endif

#endif /* MAIN_SOURCE */

#define MODULENAME _modname_

#define check_module_version (global[MODULE_VERSION_CHECK].module_version_check_slot)
#define set_dll_name(x) malloc_strcpy(&_modname_, x)
#define set_global_func(x) global = x;
#define initialize_module(x) { \
		global = global_table; \
		malloc_strcpy(&_modname_, x); \
		if (!check_module_version(MODULE_VERSION)) \
			return INVALID_MODVERSION; \
}

	
#ifndef MAIN_SOURCE
#define empty_string ""
#define space " "
#endif

#ifndef HAVE_VSNPRINTF
#define vsnprintf (global[VSNPRINTF].vsnprintf_slot)
#endif
#ifndef HAVE_SNPRINTF
#define snprintf (global[SNPRINTF].snprintf_slot)
#endif

/* Changed these to cast the function pointer rather than the arguments and result.  The old method wasn't portable to
 * some 64 bit platforms.  Next step - change instances of global[XYZ] to &xyzfunc in the code.
 *
 * Should also think about standardising types (eg Screen instead of struct ScreenStru, get rid of u_char).
 */
/* ircaux.c */
#define new_malloc(x) (global[NEW_MALLOC].new_malloc_slot)((x),MODULENAME, __FILE__,__LINE__)
#define new_free(x) (*(x) = (global[NEW_FREE].new_free_slot)(*(x),MODULENAME, __FILE__,__LINE__))
#define RESIZE(x, y, z) ((x) = (global[NEW_REALLOC].new_realloc_slot)((x), sizeof(y) * (z), MODULENAME, __FILE__, __LINE__))
#define malloc_strcpy(x, y) (global[MALLOC_STRCPY].malloc_strcpy_slot)((x), (y), MODULENAME, __FILE__, __LINE__)
#define malloc_strcat(x, y) (global[MALLOC_STRCAT].malloc_strcat_slot)((x), (y), MODULENAME, __FILE__, __LINE__)
#define malloc_str2cpy (global[MALLOC_STR2CPY].malloc_str2cpy_slot)
#define m_3dup (global[M_3DUP].m_3dup_slot)
#define m_opendup (global[M_OPENDUP].m_opendup_slot)
#define m_s3cat (global[M_S3CAT].m_s3cat_slot)
#define m_s3cat_s (global[M_S3CAT_S].m_s3cat_s_slot)
#define m_3cat (global[M_3CAT].m_3cat_slot)
#define m_2dup (global[M_2DUP].m_2dup_slot)
#define m_e3cat (global[M_E3CAT].m_e3cat_slot)

#define my_stricmp (global[MY_STRICMP].my_stricmp_slot)
#define my_strnicmp (global[MY_STRNICMP].my_strnicmp_slot)

#define my_strnstr (global[MY_STRNSTR].my_strnstr_slot)
#define chop (global[CHOP].chop_slot)
#define strmcpy (global[STRMCPY].strmcpy_slot)
#define strmcat (global[STRMCAT].strmcat_slot)
#define scanstr (global[SCANSTR].scanstr_slot)
#define m_dupchar (global[M_DUPCHAR].m_dupchar_slot)
#define streq (global[STREQ].streq_slot)
#define strieq (global[STRIEQ].strieq_slot)
#define strmopencat (global[STRMOPENCAT].strmopencat_slot)
#define ov_strcpy (global[OV_STRCPY].ov_strcpy_slot)
#define upper (global[UPPER].upper_slot)
#define lower (global[LOWER].lower_slot)
#define stristr (global[STRISTR].stristr_slot)
#define rstristr (global[RSTRISTR].rstristr_slot)
#define word_count (global[WORD_COUNT].word_count_slot)
#define remove_trailing_spaces (global[REMOVE_TRAILING_SPACES].remove_trailing_spaces_slot)
#define expand_twiddle (global[EXPAND_TWIDDLE].expand_twiddle_slot)
#define check_nickname (global[CHECK_NICKNAME].check_nickname_slot)
#define sindex (global[SINDEX].sindex_slot)
#define rsindex (global[RSINDEX].rsindex_slot)
#define is_number (global[ISNUMBER].isnumber_slot)
#define rfgets (global[RFGETS].rfgets_slot)
#define path_search (global[PATH_SEARCH].path_search_slot)
#define double_quote (global[DOUBLE_QUOTE].double_quote_slot)
#define ircpanic (global[IRCPANIC].ircpanic_slot)
#define end_strcmp (global[END_STRCMP].end_strcmp_slot)
#define beep_em (global[BEEP_EM].beep_em_slot)
#define uzfopen (global[UZFOPEN].uzfopen_slot)
#define get_time (global[FUNC_GET_TIME].func_get_time_slot)
#define time_diff (global[TIME_DIFF].time_diff_slot)
#define time_to_next_minute (global[TIME_TO_NEXT_MINUTE].time_to_next_minute_slot)
#define plural (global[PLURAL].plural_slot)
#define my_ctime (global[MY_CTIME].my_ctime_slot)
#define ccspan (global[CCSPAN].ccspan_slot)
#define my_ltoa (global[LTOA].ltoa_slot)
#define strformat (global[STRFORMAT].strformat_slot)
#define MatchingBracket (global[MATCHINGBRACKET].matchingbracket_slot)
#define parse_number (global[PARSE_NUMBER].parse_number_slot)
#define splitw (global[SPLITW].splitw_slot)
#define unsplitw (global[UNSPLITW].unsplitw_slot)
#define check_val (global[CHECK_VAL].check_val_slot)
#define on_off (global[ON_OFF].on_off_slot)
#define strextend (global[STREXTEND].strextend_slot)
#define strfill (global[STRFILL].strfill_slot)
#define empty (global[EMPTY_FUNC].empty_func_slot)
#define remove_brackets (global[REMOVE_BRACKETS].remove_brackets_slot)
#define my_atol (global[MY_ATOL].my_atol_slot)
#define strip_control (global[STRIP_CONTROL].strip_control_slot)
#define figure_out_address (global[FIGURE_OUT_ADDRESS].figure_out_address_slot)
#define strnrchr (global[STRNRCHR].strnrchr_slot)
#define mask_digits (global[MASK_DIGITS].mask_digits_slot)
#define ccscpan (global[CCSPAN].ccspan_slot)
#define charcount (global[CHARCOUNT].charcount_slot)
#define strpcat (global[STRPCAT].strpcat_slot)
#define strcpy_nocolorcodes (global[STRCPY_NOCOLORCODES].strcpy_nocolorcodes_slot)
#define cryptit (global[CRYPTIT].cryptit_slot)
#define stripdev (global[STRIPDEV].stripdev_slot)
#define mangle_line (global[MANGLE_LINE].mangle_line_slot)
#define m_strdup(x) (global[M_STRDUP].m_strdup_slot)((x), MODULENAME, __FILE__, __LINE__)
#define m_strcat_ues(x, y, z) (global[M_STRCAT_UES].m_strcat_ues_slot)((x), (y), (z), MODULENAME, __FILE__, __LINE__)
#define m_strndup(x, y) (global[M_STRNDUP].m_strndup_slot)((x), (y), MODULENAME, __FILE__, __LINE__)
#define malloc_sprintf (global[MALLOC_SPRINTF].malloc_sprintf_slot)
#define m_sprintf (global[M_SPRINTF].m_sprintf_slot)
#define next_arg (global[NEXT_ARG].next_arg_slot)
#define new_next_arg (global[NEW_NEXT_ARG].new_next_arg_slot)
#define new_new_next_arg (global[NEW_NEW_NEXT_ARG].new_new_next_arg_slot)
#define last_arg (global[LAST_ARG].last_arg_slot)
#define next_in_comma_list (global[NEXT_IN_COMMA_LIST].next_in_comma_list_slot)
#define random_number (global[RANDOM_NUMBER].random_number_slot)


/* words.c reg.c */
#define strsearch (global[STRSEARCH].strsearch_slot)
#define move_to_word (global[MOVE_TO_WORD].move_to_word_slot)
#define move_word_rel (global[MOVE_WORD_REL].move_word_rel_slot)
#define extract (global[EXTRACT].extract_slot)
#define extract2 (global[EXTRACT2].extract2_slot)
#define wild_match (global[WILD_MATCH].wild_match_slot)

/* network.c */
#define connect_by_number (global[CONNECT_BY_NUMBER].connect_by_number_slot)
#define lookup_host (global[LOOKUP_HOST].lookup_host_slot)
#define resolv (global[LOOKUP_HOST].lookup_host_slot)
#define host_to_ip (global[HOST_TO_IP].host_to_ip_slot)
#define ip_to_host (global[IP_TO_HOST].ip_to_host_slot)
#define one_to_another (global[ONE_TO_ANOTHER].one_to_another_slot)
#define set_blocking (global[SET_BLOCKING].set_blocking_slot)
#define set_non_blocking (global[SET_NON_BLOCKING].set_non_blocking_slot)


/* list.c */
#define add_to_list (global[ADD_TO_LIST].add_to_list_slot)
#define add_to_list_ext (global[ADD_TO_LIST_EXT].add_to_list_ext_slot)
#define find_in_list (global[FIND_IN_LIST].find_in_list_slot)
#define find_in_list_ext (global[FIND_IN_LIST_EXT].find_in_list_ext_slot)
#define remove_from_list (global[REMOVE_FROM_LIST_].remove_from_list__slot)
#define remove_from_list_ext (global[REMOVE_FROM_LIST_EXT].remove_from_list_ext_slot)
#define removewild_from_list (global[REMOVEWILD_FROM_LIST].removewild_from_list_slot)
#define list_lookup (global[LIST_LOOKUP].list_lookup_slot)
#define list_lookup_ext (global[LIST_LOOKUP_EXT].list_lookup_ext_slot)

/* alist.c */
#define add_to_array (global[ADD_TO_ARRAY].add_to_array_slot)
#define remove_from_array (global[REMOVE_FROM_ARRAY].remove_from_array_slot)
#define array_pop (global[ARRAY_POP].array_pop_slot)

#define remove_all_from_array (global[REMOVE_ALL_FROM_ARRAY].remove_all_from_array_slot)
#define array_lookup (global[ARRAY_LOOKUP].array_lookup_slot)
#define find_array_item (global[FIND_ARRAY_ITEM].find_array_item_slot)

#define find_fixed_array_item (global[FIND_FIXED_ARRAY_ITEM].find_fixed_array_item_slot)

/* output.c */
#define put_it (global[PUT_IT].put_it_slot)
#define bitchsay (global[BITCHSAY].bitchsay_slot)
#define yell (global[YELL].yell_slot)
#define add_to_log (global[ADD_TO_LOG].add_to_log_slot)

#define bsd_glob (global[BSD_GLOB].bsd_glob_slot)
#define bsd_globfree (global[BSD_GLOBFREE].bsd_globfree_slot)

/* misc commands */
#define my_encrypt (global[MY_ENCRYPT].my_encrypt_slot)
#define my_decrypt (global[MY_DECRYPT].my_decrypt_slot)
#define prepare_command (global[PREPARE_COMMAND].prepare_command_slot)
#define convert_output_format (global[CONVERT_OUTPUT_FORMAT].convert_output_format_slot)
#define userage (global[USERAGE].userage_slot)
#define send_text (global[SEND_TEXT].send_text_slot)
/* this needs to be worked out. it's passed in the IrcVariable * to _Init */
#define load (global[FUNC_LOAD].func_load_slot)
#define update_clock (global[UPDATE_CLOCK].update_clock_slot)
#define PasteArgs (global[PASTEARGS].pasteargs_slot)
#define BreakArgs (global[BREAKARGS].breakargs_slot)

#define set_lastlog_msg_level (global[SET_LASTLOG_MSG_LEVEL].set_lastlog_msg_level_slot)
#define split_CTCP (global[SPLIT_CTCP].split_ctcp_slot)
#define random_str (global[RANDOM_STR].random_str_slot)
#define dcc_printf (global[DCC_PRINTF].dcc_printf_slot)

/* screen.c */
#define prepare_display (global[PREPARE_DISPLAY].prepare_display_slot)
#define add_to_window (global[ADD_TO_WINDOW].add_to_window_slot)
#define skip_incoming_mirc (global[SKIP_INCOMING_MIRC].skip_incoming_mirc_slot)
#define add_to_screen (global[ADD_TO_SCREEN].add_to_screen_slot)
#define split_up_line (global[SPLIT_UP_LINE].split_up_line_slot)
#define output_line (global[OUTPUT_LINE].output_line_slot)
#define output_with_count (global[OUTPUT_WITH_COUNT].output_with_count_slot)
#define scroll_window (global[SCROLL_WINDOW].scroll_window_slot)
/* Previous broken definitions - yet it still seemed to work?
#define cursor_not_in_display(x) ((void) (global[CURSOR_IN_DISPLAY].cursor_in_display_slot((Screen *)x)))
#define cursor_in_display(x) ((void) (global[CURSOR_IN_DISPLAY].cursor_in_display_slot((Screen *)x)))
*/
#define cursor_not_in_display (global[CURSOR_NOT_IN_DISPLAY].cursor_not_in_display_slot)
#define cursor_in_display (global[CURSOR_IN_DISPLAY].cursor_in_display_slot)
#define is_cursor_in_display (global[IS_CURSOR_IN_DISPLAY].is_cursor_in_display_slot)
#define repaint_window (global[REPAINT_WINDOW].repaint_window_slot)

#define kill_screen (global[KILL_SCREEN].kill_screen_slot)
#define xterm_settitle (global[XTERM_SETTITLE].xterm_settitle_slot)
#define add_wait_prompt (global[ADD_WAIT_PROMPT].add_wait_prompt_slot)
#define skip_ctl_c_seq (global[SKIP_CTL_C_SEQ].skip_ctl_c_seq_slot)
#define strip_ansi (global[STRIP_ANSI].strip_ansi_slot)
#define create_new_screen (global[CREATE_NEW_SCREEN].create_new_screen_slot)
#define create_additional_screen (global[CREATE_ADDITIONAL_SCREEN].create_additional_screen_slot)


/* window.c */
#define free_formats (global[FREE_FORMATS].free_formats_slot)
#define set_screens_current_window (global[SET_SCREENS_CURRENT_WINDOW].set_screens_current_window_slot)
#define new_window (global[NEW_WINDOW].new_window_slot)
#define delete_window (global[DELETE_WINDOW].delete_window_slot)
#define traverse_all_windows (global[TRAVERSE_ALL_WINDOWS].traverse_all_windows_slot)
#define add_to_invisible_list (global[ADD_TO_INVISIBLE_LIST].add_to_invisible_list_slot)
#define remove_window_from_screen (global[REMOVE_WINDOW_FROM_SCREEN].remove_window_from_screen_slot)
#define recalculate_window_positions (global[RECALCULATE_WINDOW_POSITIONS].recalculate_window_positions_slot)
#define move_window (global[MOVE_WINDOW].move_window_slot)
#define resize_window (global[RESIZE_WINDOW].resize_window_slot)
#define redraw_all_windows (global[REDRAW_ALL_WINDOWS].redraw_all_windows_slot)
#define rebalance_windows (global[REBALANCE_WINDOWS].rebalance_windows_slot)
#define recalculate_windows (global[RECALCULATE_WINDOWS].recalculate_windows_slot)

#define update_all_windows (global[UPDATE_ALL_WINDOWS].update_all_windows_slot)

/* Several of these are never used! */
#define goto_window (global[GOTO_WINDOW].goto_window_slot)
#define hide_window (global[HIDE_BX_WINDOW].hide_bx_window_slot)
#define swap_last_window (global[FUNC_SWAP_LAST_WINDOW].func_swap_last_window_slot)
#define swap_next_window (global[FUNC_SWAP_NEXT_WINDOW].func_swap_next_window_slot)
#define swap_previous_window (global[FUNC_SWAP_PREVIOUS_WINDOW].func_swap_previous_window_slot)
#define show_window (global[SHOW_WINDOW].show_window_slot)
#define get_status_by_refnum (global[GET_STATUS_BY_REFNUM].get_status_by_refnum_slot)
#define get_visible_by_refnum (global[GET_VISIBLE_BY_REFNUM].get_visible_by_refnum_slot)
#define get_window_by_desc (global[GET_WINDOW_BY_DESC].get_window_by_desc_slot)
#define get_window_by_refnum (global[GET_WINDOW_BY_REFNUM].get_window_by_refnum_slot)
#define get_window_by_name (global[GET_WINDOW_BY_NAME].get_window_by_name_slot)
#define next_window (global[FUNC_NEXT_WINDOW].func_next_window_slot)
#define previous_window (global[FUNC_PREVIOUS_WINDOW].func_previous_window_slot)
#define update_window_status (global[UPDATE_WINDOW_STATUS].update_window_status_slot)
#define update_all_status (global[UPDATE_ALL_STATUS].update_all_status_slot)
#define update_window_status_all (global[UPDATE_WINDOW_STATUS_ALL].update_window_status_all_slot)
#define status_update (global[STATUS_UPDATE].status_update_slot)

#define set_prompt_by_refnum (global[SET_PROMPT_BY_REFNUM].set_prompt_by_refnum_slot)
#define get_prompt_by_refnum (global[GET_PROMPT_BY_REFNUM].get_prompt_by_refnum_slot)
#define get_target_by_refnum (global[GET_TARGET_BY_REFNUM].get_target_by_refnum_slot)
#define get_target_cmd_by_refnum (global[GET_TARGET_CMD_BY_REFNUM].get_target_cmd_by_refnum_slot)
#define get_window_target_by_desc (global[GET_WINDOW_TARGET_BY_DESC].get_window_target_by_desc_slot)
#define is_current_channel (global[IS_CURRENT_CHANNEL].is_current_channel_slot)
#define set_current_channel_by_refnum (global[SET_CURRENT_CHANNEL_BY_REFNUM].set_current_channel_by_refnum_slot)
#define get_current_channel_by_refnum (global[GET_CURRENT_CHANNEL_BY_REFNUM].get_current_channel_by_refnum_slot)
#define get_refnum_by_window (global[GET_REFNUM_BY_WINDOW].get_refnum_by_window_slot)
#define is_bound_to_window (global[IS_BOUND_TO_WINDOW].is_bound_to_window_slot)
#define get_window_bound_channel (global[GET_WINDOW_BOUND_CHANNEL].get_window_bound_channel_slot)
#define is_bound_anywhere (global[IS_BOUND_ANYWHERE].is_bound_anywhere_slot)
#define is_bound (global[IS_BOUND].is_bound_slot)
#define unbind_channel (global[UNBIND_CHANNEL].unbind_channel_slot)
#define get_bound_channel (global[GET_BOUND_CHANNEL].get_bound_channel_slot)
#define get_window_server (global[GET_WINDOW_SERVER].get_window_server_slot)
#define set_window_server (global[SET_WINDOW_SERVER].set_window_server_slot)
#define window_check_servers (global[WINDOW_CHECK_SERVERS].window_check_servers_slot)
#define change_window_server (global[CHANGE_WINDOW_SERVER].change_window_server_slot)
#define set_level_by_refnum (global[SET_LEVEL_BY_REFNUM].set_level_by_refnum_slot)
#define message_to (global[MESSAGE_TO].message_to_slot)
#define clear_window (global[CLEAR_WINDOW].clear_window_slot)
#define clear_all_windows (global[CLEAR_ALL_WINDOWS].clear_all_windows_slot)
#define clear_window_by_refnum (global[CLEAR_WINDOW_BY_REFNUM].clear_window_by_refnum_slot)
#define unclear_window_by_refnum (global[UNCLEAR_WINDOW_BY_REFNUM].unclear_window_by_refnum_slot)
#define set_scroll_lines (global[SET_SCROLL_LINES].set_scroll_lines_slot)
#define set_continued_lines (global[SET_CONTINUED_LINES].set_continued_lines_slot)
#define current_refnum (global[CURRENT_REFNUM].current_refnum_slot)
#define number_of_windows_on_screen (global[NUMBER_OF_WINDOWS_ON_SCREEN].number_of_windows_on_screen_slot)
#define set_scrollback_size (global[SET_SCROLLBACK_SIZE].set_scrollback_size_slot)
#define is_window_name_unique (global[IS_WINDOW_NAME_UNIQUE].is_window_name_unique_slot)
#define get_nicklist_by_window (global[GET_NICKLIST_BY_WINDOW].get_nicklist_by_window_slot)
#define scrollback_backwards_lines (global[SCROLLBACK_BACKWARDS_LINES].scrollback_backwards_lines_slot)
#define scrollback_forwards_lines (global[SCROLLBACK_FORWARDS_LINES].scrollback_forwards_lines_slot)
#define scrollback_forwards (global[SCROLLBACK_FORWARDS].scrollback_forwards_slot)
#define scrollback_backwards (global[SCROLLBACK_BACKWARDS].scrollback_backwards_slot)
#define scrollback_end (global[SCROLLBACK_END].scrollback_end_slot)
#define scrollback_start (global[SCROLLBACK_START].scrollback_start_slot)
#define set_hold_mode (global[SET_HOLD_MODE].set_hold_mode_slot)
#define unhold_windows (global[UNHOLD_WINDOWS].unhold_windows_slot)
#define unstop_all_windows (global[FUNC_UNSTOP_ALL_WINDOWS].func_unstop_all_windows_slot)
#define reset_line_cnt (global[RESET_LINE_CNT].reset_line_cnt_slot)
#define toggle_stop_screen (global[FUNC_TOGGLE_STOP_SCREEN].func_toggle_stop_screen_slot)
#define flush_everything_being_held (global[FLUSH_EVERYTHING_BEING_HELD].flush_everything_being_held_slot)
#define unhold_a_window (global[UNHOLD_A_WINDOW].unhold_a_window_slot)
#define recalculate_window_cursor (global[RECALCULATE_WINDOW_CURSOR].recalculate_window_cursor_slot)
#define make_window_current (global[MAKE_WINDOW_CURRENT].make_window_current_slot)
#define clear_scrollback (global[CLEAR_SCROLLBACK].clear_scrollback_slot)

#define set_display_target (global[SET_DISPLAY_TARGET].set_display_target_slot)
#define save_display_target (global[SAVE_DISPLAY_TARGET].save_display_target_slot)
#define restore_display_target (global[RESTORE_DISPLAY_TARGET].restore_display_target_slot)
#define reset_display_target (global[RESET_DISPLAY_TARGET].reset_display_target_slot)

#define build_status (global[BUILD_STATUS].build_status_slot)



#define do_hook (global[HOOK].hook_slot)

/* input.c */
#define update_input (global[FUNC_UPDATE_INPUT].func_update_input_slot)
#define cursor_to_input (global[CURSOR_TO_INPUT].cursor_to_input_slot)
#define set_input (global[SET_INPUT].set_input_slot)
#define get_input (global[GET_INPUT].get_input_slot)
#define get_input_prompt (global[GET_INPUT_PROMPT].get_input_prompt_slot)
#define set_input_prompt (global[SET_INPUT_PROMPT].set_input_prompt_slot)
#define addtabkey (global[ADDTABKEY].addtabkey_slot)
#define gettabkey (global[GETTABKEY].gettabkey_slot)
#define getnextnick (global[GETNEXTNICK].getnextnick_slot)
#define getchannick (global[GETCHANNICK].getchannick_slot)
#define lookup_nickcompletion (global[LOOKUP_NICKCOMPLETION].lookup_nickcompletion_slot)
#define add_completion_type (global[ADD_COMPLETION_TYPE].add_completion_type_slot)

/* names.c */
#define is_channel (global[IS_CHANNEL].is_channel_slot)
#define make_channel (global[MAKE_CHANNEL].make_channel_slot)
#define is_chanop (global[IS_CHANOP].is_chanop_slot)
#define is_halfop (global[IS_HALFOP].is_halfop_slot)
#define im_on_channel (global[IM_ON_CHANNEL].im_on_channel_slot)
#define is_on_channel (global[IS_ON_CHANNEL].is_on_channel_slot)
#define add_channel (global[ADD_CHANNEL].add_channel_slot)
#define add_to_channel (global[ADD_TO_CHANNEL].add_to_channel_slot)
#define get_channel_key (global[GET_CHANNEL_KEY].get_channel_key_slot)
#define recreate_mode (global[FUNC_RECREATE_MODE].func_recreate_mode_slot)
#define do_compress_modes (global[FUNC_COMPRESS_MODES].func_compress_modes_slot)
#define got_ops (global[FUNC_GOT_OPS].func_got_ops_slot)
#define get_channel_bans (global[GET_CHANNEL_BANS].get_channel_bans_slot)
#define get_channel_mode (global[GET_CHANNEL_MODE].get_channel_mode_slot)
#define clear_bans (global[CLEAR_BANS].clear_bans_slot)
#define remove_channel (global[REMOVE_CHANNEL].remove_channel_slot)
#define remove_from_channel (global[REMOVE_FROM_CHANNEL].remove_from_channel_slot)
#define rename_nick (global[RENAME_NICK].rename_nick_slot)
#define get_channel_oper (global[GET_CHANNEL_OPER].get_channel_oper_slot)
#define get_channel_halfop (global[GET_CHANNEL_HALFOP].get_channel_halfop_slot)
#define get_channel_voice (global[GET_CHANNEL_VOICE].get_channel_voice_slot)
#define fetch_userhost (global[FETCH_USERHOST].fetch_userhost_slot)
#define create_channel_list (global[CREATE_CHANNEL_LIST].create_channel_list_slot)
#define flush_channel_stats (global[FLUSH_CHANNEL_STATS].flush_channel_stats_slot)
#define lookup_channel (global[LOOKUP_CHANNEL].lookup_channel_slot)

/* hash.c */
#define find_nicklist_in_channellist (global[FIND_NICKLIST_IN_CHANNELLIST].find_nicklist_in_channellist_slot)
#define add_nicklist_to_channellist (global[ADD_NICKLIST_TO_CHANNELLIST].add_nicklist_to_channellist_slot)
#define next_nicklist (global[NEXT_NICKLIST].next_nicklist_slot)
#define next_namelist (global[NEXT_NAMELIST].next_namelist_slot)
#define add_name_to_genericlist (global[ADD_NAME_TO_GENERICLIST].add_name_to_genericlist_slot)
#define find_name_in_genericlist (global[FIND_NAME_IN_GENERICLIST].find_name_in_genericlist_slot)
#define add_whowas_userhost_channel (global[ADD_WHOWAS_USERHOST_CHANNEL].add_whowas_userhost_channel_slot)
#define find_userhost_channel (global[FIND_USERHOST_CHANNEL].find_userhost_channel_slot)
#define next_userhost (global[NEXT_USERHOST].next_userhost_slot)
#define sorted_nicklist (global[SORTED_NICKLIST].sorted_nicklist_slot)
#define clear_sorted_nicklist (global[CLEAR_SORTED_NICKLIST].clear_sorted_nicklist_slot)
#define add_name_to_floodlist (global[ADD_NAME_TO_FLOODLIST].add_name_to_floodlist_slot)
#define find_name_in_floodlist (global[FIND_NAME_IN_FLOODLIST].find_name_in_floodlist_slot)

#define remove_oldest_whowas_hashlist (global[REMOVE_OLDEST_WHOWAS_HASHLIST].remove_oldest_whowas_hashlist_slot)



/* cset.c fset.c vars.c set string and set int ops */
#define fget_string_var (global[FGET_STRING_VAR].fget_string_var_slot)
#define fset_string_var (global[FSET_STRING_VAR].fset_string_var_slot)
#define get_wset_string_var (global[GET_WSET_STRING_VAR].get_wset_string_var_slot)
#define set_wset_string_var (global[SET_WSET_STRING_VAR].set_wset_string_var_slot)
#define get_cset_int_var (global[GET_CSET_INT_VAR].get_cset_int_var_slot)
#define set_cset_int_var (global[SET_CSET_INT_VAR].set_cset_int_var_slot)
#define get_cset_str_var (global[GET_CSET_STR_VAR].get_cset_str_var_slot)
#define set_cset_str_var (global[SET_CSET_STR_VAR].set_cset_str_var_slot)

#define get_dllint_var (global[GET_DLLINT_VAR].get_dllint_var_slot)
#define set_dllint_var (global[SET_DLLINT_VAR].set_dllint_var_slot)
#define get_dllstring_var (global[GET_DLLSTRING_VAR].get_dllstring_var_slot)
#define set_dllstring_var (global[SET_DLLSTRING_VAR].set_dllstring_var_slot)
#define save_dllvar (global[SAVE_DLLVAR].save_dllvar_slot)

#define get_int_var (global[GET_INT_VAR].get_int_var_slot)
#define set_int_var (global[SET_INT_VAR].set_int_var_slot)
#define get_string_var (global[GET_STRING_VAR].get_string_var_slot)
#define set_string_var (global[SET_STRING_VAR].set_string_var_slot)


/* module.c */
#define add_module_proc (global[ADD_MODULE_PROC].add_module_proc_slot)
#define remove_module_proc (global[REMOVE_MODULE_PROC].remove_module_proc_slot)


/* timer.c */
#define add_timer (global[ADD_TIMER].add_timer_slot)
#define delete_timer (global[DELETE_TIMER].delete_timer_slot)
#define delete_all_timers (global[DELETE_ALL_TIMERS].delete_all_timers_slot)



/* server.c */
#define send_to_server (global[SEND_TO_SERVER].send_to_server_slot)
#define queue_send_to_server (global[QUEUE_SEND_TO_SERVER].queue_send_to_server_slot)
#define my_send_to_server (global[MY_SEND_TO_SERVER].my_send_to_server_slot)
#define get_connected (global[GET_CONNECTED].get_connected_slot)
#define connect_to_server_by_refnum (global[CONNECT_TO_SERVER_BY_REFNUM].connect_to_server_by_refnum_slot)
#define close_server (global[CLOSE_SERVER].close_server_slot)
#define is_server_connected (global[IS_SERVER_CONNECTED].is_server_connected_slot)
#define flush_server (global[FLUSH_SERVER].flush_server_slot)
#define server_is_connected (global[SERVER_IS_CONNECTED].server_is_connected_slot)
#define is_server_open (global[IS_SERVER_OPEN].is_server_open_slot)
#define close_all_server (global[CLOSE_ALL_SERVER].close_all_server_slot)

#define read_server_file (global[READ_SERVER_FILE].read_server_file_slot)
#define add_to_server_list (global[ADD_TO_SERVER_LIST].add_to_server_list_slot)
#define build_server_list (global[BUILD_SERVER_LIST].build_server_list_slot)
#define display_server_list (global[DISPLAY_SERVER_LIST].display_server_list_slot)
#define parse_server_info (global[PARSE_SERVER_INFO].parse_server_info_slot)
#define server_list_size (global[SERVER_LIST_SIZE].server_list_size_slot)

#define find_server_refnum (global[FIND_SERVER_REFNUM].find_server_refnum_slot)
#define find_in_server_list (global[FIND_IN_SERVER_LIST].find_in_server_list_slot)
#define parse_server_index (global[PARSE_SERVER_INDEX].parse_server_index_slot)

#define set_server_redirect (global[SET_SERVER_REDIRECT].set_server_redirect_slot)
#define get_server_redirect (global[GET_SERVER_REDIRECT].get_server_redirect_slot)
#define check_server_redirect (global[CHECK_SERVER_REDIRECT].check_server_redirect_slot)
#define fudge_nickname (global[FUDGE_NICKNAME].fudge_nickname_slot)
#define reset_nickname (global[RESET_NICKNAME].reset_nickname_slot)

#define set_server_cookie (global[SET_SERVER_COOKIE].set_server_cookie_slot)
#define update_server_umode (global[UPDATE_SERVER_UMODE].update_server_umode_slot)
#define set_server_motd (global[SET_SERVER_MOTD].set_server_motd_slot)
#define set_server_operator (global[SET_SERVER_OPERATOR].set_server_operator_slot)
#define set_server_itsname (global[SET_SERVER_ITSNAME].set_server_itsname_slot)
#define set_server_version (global[SET_SERVER_VERSION].set_server_version_slot)
#define set_server_lag (global[SET_SERVER_LAG].set_server_lag_slot)
#define set_server_password (global[SET_SERVER_PASSWORD].set_server_password_slot)
#define set_server_nickname (global[SET_SERVER_NICKNAME].set_server_nickname_slot)
#define set_server2_8 (global[SET_SERVER2_8].set_server2_8_slot)
#define set_server_away (global[SET_SERVER_AWAY].set_server_away_slot)

#define get_server_cookie (global[GET_SERVER_COOKIE].get_server_cookie_slot)
#define get_server_nickname (global[GET_SERVER_NICKNAME].get_server_nickname_slot)
#define get_server_name (global[GET_SERVER_NAME].get_server_name_slot)
#define get_server_itsname (global[GET_SERVER_ITSNAME].get_server_itsname_slot)
#define get_server_motd (global[GET_SERVER_MOTD].get_server_motd_slot)
#define get_server_operator (global[GET_SERVER_OPERATOR].get_server_operator_slot)
#define get_server_version (global[GET_SERVER_VERSION].get_server_version_slot)
#define get_server_umode (global[GET_SERVER_UMODE].get_server_umode_slot)
#define get_server_port (global[GET_SERVER_PORT].get_server_port_slot)
#define get_server_lag (global[GET_SERVER_LAG].get_server_lag_slot)
#define get_server2_8 (global[GET_SERVER2_8].get_server2_8_slot)
#define get_umode (global[GET_UMODE].get_umode_slot)
#define get_server_away (global[GET_SERVER_AWAY].get_server_away_slot)
#define get_server_network (global[GET_SERVER_NETWORK].get_server_network_slot)
#define get_pending_nickname (global[GET_PENDING_NICKNAME].get_pending_nickname_slot)
#define server_disconnect (global[SERVER_DISCONNECT].server_disconnect_slot)

#define get_server_list (global[GET_SERVER_LIST].get_server_list_slot)
#define get_server_channels (global[GET_SERVER_CHANNELS].get_server_channels_slot)

#define set_server_last_ctcp_time (global[SET_SERVER_LAST_CTCP_TIME].set_server_last_ctcp_time_slot)
#define get_server_last_ctcp_time (global[GET_SERVER_LAST_CTCP_TIME].get_server_last_ctcp_time_slot)
#define set_server_trace_flag (global[SET_SERVER_TRACE_FLAG].set_server_trace_flag_slot)
#define get_server_trace_flag (global[GET_SERVER_TRACE_FLAG].get_server_trace_flag_slot)
#define get_server_read (global[GET_SERVER_READ].get_server_read_slot)
#define get_server_linklook (global[GET_SERVER_LINKLOOK].get_server_linklook_slot)
#define set_server_linklook (global[SET_SERVER_LINKLOOK].set_server_linklook_slot)
#define get_server_stat_flag (global[GET_SERVER_STAT_FLAG].get_server_stat_flag_slot)
#define set_server_stat_flag (global[SET_SERVER_STAT_FLAG].set_server_stat_flag_slot)
#define get_server_linklook_time (global[GET_SERVER_LINKLOOK_TIME].get_server_linklook_time_slot)
#define set_server_linklook_time (global[SET_SERVER_LINKLOOK_TIME].set_server_linklook_time_slot)
#define get_server_trace_kill (global[GET_SERVER_TRACE_KILL].get_server_trace_kill_slot)
#define set_server_trace_kill (global[SET_SERVER_TRACE_KILL].set_server_trace_kill_slot)
#define add_server_channels (global[ADD_SERVER_CHANNELS].add_server_channels_slot)
#define set_server_channels (global[SET_SERVER_CHANNELS].set_server_channels_slot)
#define send_msg_to_channels (global[SEND_MSG_TO_CHANNELS].send_msg_to_channels_slot)
#define send_msg_to_nicks (global[SEND_MSG_TO_NICKS].send_msg_to_nicks_slot)
#define is_server_queue (global[IS_SERVER_QUEUE].is_server_queue_slot)


/* sockets */
#define add_socketread (global[ADD_SOCKETREAD].add_socketread_slot)
#define add_sockettimeout (global[ADD_SOCKETTIMEOUT].add_sockettimeout_slot)
#define close_socketread (global[CLOSE_SOCKETREAD].close_socketread_slot)
#define get_socket (global[GET_SOCKET].get_socket_slot)
#define set_socketflags (global[SET_SOCKETFLAGS].set_socketflags_slot)
#define get_socketflags (global[GET_SOCKETFLAGS].get_socketflags_slot)
#define check_socket (global[CHECK_SOCKET].check_socket_slot)
#define read_sockets (global[READ_SOCKETS].read_sockets_slot)
#define write_sockets (global[WRITE_SOCKETS].write_sockets_slot)
#define get_max_fd (global[GET_MAX_FD].get_max_fd_slot)
#define new_close (global[NEW_CLOSE].new_close_slot)
#define new_open (global[NEW_OPEN].new_open_slot)
#define dgets (global[DGETS].dgets_slot)
#define get_socketinfo (global[GET_SOCKETINFO].get_socketinfo_slot)
#define set_socketinfo (global[SET_SOCKETINFO].set_socketinfo_slot)
#define set_socket_write (global[SET_SOCKETWRITE].set_socketwrite_slot)


/* flood.c */
#define is_other_flood (global[IS_OTHER_FLOOD].is_other_flood_slot)
#define check_flooding (global[CHECK_FLOODING].check_flooding_slot)
#define flood_prot (global[FLOOD_PROT].flood_prot_slot)

/* expr.c */
#define next_unit (global[NEXT_UNIT].next_unit_slot)
#define parse_inline (global[PARSE_INLINE].parse_inline_slot)
#define expand_alias (global[EXPAND_ALIAS].expand_alias_slot)
#define alias_special_char (global[ALIAS_SPECIAL_CHAR].alias_special_char_slot)
#define parse_line (global[PARSE_LINE].parse_line_slot)
#define parse_command (global[PARSE_COMMAND_FUNC].parse_command_func_slot)
#define make_local_stack (global[MAKE_LOCAL_STACK].make_local_stack_slot)
#define destroy_local_stack (global[DESTROY_LOCAL_STACK].destroy_local_stack_slot)


/* dcc.c */
#define dcc_create (global[DCC_CREATE_FUNC].dcc_create_func_slot)
#define find_dcc (global[FIND_DCC_FUNC].find_dcc_func_slot)
#define erase_dcc_info (global[ERASE_DCC_INFO].erase_dcc_info_slot)
#define add_dcc_bind (global[ADD_DCC_BIND].add_dcc_bind_slot)
#define remove_dcc_bind (global[REMOVE_DCC_BIND].remove_dcc_bind_slot)
#define remove_all_dcc_binds (global[REMOVE_ALL_DCC_BINDS].remove_all_dcc_binds_slot)
#define get_active_count (global[GET_ACTIVE_COUNT].get_active_count_slot)
#define get_num_queue (global[GET_NUM_QUEUE].get_num_queue_slot)
#define add_to_queue (global[ADD_TO_QUEUE].add_to_queue_slot)
#define dcc_filesend (global[DCC_FILESEND].dcc_filesend_slot)
#define dcc_resend (global[DCC_RESEND].dcc_resend_slot)
#define dcc_chat_socketread (global[DCC_CHAT_SOCKETREAD].dcc_chat_socketread_slot)
#define dcc_send_socketread (global[DCC_SEND_SOCKETREAD].dcc_send_socketread_slot)

/* irc.c */
#define irc_exit (global[IRC_EXIT_FUNC].irc_exit_func_slot)
#define io (global[IRC_IO_FUNC].irc_io_func_slot)

/* commands.c */
#define find_command (global[FIND_COMMAND_FUNC].find_command_func_slot)

#define lock_stack_frame (global[LOCK_STACK_FRAME].lock_stack_frame_slot)
#define unlock_stack_frame (global[UNLOCK_STACK_FRAME].unlock_stack_frame_slot)

/* who.c */
#define userhostbase (global[USERHOSTBASE].userhostbase_slot)
#define isonbase (global[ISONBASE].isonbase_slot)
#define whobase (global[WHOBASE].whobase_slot)

#define add_to_window_list (global[ADD_TO_WINDOW_LIST].add_to_window_list_slot)

/*
 * Rest of these are all variables of various sorts.
 */

#ifndef MAIN_SOURCE

#define nickname ((char *) *global[NICKNAME].nickname_slot)
#define irc_version ((char *) *global[IRC_VERSION].irc_version_slot)

#define from_server (*global[FROM_SERVER].from_server_slot)
#define connected_to_server (*global[CONNECTED_TO_SERVER].connected_to_server_slot)
#define primary_server (*global[PRIMARY_SERVER].primary_server_slot)
#define parsing_server_index (*global[PARSING_SERVER_INDEX].parsing_server_index_slot)
#define now (*global[NOW].now_slot)
#define start_time (*global[START_TIME].start_time_slot)
#define idle_time() ((time_t) *(global[IDLE_TIME].idle_time_slot))

#define loading_global (*global[LOADING_GLOBAL].loading_global_slot)
#define target_window (*global[TARGET_WINDOW].target_window_slot)
#define current_window (*global[CURRENT_WINDOW].current_window_slot)
#define invisible_list (*global[INVISIBLE_LIST].invisible_list_slot)
#define main_screen (*global[MAIN_SCREEN].main_screen_slot)
#define last_input_screen (*global[LAST_INPUT_SCREEN].last_input_screen_slot)
#define output_screen (*global[OUTPUT_SCREEN].output_screen_slot)
#define screen_list (*global[SCREEN_LIST].screen_list_slot)
#define irclog_fp (*global[IRCLOG_FP].irclog_fp_slot)
#define window_display (*global[WINDOW_DISPLAY].window_display_slot)
#define status_update_flag (*global[STATUS_UPDATE_FLAG].status_update_flag_slot)
#define tabkey_array (*global[TABKEY_ARRAY].tabkey_array_slot)
#define autoreply_array (*global[AUTOREPLY_ARRAY].autoreply_array_slot)
#define identd (*global[IDENTD_SOCKET].identd_socket_slot)
#define doing_notice (*global[DOING_NOTICE].doing_notice_slot)

#define default_output_function (global[DEFAULT_OUTPUT_FUNCTION].default_output_function_slot)

#define serv_open_func ((*global[SERV_OPEN_FUNC].serv_open_func_slot))
#define serv_input_func ((*global[SERV_INPUT_FUNC].serv_input_func_slot))
#define serv_output_func ((*global[SERV_OUTPUT_FUNC].serv_output_func_slot))
#define serv_close_func ((*global[SERV_CLOSE_FUNC].serv_close_func_slot))
#ifdef WANT_TCL
#define tcl_interp (global[VAR_TCL_INTERP].var_tcl_interp_slot)
#else
#define tcl_interp NULL
#endif
#if 1
#endif

#else
#undef get_time
#define get_time(a) BX_get_time(a)
#endif /* MAIN_SOURCE */

#ifdef GUI
#ifndef MAIN_SOURCE
#define lastclicklinedata ((char *) *global[LASTCLICKLINEDATA].lastclicklinedata_slot)
#define contextx (*global[CONTEXTX].contextx_slot)
#define contexty (*global[CONTEXTY].contexty_slot)
#define guiipc (*global[GUIIPC].guiipc_slot)
#endif
#define gui_mutex_lock() (global[GUI_MUTEX_LOCK].gui_mutex_lock_slot)()
#define gui_mutex_unlock() (global[GUI_MUTEX_UNLOCK].gui_mutex_unlock_slot)()
#endif

#endif /* WTERM_C || STERM_C */
#endif
