/*
 * Module/dll handling code written by Colten Edwards.
 * Copyright 1997
 */
#ifndef MODULE_H_
#define MODULE_H_


/*
 * if we change the table below, we change this module number to the 
 * current date (YYYYMMDDxx where xx is a serial number).
 */
#define MODULE_VERSION 2018020801UL

#include "struct.h"
#include "alist.h"
#include "whowas.h"
#include "cdcc.h"
#include "server.h"
#include "flood.h"
#include "input.h"
#include "cset.h"
#include "vars.h"
#include "dcc.h"

typedef union BXGlobalEntry BXGlobalEntry;

typedef int (*Function_ptr)();

#ifdef WANT_DLL
#ifdef HPUX
#include <dl.h>
#endif

#define COMMAND_PROC	0x0001		/* New /command proc return void */
#define ALIAS_PROC	0x0002		/* new $alias proc return new_malloc'd string */
#define CTCP_PROC	0x0004		/* new ctcp proc return new_malloc'd string*/
#define VAR_PROC	0x0008		/* new variable no return */
#define HOOK_PROC	0x0010		/* new numeric proc 
					 * return int 1 if we don't want client
					 * to also handle this.
					 * or 0  if we want client to handle
					 */
#define RAW_PROC	0x0020		/* new raw irc proc */
#define DCC_PROC	0x0040		/* add to dcc command list */
#define OUTPUT_PROC	0x0080		/* New output proc for all windows. */
#define WINDOW_PROC	0x0100		/* New window proc */
#define TABLE_PROC	0x8000		/* removing a global_table proc */

#define INVALID_MODVERSION -1

typedef int (Irc_PackageInitProc)  (IrcCommandDll **, BXGlobalEntry *);
typedef char *(Irc_PackageVersionProc)  (IrcCommandDll **);

typedef struct _function_table 
{
	char	*name;
	char	*desc;
	int	id;
	int	flag;
	void	*func1;
	void	*func2;
} Function;

typedef struct _package_installed {
	struct _package_installed *next;
	char    *name;
	char    *version;

	int	major;
	int	minor;
	int	lock;

#if defined(HPUX)
	shl_t handle;
#elif defined(__EMX__)
	HMODULE handle;
#elif defined(WINNT)
	HINSTANCE handle;
#else
	void	*handle;
#endif
	Irc_PackageInitProc *cleanup;
} Packages;
                                
Packages *find_module (char *);
int BX_add_module_proc (unsigned int, char *, char *, char *, int, int, void *, void *);
int remove_package (char *);
int BX_remove_module_proc (unsigned int, char *, char *, char *);
int add_module(unsigned int, Function *, char *);

extern BuiltInDllFunctions *dll_functions;
#ifndef __hook_c
extern NumericFunction *dll_numeric_list;
#endif
extern IrcCommandDll *dll_commands;
extern CtcpEntryDll *dll_ctcp;
extern WindowDll *dll_window;
extern IrcVariableDll *dll_variable;

IrcCommandDll *find_dll_command(const char *, int *);
char *BX_get_dllstring_var(char *);
int BX_get_dllint_var(char *);
void BX_set_dllstring_var(char *, char *);
void BX_set_dllint_var(char *, unsigned int);
void BX_save_dllvar(FILE *, char *);
RawDll *find_raw_proc(char *, char **);

int check_version(unsigned long);
#endif /* WANT_DLL */

/* 
 * the order of this enum is extremely important. ie a module compiled
 * on a differant order would fail miserably. So when adding to the list
 * make sure and add to the end of the list.
 */
 
