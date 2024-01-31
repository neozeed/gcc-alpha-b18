/* sys/strace.h */

/* This file contains routines for tracing system calls and other internal
   phenomenon.

   When tracing system calls, try to use the same style throughout:

   result = syscall (arg1, arg2, arg3) [optional extra stuff]

   If a system call can block (eg: read, write, wait), print another message
   before hanging so the user will know why the program has stopped.

   Note: __seterrno will also print a trace message.  Have that printed
   *first*.  This will make it easy to always know what __seterrno is
   refering to.  For the same reason, try not to have __seterrno messages
   printed alone.
*/

#ifndef _SYS_STRACE_H
#define _SYS_STRACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Bitmasks of tracing messages to print.  */

#define _STRACE_ALL	 0x0001	/* so behaviour of strace=1 is unchanged */
#define _STRACE_FLUSH	 0x0002	/* flush output buffer after every message */
#define _STRACE_INHERIT  0x0004	/* children inherit mask from parent */
#define _STRACE_UHOH	 0x0008	/* unusual or weird phenomenon */
#define _STRACE_SYSCALL	 0x0010	/* system calls */
#define _STRACE_STARTUP	 0x0020	/* argc/envp printout at startup */
#define _STRACE_DEBUG    0x0040	/* info to help debugging */
#define _STRACE_PARANOID 0x0080	/* paranoid info */
#define _STRACE_TERMIOS	 0x0100	/* info for debugging termios stuff */
#define _STRACE_SELECT	 0x0200	/* info on ugly select internals */
#define _STRACE_WM	 0x0400	/* trace windows messages (enable _strace_wm) */
#define _STRACE_SIGP	 0x0800	/* trace signal and process handling */
#define _STRACE_NEWFILE	 0x1000 /* open a new file for strace */
#define _STRACE_EXITDUMP 0x4000 /* dump strace cache on exit */
#define _STRACE_CACHE	 0x8000 /* cache strace messages */

/* Return the current strace mask.  */
int strace (void);

/* Dump cached strace data, if any */
void strace_dump (void);

/* Output message to strace log */
void strace_printf (const char *, ...);

void _strace_wm (int message, int word, int lon);

#define strace_printf_wrap(what, fmt, args...) \
    ({\
	if (strace() &((_STRACE_ ## what)|1)) \
	  strace_printf("%F: " fmt, __PRETTY_FUNCTION__ , ## args); \
    })
#define debug_printf(fmt, args...) strace_printf_wrap(DEBUG, fmt , ## args)
#define syscall_printf(fmt, args...) strace_printf_wrap(SYSCALL, fmt , ## args)
#define paranoid_printf(fmt, args...) strace_printf_wrap(PARANOID, fmt , ## args)
#define termios_printf(fmt, args...) strace_printf_wrap(TERMIOS, fmt , ## args)
#define select_printf(fmt, args...) strace_printf_wrap(SELECT, fmt , ## args)
#define wm_printf(fmt, args...) strace_printf_wrap(WM, fmt , ## args)
#define sigproc_printf(fmt, args...) strace_printf_wrap(SIGP, fmt , ## args)

#ifdef __cplusplus
}
#endif

#endif /* _SYS_STRACE_H */