enum FUNCTION_VALUE
{
/* ircaux.c */
	MODULE_VERSION_CHECK,
/* output.c */	
	PUT_IT,
	BITCHSAY,
	YELL,
	ADD_TO_LOG,
	VSNPRINTF,
	SNPRINTF,
	NEW_MALLOC,
	NEW_FREE,
	NEW_REALLOC,
	MALLOC_STRCPY,
	MALLOC_STRCAT,
	MALLOC_STR2CPY,
	M_3DUP,
	M_OPENDUP,
	M_S3CAT,
	M_S3CAT_S,
	M_3CAT,
	UPPER,
	LOWER,
	STRISTR,
	RSTRISTR,
	WORD_COUNT,
	REMOVE_TRAILING_SPACES,
	MY_STRICMP,
	MY_STRNICMP,
	MY_STRNSTR,
	CHOP,
	STRMCPY,
	STRMCAT,
	SCANSTR,
	EXPAND_TWIDDLE,
	CHECK_NICKNAME,
	SINDEX,
	RSINDEX,
	ISNUMBER,
	RFGETS,
	PATH_SEARCH,
	DOUBLE_QUOTE,
	IRCPANIC,
	END_STRCMP,
	BEEP_EM,
	UZFOPEN,
	FUNC_GET_TIME,
	TIME_DIFF,
	TIME_TO_NEXT_MINUTE,
	PLURAL,
	MY_CTIME,
	LTOA,
	STRFORMAT,
	MATCHINGBRACKET,
	PARSE_NUMBER,
	SPLITW,
	UNSPLITW,
	M_2DUP,
	M_E3CAT,
	CHECK_VAL,
	ON_OFF,
	STREXTEND,
	STRFILL,
	EMPTY_FUNC,
	REMOVE_BRACKETS,
	MY_ATOL,
	M_DUPCHAR,
	STREQ,
	STRIEQ,
	STRMOPENCAT,
	OV_STRCPY,
	STRIP_CONTROL,
	FIGURE_OUT_ADDRESS,
	STRNRCHR,
	MASK_DIGITS,
	CCSPAN,
	CHARCOUNT,
	STRPCAT,
	STRCPY_NOCOLORCODES,
	CRYPTIT,
	STRIPDEV,
	MANGLE_LINE,
	M_STRDUP,
	M_STRCAT_UES,
	M_STRNDUP,
	MALLOC_SPRINTF,
	M_SPRINTF,
	NEXT_ARG,
	NEW_NEXT_ARG,
	NEW_NEW_NEXT_ARG,
	LAST_ARG,
	NEXT_IN_COMMA_LIST,
	RANDOM_NUMBER,
	
/* words.c */
	STRSEARCH,
	MOVE_TO_WORD,
	MOVE_WORD_REL,
	EXTRACT,
	EXTRACT2,
	WILD_MATCH,
/* network */
	CONNECT_BY_NUMBER,
	RESOLV,
	LOOKUP_HOST,
	LOOKUP_IP,
	HOST_TO_IP,
	IP_TO_HOST,
	ONE_TO_ANOTHER,
	SET_BLOCKING,
	SET_NON_BLOCKING,

/* list.c */
	ADD_TO_LIST,
	ADD_TO_LIST_EXT,
	REMOVE_FROM_LIST_,
	REMOVE_FROM_LIST_EXT,
	REMOVEWILD_FROM_LIST,
	LIST_LOOKUP,
	LIST_LOOKUP_EXT,
	FIND_IN_LIST,
	FIND_IN_LIST_EXT,
/* alist.c */
	ADD_TO_ARRAY,
	REMOVE_FROM_ARRAY,
	ARRAY_POP,
	REMOVE_ALL_FROM_ARRAY,
	ARRAY_LOOKUP,
	FIND_ARRAY_ITEM,
	FIND_FIXED_ARRAY_ITEM,
	
/* server.c */
	SEND_TO_SERVER,
	QUEUE_SEND_TO_SERVER,
	MY_SEND_TO_SERVER,
/* connecting to the server */
	GET_CONNECTED,
	CONNECT_TO_SERVER_BY_REFNUM,
	CLOSE_SERVER,
	IS_SERVER_CONNECTED,
	FLUSH_SERVER,
	SERVER_IS_CONNECTED,
	IS_SERVER_OPEN,
	CLOSE_ALL_SERVER,
/* server file reading */
	READ_SERVER_FILE,
	ADD_TO_SERVER_LIST,
	BUILD_SERVER_LIST,
	DISPLAY_SERVER_LIST,
	PARSE_SERVER_INFO,
	SERVER_LIST_SIZE,
/* misc server/nickname functions */
	FIND_SERVER_REFNUM,
	FIND_IN_SERVER_LIST,
	PARSE_SERVER_INDEX,
	SET_SERVER_REDIRECT,
	GET_SERVER_REDIRECT,
	CHECK_SERVER_REDIRECT,
	FUDGE_NICKNAME,
	RESET_NICKNAME,
/* various set server struct functions */
	SET_SERVER_COOKIE,
	UPDATE_SERVER_UMODE,
	SET_SERVER_MOTD,
	SET_SERVER_OPERATOR,
	SET_SERVER_ITSNAME,
	SET_SERVER_VERSION,
	SET_SERVER_LAG,
	SET_SERVER_PASSWORD,
	SET_SERVER_NICKNAME,
	SET_SERVER2_8,
	SET_SERVER_AWAY,
/* various get server struct functions */
	GET_SERVER_COOKIE,
	GET_SERVER_NICKNAME,
	GET_SERVER_NAME,
	GET_SERVER_ITSNAME,
	GET_SERVER_MOTD,
	GET_SERVER_OPERATOR,
	GET_SERVER_VERSION,
	GET_SERVER_UMODE,
	GET_SERVER_PORT,
	GET_SERVER_LAG,
	GET_SERVER2_8,
	GET_UMODE,
	GET_SERVER_AWAY,
	GET_SERVER_NETWORK,
	GET_PENDING_NICKNAME,
	SERVER_DISCONNECT,

	GET_SERVER_LIST,
	GET_SERVER_CHANNELS,

	SET_SERVER_LAST_CTCP_TIME,
	GET_SERVER_LAST_CTCP_TIME,
	SET_SERVER_TRACE_FLAG,
	GET_SERVER_TRACE_FLAG,
	GET_SERVER_READ,
	GET_SERVER_LINKLOOK,
	SET_SERVER_LINKLOOK,
	GET_SERVER_LINKLOOK_TIME,
	SET_SERVER_LINKLOOK_TIME,
	GET_SERVER_TRACE_KILL,
	SET_SERVER_TRACE_KILL,
	ADD_SERVER_CHANNELS,
	SET_SERVER_CHANNELS,
	SEND_MSG_TO_CHANNELS,
	SEND_MSG_TO_NICKS,
	IS_SERVER_QUEUE,
/* glob.c */
	BSD_GLOB,
	BSD_GLOBFREE,			
	
	CONVERT_OUTPUT_FORMAT,
	UPDATE_CLOCK,
	BREAKARGS,
	PASTEARGS,
	USERAGE,
	SEND_TEXT,
	SET_LASTLOG_MSG_LEVEL,
	SPLIT_CTCP,
	RANDOM_STR,
	DCC_PRINTF,

	MY_ENCRYPT,
	MY_DECRYPT,
	PREPARE_COMMAND,
	BUILD_STATUS,
	FUNC_LOAD,

	HOOK,
/* irc.c */
	IRC_IO_FUNC,
	IRC_EXIT_FUNC,
/* alias.c */
	LOCK_STACK_FRAME,
	UNLOCK_STACK_FRAME,
	
	
/* input.c */
	FUNC_UPDATE_INPUT,
	CURSOR_TO_INPUT,
	SET_INPUT,
	GET_INPUT,
	SET_INPUT_PROMPT,
	GET_INPUT_PROMPT,
	ADDTABKEY,
	GETTABKEY,
	GETNEXTNICK,
	GETCHANNICK,
	LOOKUP_NICKCOMPLETION,
	ADD_COMPLETION_TYPE,
		
/* module.c */
	ADD_MODULE_PROC,
	REMOVE_MODULE_PROC,
/* names.c */	
	IS_CHANOP,
	IS_CHANNEL,
	MAKE_CHANNEL,
	IM_ON_CHANNEL,
	IS_ON_CHANNEL,
	ADD_CHANNEL,
	ADD_TO_CHANNEL,
	GET_CHANNEL_KEY,
	FUNC_RECREATE_MODE,
	FUNC_COMPRESS_MODES,
	FUNC_GOT_OPS,
	GET_CHANNEL_BANS,
	GET_CHANNEL_MODE,
	CLEAR_BANS,
	REMOVE_CHANNEL,
	REMOVE_FROM_CHANNEL,
	RENAME_NICK,
	GET_CHANNEL_OPER,
	GET_CHANNEL_HALFOP,
	FETCH_USERHOST,
	GET_CHANNEL_VOICE,
	CREATE_CHANNEL_LIST,
	FLUSH_CHANNEL_STATS,
	LOOKUP_CHANNEL,
		
	FIND_NICKLIST_IN_CHANNELLIST,
	ADD_NICKLIST_TO_CHANNELLIST,
	NEXT_NICKLIST,

	NEXT_NAMELIST,
	ADD_NAME_TO_GENERICLIST,
	FIND_NAME_IN_GENERICLIST,
	ADD_WHOWAS_USERHOST_CHANNEL,
	FIND_USERHOST_CHANNEL,
	NEXT_USERHOST,
	SORTED_NICKLIST,
	CLEAR_SORTED_NICKLIST,
	ADD_NAME_TO_FLOODLIST,
	FIND_NAME_IN_FLOODLIST,
	CLEAR_WHOWAS_HASH_TABLE,
	REMOVE_OLDEST_WHOWAS_HASHLIST,
	
		
/* cset.c fset.c vars.c */	
	FGET_STRING_VAR,
	FSET_STRING_VAR,
	GET_WSET_STRING_VAR,
	SET_WSET_STRING_VAR,
	SET_CSET_INT_VAR,
	GET_CSET_INT_VAR,
	SET_CSET_STR_VAR,
	GET_CSET_STR_VAR,
	GET_DLLINT_VAR,
	SET_DLLINT_VAR,
	GET_DLLSTRING_VAR,
	SET_DLLSTRING_VAR,
	SAVE_DLLVAR,
	GET_INT_VAR,
	SET_INT_VAR,
	GET_STRING_VAR,
	SET_STRING_VAR,

	ADD_TIMER,
	DELETE_TIMER,
	DELETE_ALL_TIMERS,

/* sockets from misc.c */
	ADD_SOCKETREAD,
	ADD_SOCKETTIMEOUT,
	CLOSE_SOCKETREAD,
	GET_SOCKET,
	SET_SOCKETFLAGS,
	GET_SOCKETFLAGS,
	GET_SOCKETINFO,
	SET_SOCKETINFO,
	SET_SOCKETWRITE,
	CHECK_SOCKET,
	READ_SOCKETS,
	WRITE_SOCKETS,
	GET_MAX_FD,
	NEW_CLOSE,
	NEW_OPEN,	
	DGETS,


/* screen.c */
	PREPARE_DISPLAY,
	ADD_TO_WINDOW,
	SKIP_INCOMING_MIRC,
	ADD_TO_SCREEN,
	SPLIT_UP_LINE,
	OUTPUT_LINE,
	OUTPUT_WITH_COUNT,
	SCROLL_WINDOW,
	CURSOR_NOT_IN_DISPLAY,
	CURSOR_IN_DISPLAY,
	IS_CURSOR_IN_DISPLAY,
	REPAINT_WINDOW,
	CREATE_NEW_SCREEN,
	CREATE_ADDITIONAL_SCREEN,
	KILL_SCREEN,
	XTERM_SETTITLE,
	ADD_WAIT_PROMPT,
	SKIP_CTL_C_SEQ,
	STRIP_ANSI,

/* window.c */
	FREE_FORMATS,
	REMOVE_WINDOW_FROM_SCREEN,
	SET_SCREENS_CURRENT_WINDOW,
	NEW_WINDOW,
	DELETE_WINDOW,
	TRAVERSE_ALL_WINDOWS,
	ADD_TO_INVISIBLE_LIST,
	ADD_TO_WINDOW_LIST,
	RECALCULATE_WINDOW_POSITIONS,
	MOVE_WINDOW,
	RESIZE_WINDOW,
	REDRAW_ALL_WINDOWS,
	REBALANCE_WINDOWS,
	RECALCULATE_WINDOWS,
	UPDATE_ALL_WINDOWS,
	GOTO_WINDOW,
	HIDE_BX_WINDOW,
	FUNC_SWAP_LAST_WINDOW,
	FUNC_SWAP_NEXT_WINDOW,
	FUNC_SWAP_PREVIOUS_WINDOW,
	SHOW_WINDOW,
	GET_STATUS_BY_REFNUM,
	GET_WINDOW_BY_DESC,
	GET_WINDOW_BY_REFNUM,
	GET_VISIBLE_BY_REFNUM,
	GET_WINDOW_BY_NAME,
	FUNC_NEXT_WINDOW,
	FUNC_PREVIOUS_WINDOW,
	UPDATE_WINDOW_STATUS,
	UPDATE_ALL_STATUS,
	UPDATE_WINDOW_STATUS_ALL,
	STATUS_UPDATE,
	SET_PROMPT_BY_REFNUM,
	GET_PROMPT_BY_REFNUM,
	QUERY_NICK, /* DEFUNCT */
	QUERY_HOST, /* DEFUNCT */
	QUERY_CMD, /* DEFUNCT */
	GET_TARGET_BY_REFNUM,
	GET_TARGET_CMD_BY_REFNUM,
	GET_WINDOW_TARGET_BY_DESC,
	IS_CURRENT_CHANNEL,
	SET_CURRENT_CHANNEL_BY_REFNUM,
	GET_CURRENT_CHANNEL_BY_REFNUM,
	GET_REFNUM_BY_WINDOW,
	IS_BOUND_TO_WINDOW,
	GET_WINDOW_BOUND_CHANNEL,
	IS_BOUND_ANYWHERE,
	IS_BOUND,
	UNBIND_CHANNEL,
	GET_BOUND_CHANNEL,
	GET_WINDOW_SERVER,
	SET_WINDOW_SERVER,
	WINDOW_CHECK_SERVERS,
	CHANGE_WINDOW_SERVER,
	SET_LEVEL_BY_REFNUM,
	SET_SERVER_STAT_FLAG,
	GET_SERVER_STAT_FLAG,
	MESSAGE_TO,
	CLEAR_WINDOW,
	CLEAR_ALL_WINDOWS,
	CLEAR_WINDOW_BY_REFNUM,
	UNCLEAR_WINDOW_BY_REFNUM,
	SET_SCROLL_LINES,
	SET_CONTINUED_LINES,
	CURRENT_REFNUM,
	NUMBER_OF_WINDOWS_ON_SCREEN,
	SET_SCROLLBACK_SIZE,
	IS_WINDOW_NAME_UNIQUE,
	GET_NICKLIST_BY_WINDOW,
	SCROLLBACK_BACKWARDS_LINES,
	SCROLLBACK_FORWARDS_LINES,
	SCROLLBACK_FORWARDS,
	SCROLLBACK_BACKWARDS,
	SCROLLBACK_END,
	SCROLLBACK_START,
	SET_HOLD_MODE,
	UNHOLD_WINDOWS,
	FUNC_UNSTOP_ALL_WINDOWS,
	RESET_LINE_CNT,
	FUNC_TOGGLE_STOP_SCREEN,
	FLUSH_EVERYTHING_BEING_HELD,
	UNHOLD_A_WINDOW,
	RECALCULATE_WINDOW_CURSOR,
	MAKE_WINDOW_CURRENT,
	CLEAR_SCROLLBACK,
	SET_DISPLAY_TARGET,
	RESET_DISPLAY_TARGET,
	RESTORE_DISPLAY_TARGET,
	SAVE_DISPLAY_TARGET,
	
	IS_OTHER_FLOOD,
	CHECK_FLOODING,
	FLOOD_PROT,	
/* expr.c */
	
	NEXT_UNIT,
	EXPAND_ALIAS,
	PARSE_INLINE,
	ALIAS_SPECIAL_CHAR,
	PARSE_LINE,
	PARSE_COMMAND_FUNC,
	MAKE_LOCAL_STACK,
	DESTROY_LOCAL_STACK,
	
/* dcc.c */
	DCC_CREATE_FUNC,
	FIND_DCC_FUNC,
	ERASE_DCC_INFO,	
	ADD_DCC_BIND,
	REMOVE_DCC_BIND,
	REMOVE_ALL_DCC_BINDS,
	GET_ACTIVE_COUNT,
	GET_NUM_QUEUE,
	ADD_TO_QUEUE,
	DCC_FILESEND,
	DCC_RESEND,
	DCC_CHAT_SOCKETREAD,
	DCC_SEND_SOCKETREAD,
		
/* who.c */
	WHOBASE,
	ISONBASE,
	USERHOSTBASE,

	FIND_COMMAND_FUNC,
			

	NICKNAME,
	IRC_VERSION,
	FROM_SERVER,
	CONNECTED_TO_SERVER,
	PRIMARY_SERVER,
	PARSING_SERVER_INDEX,
	NOW,
	START_TIME,
	IDLE_TIME,

	LOADING_GLOBAL,
	TARGET_WINDOW,
	CURRENT_WINDOW,
	INVISIBLE_LIST,
	
	MAIN_SCREEN,
	LAST_INPUT_SCREEN,
	OUTPUT_SCREEN,
	SCREEN_LIST,
	IRCLOG_FP,
	DOING_NOTICE,

	WINDOW_DISPLAY,
	STATUS_UPDATE_FLAG,
	TABKEY_ARRAY,
	AUTOREPLY_ARRAY,
	IDENTD_SOCKET,
				
	VAR_TCL_INTERP,
        LASTCLICKLINEDATA,
        CONTEXTX,
        CONTEXTY,
        GUIIPC,
	GUI_MUTEX_LOCK,
	GUI_MUTEX_UNLOCK,
	
/* input output functions */
	SERV_OPEN_FUNC,
	SERV_INPUT_FUNC,
	SERV_OUTPUT_FUNC,
	SERV_CLOSE_FUNC,
	CHECK_EXT_MAIL_STATUS,
	CHECK_EXT_MAIL,
	DEFAULT_OUTPUT_FUNCTION,
	DEFAULT_STATUS_OUTPUT_FUNCTION,

/* names.c */
    IS_HALFOP,

/* leave at the end */
	NUMBER_OF_GLOBAL_FUNCTIONS
};


/*
 * BXGlobalEntry: a type-checked union over every entry in the global
 * function/variable table.  modules.c assigns each slot the actual
 * function or address; modval.h macros read the typed member, so the
 * compiler verifies every interface instead of blindly casting to
 * Function_ptr.  Member names are the lowercase enum name + '_slot'.
 */
typedef union BXGlobalEntry BXGlobalEntry;
union BXGlobalEntry {
    void *generic;
    int (*module_version_check_slot)(unsigned long);
    int (*vsnprintf_slot)(char *, size_t, const char *, va_list);
    int (*snprintf_slot)(char *, size_t, const char *, ...);
    void * (*new_malloc_slot)(size_t, const char *, const char *, int);
    void * (*new_free_slot)(void *, const char *, const char *, int);
    void * (*new_realloc_slot)(void *, size_t, const char *, const char *, int);
    char * (*malloc_strcpy_slot)(char **, const char *, const char *, const char *, int);
    char * (*malloc_strcat_slot)(char **, const char *, const char *, const char *, int);
    char * (*malloc_str2cpy_slot)(char **, const char *, const char *);
    char * (*m_3dup_slot)(const char *, const char *, const char *);
    char * (*m_opendup_slot)(const char *, ...);
    char * (*m_s3cat_slot)(char **, const char *, const char *);
    char * (*m_s3cat_s_slot)(char **, const char *, const char *);
    char * (*m_3cat_slot)(char **, const char *, const char *);
    char * (*m_2dup_slot)(const char *, const char *);
    char * (*m_e3cat_slot)(char **, const char *, const char *);
    int (*my_stricmp_slot)(const char *, const char *);
    int (*my_strnicmp_slot)(const char *, const char *, size_t);
    int (*my_strnstr_slot)(const char *, const char *, size_t);
    char * (*chop_slot)(char *, int);
    char * (*strmcpy_slot)(char *, const char *, int);
    char * (*strmcat_slot)(char *, const char *, int);
    int (*scanstr_slot)(char *, char *);
    char * (*m_dupchar_slot)(int);
    size_t (*streq_slot)(const char *, const char *);
    size_t (*strieq_slot)(const char *, const char *);
    char * (*strmopencat_slot)(char *, int , ...);
    char * (*ov_strcpy_slot)(char *, const char *);
    char * (*upper_slot)(char *);
    char * (*lower_slot)(char *);
    char * (*stristr_slot)(const char *, const char *);
    char * (*rstristr_slot)(char *, char *);
    int (*word_count_slot)(char *);
    char * (*remove_trailing_spaces_slot)(char *);
    char * (*expand_twiddle_slot)(char *);
    char * (*check_nickname_slot)(char *);
    char * (*sindex_slot)(const char *, const char *);
    char * (*rsindex_slot)(const char *, const char *, const char *);
    int (*isnumber_slot)(const char *);
    char * (*rfgets_slot)(char *, int , FILE *);
    char * (*path_search_slot)(char *, char *);
    char   * (*double_quote_slot)(const char *, const char *, char *);
    void (*ircpanic_slot)(char *, ...);
    int (*end_strcmp_slot)(const char *, const char *, int);
    void (*beep_em_slot)(int);
    FILE * (*uzfopen_slot)(char **, char *, int);
    struct timeval (*func_get_time_slot)(struct timeval *);
    double (*time_diff_slot)(struct timeval , struct timeval);
    int (*time_to_next_minute_slot)(void);
    char * (*plural_slot)(int);
    char * (*my_ctime_slot)(time_t);
    size_t (*ccspan_slot)(const char *, int);
    char *(*ltoa_slot)(long );
    char *(*strformat_slot)(char *, const char *, int , char );
    char *(*matchingbracket_slot)(char *, char , char );
    int (*parse_number_slot)(char **);
    int (*splitw_slot)(char *, char ***);
    char *(*unsplitw_slot)(char ***, int );
    int (*check_val_slot)(char *);
    char *(*on_off_slot)(int );
    char *(*strextend_slot)(char *, char , int );
    const char *(*strfill_slot)(char , int );
    int (*empty_func_slot)(const char *);
    char *(*remove_brackets_slot)(const char *, const char *, int *);
    long (*my_atol_slot)(const char *);
    void (*strip_control_slot)(const char *, char *);
    int (*figure_out_address_slot)(char *, char **, char **, char **, char **, int *);
    char *(*strnrchr_slot)(char *, char , int );
    void (*mask_digits_slot)(char **);
    int (*charcount_slot)(const char *, char );
    char *(*strpcat_slot)(char *, const char *, ...);
    char *(*strcpy_nocolorcodes_slot)(char *, const char *);
    char *(*cryptit_slot)(const char *);
    char *(*stripdev_slot)(char *);
    size_t (*mangle_line_slot)(char *, int, size_t);
    char *(*m_strdup_slot)(const char *, const char *, const char *, const int );
    char *(*m_strcat_ues_slot)(char **, char *, int , const char *, const char *, const int );
    char *(*m_strndup_slot)(const char *, size_t, const char *, const char *, const int );
    char *(*malloc_sprintf_slot)(char **, const char *, ...);
    char *(*m_sprintf_slot)(const char *, ...);
    char *(*next_arg_slot)(char *, char **);
    char *(*new_next_arg_slot)(char *, char **);
    char *(*new_new_next_arg_slot)(char *, char **, char *);
    char *(*last_arg_slot)(char **);
    char *(*next_in_comma_list_slot)(char *, char **);
    u_long (*random_number_slot)(u_long);
    char *(*strsearch_slot)(const char *, const char *, int);
    char *(*move_to_word_slot)(const char *, int);
    char *(*move_word_rel_slot)(const char *, char **, int );
    char *(*extract_slot)(char *, int , int );
    char *(*extract2_slot)(const char *, int , int );
    int (*wild_match_slot)(const char *, const char *);
    int (*connect_by_number_slot)(char *, unsigned short *, int , int , int );
    struct sockaddr_foobar *(*lookup_host_slot)(const char *);
    char *(*host_to_ip_slot)(const char *);
    char *(*ip_to_host_slot)(const char *);
    char *(*one_to_another_slot)(const char *);
    int (*set_blocking_slot)(int );
    int (*set_non_blocking_slot)(int );
    void (*add_to_list_slot)(List **, List *);
    void (*add_to_list_ext_slot)(List **, List *, int (*)(List *, List *));
    List *(*find_in_list_slot)(List **, char *, int);
    List *(*find_in_list_ext_slot)(List **, char *, int, int (*)(List *, char *));
    List *(*remove_from_list__slot)(List **, char *);
    List *(*remove_from_list_ext_slot)(List **, char *, int (*)(List *, char *));
    List *(*removewild_from_list_slot)(List **, char *);
    List *(*list_lookup_slot)(List **, char *, int, int);
    List *(*list_lookup_ext_slot)(List **, char *, int, int, int (*)(List *, char *));
    Array_item *(*add_to_array_slot)(Array *, Array_item *);
    Array_item *(*remove_from_array_slot)(Array *, char *);
    Array_item *(*array_pop_slot)(Array *, int);
    Array_item *(*remove_all_from_array_slot)(Array *, char *);
    Array_item *(*array_lookup_slot)(Array *, char *, int, int );
    Array_item *(*find_array_item_slot)(Array *, char *, int *, int *);
    void *(*find_fixed_array_item_slot)(void *, size_t, int, const char *, int *, int *);
    void (*put_it_slot)(const char *, ...);
    void (*bitchsay_slot)(const char *, ...);
    void (*yell_slot)(const char *, ...);
    void (*add_to_log_slot)(FILE *, time_t, const char *, int );
    int (*bsd_glob_slot)(const char *, int, int (*)(const char *, int), glob_t *);
    void (*bsd_globfree_slot)(glob_t *);
    void (*my_encrypt_slot)(char *, int , const char *);
    void (*my_decrypt_slot)(char *, int , const char *);
    ChannelList *(*prepare_command_slot)(int *, char *, int);
    char *(*convert_output_format_slot)(const char *, const char *, ...);
    void (*userage_slot)(char *, char *);
    void (*send_text_slot)(const char *, const char *, unsigned);
    void (*func_load_slot)(char *, char *, char *, char *);
    char *(*update_clock_slot)(int );
    char *(*pasteargs_slot)(char **, int );
    int (*breakargs_slot)(char *, char **, char **, int );
    unsigned long (*set_lastlog_msg_level_slot)(unsigned long );
    void (*split_ctcp_slot)(char *, char *, char *);
    char *(*random_str_slot)(int , int );
    int (*dcc_printf_slot)(int, char *, ...);
    char **(*prepare_display_slot)(const char *, int , int *, int );
    void (*add_to_window_slot)(Window *, const char *);
    char *(*skip_incoming_mirc_slot)(char *);
    void (*add_to_screen_slot)(char *);
    char **(*split_up_line_slot)(const char *, int );
    int (*output_line_slot)(const char *);
    int (*output_with_count_slot)(const char *, int , int );
    void (*scroll_window_slot)(Window *);
    void (*cursor_not_in_display_slot)(Screen *);
    void (*cursor_in_display_slot)(Window *);
    int (*is_cursor_in_display_slot)(Screen *);
    void (*repaint_window_slot)(Window *, int, int);
    void (*kill_screen_slot)(Screen *);
    void (*xterm_settitle_slot)(void);
    void (*add_wait_prompt_slot)(char *, void (*)(char *, char *), char *, int , int );
    char *(*skip_ctl_c_seq_slot)(const char *, int *, int *, int );
    char *(*strip_ansi_slot)(const char *);
    Screen * (*create_new_screen_slot)(void);
    Window * (*create_additional_screen_slot)(void);
    void (*free_formats_slot)(Window *);
    void (*set_screens_current_window_slot)(Screen *, Window *);
    Window *(*new_window_slot)(struct ScreenStru *);
    void (*delete_window_slot)(Window *);
    int (*traverse_all_windows_slot)(Window **);
    void (*add_to_invisible_list_slot)(Window *);
    void (*remove_window_from_screen_slot)(Window *);
    void (*recalculate_window_positions_slot)(struct ScreenStru *);
    void (*move_window_slot)(Window *, int);
    void (*resize_window_slot)(int, Window *, int);
    void (*redraw_all_windows_slot)(void);
    void (*rebalance_windows_slot)(struct ScreenStru *);
    void (*recalculate_windows_slot)(struct ScreenStru *);
    void (*update_all_windows_slot)(void);
    void (*goto_window_slot)(Screen *, int);
    void (*hide_bx_window_slot)(Window *);
    void (*func_swap_last_window_slot)(char , char *);
    void (*func_swap_next_window_slot)(char , char *);
    void (*func_swap_previous_window_slot)(char , char *);
    void (*show_window_slot)(Window *);
    char *(*get_status_by_refnum_slot)(unsigned , unsigned );
    int (*get_visible_by_refnum_slot)(char *);
    Window *(*get_window_by_desc_slot)(const char *);
    Window *(*get_window_by_refnum_slot)(unsigned );
    Window *(*get_window_by_name_slot)(const char *);
    void (*func_next_window_slot)(char , char *);
    void (*func_previous_window_slot)(char , char *);
    void (*update_window_status_slot)(Window *, int );
    void (*update_all_status_slot)(Window *, char *, int);
    void (*update_window_status_all_slot)(void );
    int (*status_update_slot)(int );
    void (*set_prompt_by_refnum_slot)(unsigned , char *);
    char *(*get_prompt_by_refnum_slot)(unsigned );
    char *(*get_target_by_refnum_slot)(unsigned );
    char *(*get_target_cmd_by_refnum_slot)(u_int);
    Window *(*get_window_target_by_desc_slot)(char *);
    int (*is_current_channel_slot)(const char *, int , int );
    const char *(*set_current_channel_by_refnum_slot)(unsigned , char *);
    char *(*get_current_channel_by_refnum_slot)(unsigned );
    char *(*get_refnum_by_window_slot)(const Window *);
    int (*is_bound_to_window_slot)(const Window *, const char *);
    Window *(*get_window_bound_channel_slot)(const char *);
    int (*is_bound_anywhere_slot)(const char *);
    int (*is_bound_slot)(const char *, int );
    void (*unbind_channel_slot)(const char *, int );
    char *(*get_bound_channel_slot)(Window *);
    int (*get_window_server_slot)(unsigned );
    void (*set_window_server_slot)(int , int , int );
    void (*window_check_servers_slot)(int );
    void (*change_window_server_slot)(int , int );
    void (*set_level_by_refnum_slot)(unsigned , unsigned long );
    void (*message_to_slot)(unsigned long );
    void (*clear_window_slot)(Window *);
    void (*clear_all_windows_slot)(int , int );
    void (*clear_window_by_refnum_slot)(unsigned );
    void (*unclear_window_by_refnum_slot)(unsigned );
    void (*set_scroll_lines_slot)(Window *, char *, int);
    void (*set_continued_lines_slot)(Window *, char *, int);
    unsigned (*current_refnum_slot)(void );
    int (*number_of_windows_on_screen_slot)(Window *);
    void (*set_scrollback_size_slot)(Window *, char *, int);
    int (*is_window_name_unique_slot)(char *);
    char *(*get_nicklist_by_window_slot)(Window *);
    void (*scrollback_backwards_lines_slot)(int );
    void (*scrollback_forwards_lines_slot)(int );
    void (*scrollback_forwards_slot)(char , char *);
    void (*scrollback_backwards_slot)(char , char *);
    void (*scrollback_end_slot)(char , char *);
    void (*scrollback_start_slot)(char , char *);
    void (*set_hold_mode_slot)(Window *, int, int);
    int (*unhold_windows_slot)(void );
    void (*func_unstop_all_windows_slot)(char , char *);
    void (*reset_line_cnt_slot)(Window *, char *, int);
    void (*func_toggle_stop_screen_slot)(char , char *);
    void (*flush_everything_being_held_slot)(Window *);
    int (*unhold_a_window_slot)(Window *);
    void (*recalculate_window_cursor_slot)(Window *);
    void (*make_window_current_slot)(Window *);
    void (*clear_scrollback_slot)(Window *);
    void (*set_display_target_slot)(const char *, unsigned long );
    void (*save_display_target_slot)(const char **, unsigned long *);
    void (*restore_display_target_slot)(const char *, unsigned long );
    void (*reset_display_target_slot)(void );
    void (*build_status_slot)(Window *, char *, int);
    int (*hook_slot)(int, char *, ...);
    void (*func_update_input_slot)(int );
    void (*cursor_to_input_slot)(void );
    void (*set_input_slot)(char *);
    char *(*get_input_slot)(void );
    char *(*get_input_prompt_slot)(void );
    void (*set_input_prompt_slot)(Window *, char *, int);
    void (*addtabkey_slot)(char *, char *, int );
    NickTab *(*gettabkey_slot)(int, int, char *);
    NickTab *(*getnextnick_slot)(int, char *, char *, char *);
    char *(*getchannick_slot)(char *, char *);
    NickList *(*lookup_nickcompletion_slot)(ChannelList *, char *);
    int (*add_completion_type_slot)(char *, int , enum completion );
    int (*is_channel_slot)(const char *);
    char *(*make_channel_slot)(char *);
    int (*is_chanop_slot)(char *, char *);
    int (*is_halfop_slot)(char *, char *);
    int (*im_on_channel_slot)(char *, int );
    int (*is_on_channel_slot)(char *, int , char *);
    ChannelList *(*add_channel_slot)(char *, int, int);
    ChannelList *(*add_to_channel_slot)(char *, char *, int, int, int, char *, char *, char *, int, int);
    char *(*get_channel_key_slot)(char *, int );
    char *(*func_recreate_mode_slot)(ChannelList *);
    char *(*func_compress_modes_slot)(ChannelList *, int, char *, char *);
    int (*func_got_ops_slot)(int, ChannelList *);
    char *(*get_channel_bans_slot)(char *, int , int );
    char *(*get_channel_mode_slot)(char *, int );
    void (*clear_bans_slot)(ChannelList *);
    void (*remove_channel_slot)(const char *);
    void (*remove_from_channel_slot)(char *, char *, int , int , char *);
    void (*rename_nick_slot)(char *, char *, int );
    int (*get_channel_oper_slot)(char *, int );
    int (*get_channel_halfop_slot)(char *, int );
    int (*get_channel_voice_slot)(char *, int );
    char *(*fetch_userhost_slot)(int , char *);
    char *(*create_channel_list_slot)(Window *);
    void (*flush_channel_stats_slot)(void );
    ChannelList *(*lookup_channel_slot)(const char *, int, int);
    NickList *(*find_nicklist_in_channellist_slot)(const char *, ChannelList *, int);
    void (*add_nicklist_to_channellist_slot)(NickList *, ChannelList *);
    NickList *(*next_nicklist_slot)(ChannelList *, NickList *);
    List *(*next_namelist_slot)(HashEntry *, List *, unsigned int);
    void (*add_name_to_genericlist_slot)(char *, HashEntry *, unsigned int);
    List *(*find_name_in_genericlist_slot)(const char *, HashEntry *, unsigned int, int);
    void (*add_whowas_userhost_channel_slot)(WhowasList *, WhowasWrapList *);
    WhowasList *(*find_userhost_channel_slot)(char *, char *, int, WhowasWrapList *);
    WhowasList *(*next_userhost_slot)(WhowasWrapList *, WhowasList *);
    NickList *(*sorted_nicklist_slot)(ChannelList *, int);
    void (*clear_sorted_nicklist_slot)(NickList **);
    Flooding *(*add_name_to_floodlist_slot)(char *, char *, char *, HashEntry *, unsigned int);
    Flooding *(*find_name_in_floodlist_slot)(char *, char *, HashEntry *, unsigned int, int);
    int (*remove_oldest_whowas_hashlist_slot)(WhowasWrapList *, time_t, int);
    char *(*fget_string_var_slot)(enum FSET_TYPES );
    void (*fset_string_var_slot)(enum FSET_TYPES , char *);
    char *(*get_wset_string_var_slot)(WSet *, int);
    void (*set_wset_string_var_slot)(WSet *, int, char *);
    int (*get_cset_int_var_slot)(CSetList *, int);
    void (*set_cset_int_var_slot)(CSetList *, int, int);
    char *(*get_cset_str_var_slot)(CSetList *, int);
    void (*set_cset_str_var_slot)(CSetList *, int, const char *);
    int (*get_dllint_var_slot)(char *);
    void (*set_dllint_var_slot)(char *, unsigned int );
    char *(*get_dllstring_var_slot)(char *);
    void (*set_dllstring_var_slot)(char *, char *);
    void (*save_dllvar_slot)(FILE *, char *);
    int (*get_int_var_slot)(enum VAR_TYPES );
    void (*set_int_var_slot)(enum VAR_TYPES , unsigned int );
    char *(*get_string_var_slot)(enum VAR_TYPES );
    void (*set_string_var_slot)(enum VAR_TYPES , char *);
    int (*add_module_proc_slot)(unsigned int , char *, char *, char *, int , int , void *, void *);
    int (*remove_module_proc_slot)(unsigned int , char *, char *, char *);
    char *(*add_timer_slot)(int , char *, double , long , int (*)(void *, char *), char *, char *, int , char *);
    int (*delete_timer_slot)(char *);
    void (*delete_all_timers_slot)(void );
    void (*send_to_server_slot)(const char *, ...);
    void (*queue_send_to_server_slot)(int, const char *, ...);
    void (*my_send_to_server_slot)(int, const char *, ...);
    void (*get_connected_slot)(int , int );
    int (*connect_to_server_by_refnum_slot)(int , int );
    void (*close_server_slot)(int , char *);
    int (*is_server_connected_slot)(int );
    void (*flush_server_slot)(void );
    void (*server_is_connected_slot)(int , int );
    int (*is_server_open_slot)(int );
    void (*close_all_server_slot)(void );
    int (*read_server_file_slot)(char *);
    void (*add_to_server_list_slot)(char *, int , char *, char *, char *, int , int );
    int (*build_server_list_slot)(char *);
    void (*display_server_list_slot)(void );
    void (*parse_server_info_slot)(char *, char **, char **, char **, char **);
    int (*server_list_size_slot)(void );
    int (*find_server_refnum_slot)(char *, char **);
    int (*find_in_server_list_slot)(char *, int );
    int (*parse_server_index_slot)(char *);
    void (*set_server_redirect_slot)(int , const char *);
    char *(*get_server_redirect_slot)(int );
    int (*check_server_redirect_slot)(char *);
    void (*fudge_nickname_slot)(int);
    void (*reset_nickname_slot)(int );
    void (*set_server_cookie_slot)(int , char *);
    void (*update_server_umode_slot)(int , char , int );
    void (*set_server_motd_slot)(int , int );
    void (*set_server_operator_slot)(int , int );
    void (*set_server_itsname_slot)(int , char *);
    void (*set_server_version_slot)(int , int );
    void (*set_server_lag_slot)(int , int );
    char *(*set_server_password_slot)(int , char *);
    void (*set_server_nickname_slot)(int , char *);
    void (*set_server2_8_slot)(int , int );
    void (*set_server_away_slot)(int , char *, int );
    char *(*get_server_cookie_slot)(int );
    char *(*get_server_nickname_slot)(int );
    char *(*get_server_name_slot)(int );
    char *(*get_server_itsname_slot)(int );
    int (*get_server_motd_slot)(int );
    int (*get_server_operator_slot)(int );
    int (*get_server_version_slot)(int );
    int (*get_server_umode_slot)(int , char);
    int (*get_server_port_slot)(int );
    int (*get_server_lag_slot)(int );
    int (*get_server2_8_slot)(int );
    char *(*get_umode_slot)(int );
    char *(*get_server_away_slot)(int );
    char *(*get_server_network_slot)(int );
    char *(*get_pending_nickname_slot)(int );
    void (*server_disconnect_slot)(int , char *);
    Server *(*get_server_list_slot)(void);
    ChannelList *(*get_server_channels_slot)(int);
    void (*set_server_last_ctcp_time_slot)(int , time_t);
    time_t (*get_server_last_ctcp_time_slot)(int);
    void (*set_server_trace_flag_slot)(int , int );
    int (*get_server_trace_flag_slot)(int );
    int (*get_server_read_slot)(int );
    int (*get_server_linklook_slot)(int );
    void (*set_server_linklook_slot)(int , int );
    int (*get_server_stat_flag_slot)(int );
    void (*set_server_stat_flag_slot)(int , int );
    time_t (*get_server_linklook_time_slot)(int );
    void (*set_server_linklook_time_slot)(int , time_t);
    int (*get_server_trace_kill_slot)(int );
    void (*set_server_trace_kill_slot)(int , int );
    void (*add_server_channels_slot)(int, ChannelList *);
    void (*set_server_channels_slot)(int, ChannelList *);
    void (*send_msg_to_channels_slot)(int, const char *);
    void (*send_msg_to_nicks_slot)(ChannelList *, int, char *);
    int (*is_server_queue_slot)(void );
    int (*add_socketread_slot)(int, int, unsigned long, char *, void (*)(int), void (*)(int));
    void (*add_sockettimeout_slot)(int , time_t, void *);
    void (*close_socketread_slot)(int );
    SocketList *(*get_socket_slot)(int );
    unsigned long (*set_socketflags_slot)(int , unsigned long );
    unsigned long (*get_socketflags_slot)(int );
    int (*check_socket_slot)(int );
    int (*read_sockets_slot)(int , char *, int );
    int (*write_sockets_slot)(int , char *, int , int );
    int (*get_max_fd_slot)(void );
    int (*new_close_slot)(int );
    int (*new_open_slot)(int );
    int (*dgets_slot)(char *, int , int , int , void *);
    void *(*get_socketinfo_slot)(int );
    void (*set_socketinfo_slot)(int , void *);
    int (*set_socketwrite_slot)(int );
    int (*is_other_flood_slot)(ChannelList *, NickList *, enum flood_type, int *);
    int (*check_flooding_slot)(char *, enum flood_type, char *, char *);
    int (*flood_prot_slot)(char *, char *, enum flood_type, int, char *);
    char *(*next_unit_slot)(char *, const char *, int *, int );
    char *(*parse_inline_slot)(char *, const char *, int *);
    char *(*expand_alias_slot)(const char *, const char *, int *, char **);
    char *(*alias_special_char_slot)(char **, char *, const char *, char *, int *);
    void (*parse_line_slot)(const char *, char *, const char *, int , int , int );
    int (*parse_command_func_slot)(char *, int , char *);
    void (*make_local_stack_slot)(char *);
    void (*destroy_local_stack_slot)(void );
    DCC_int *(*dcc_create_func_slot)(char *, char *, char *, unsigned long, int, int, unsigned long, void (*)(int));
    SocketList *(*find_dcc_func_slot)(const char *, const char *, const char *, int, int, int, int);
    void (*erase_dcc_info_slot)(int, int, char *, ...);
    int (*add_dcc_bind_slot)(char *, char *, const struct dcc_ops *);
    int (*remove_dcc_bind_slot)(char *, int );
    int (*remove_all_dcc_binds_slot)(const char *);
    int (*get_active_count_slot)(void );
    int (*get_num_queue_slot)(void );
    int (*add_to_queue_slot)(char *, char *, pack *);
    void (*dcc_filesend_slot)(char *, char *);
    void (*dcc_resend_slot)(char *, char *);
    void (*dcc_chat_socketread_slot)(int);
    void (*dcc_send_socketread_slot)(int);
    void (*irc_exit_func_slot)(int, char *, char *, ...);
    void (*irc_io_func_slot)(const char *);
    const IrcCommand *(*find_command_func_slot)(const char *, int *);
    void (*lock_stack_frame_slot)(void );
    void (*unlock_stack_frame_slot)(void );
    void (*userhostbase_slot)(char *, void (*)(UserhostItem *, char *, char *), int, char *, ...);
    void (*isonbase_slot)(char *, void (*)(char *, char *));
    void (*whobase_slot)(char *, void (*)(WhoEntry *, char *, char **), void (*)(WhoEntry *, char *, char **), char *, ...);
    Window *(*add_to_window_list_slot)(struct ScreenStru *, Window *);
    char ** nickname_slot;
    char ** irc_version_slot;
    int * from_server_slot;
    int * connected_to_server_slot;
    int * primary_server_slot;
    int * parsing_server_index_slot;
    time_t * now_slot;
    time_t * start_time_slot;
    time_t * idle_time_slot;
    int * loading_global_slot;
    Window ** target_window_slot;
    Window ** current_window_slot;
    Window ** invisible_list_slot;
    Screen ** main_screen_slot;
    Screen ** last_input_screen_slot;
    Screen ** output_screen_slot;
    Screen ** screen_list_slot;
    FILE ** irclog_fp_slot;
    int * window_display_slot;
    int * status_update_flag_slot;
    NickTab ** tabkey_array_slot;
    NickTab ** autoreply_array_slot;
    int * identd_socket_slot;
    int * doing_notice_slot;
    void (*default_output_function_slot)(Window *, const char *);
    int (**serv_open_func_slot)(int, unsigned long, int);
    int (**serv_input_func_slot)(int, char *, int, int, int);
    int (**serv_output_func_slot)(int, int, char *, int);
    int (**serv_close_func_slot)(int, unsigned long, int);
    int (*check_ext_mail_status_slot)(void);
    char *(*check_ext_mail_slot)(void);
    struct Tcl_Interp * var_tcl_interp_slot;
    char ** lastclicklinedata_slot;
    int * contextx_slot;
    int * contexty_slot;
    int * guiipc_slot;
    void (*gui_mutex_lock_slot)(void);
    void (*gui_mutex_unlock_slot)(void);
    struct sockaddr_foobar *(*resolv_slot)(const char *);
    char *(*lookup_ip_slot)(const char *);
    void ** default_status_output_function_slot;
};
extern BXGlobalEntry global_table[];
extern IrcCommand irc_command[];

#endif
