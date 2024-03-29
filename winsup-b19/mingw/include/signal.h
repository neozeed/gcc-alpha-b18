/* 
 * signal.h
 *
 * A way to set handlers for exceptional conditions (also known as signals).
 *
 * This header file is meant for use with CRTDLL.DLL as included with
 * Windows 95(tm) and Windows NT(tm). In conjunction with other versions
 * of the standard C library things may or may not work so well.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef	_SIGNAL_H_
#define	_SIGNAL_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * The prototypes (below) are the easy part. The hard part is figuring
 * out what signals are available and what numbers they are assigned
 * along with appropriate values of SIG_DFL and SIG_IGN.
 */

/*
 * A pointer to a signal handler function. A signal handler takes a
 * single int, which is the signal it handles.
 */
typedef	void (*_p_sig_fn_t)(int nSig);

/*
 * These are special values of signal handler pointers which are
 * used to send a signal to the default handler (SIG_DFL), ignore
 * the signal (SIG_IGN), or indicate an error return (SIG_ERR).
 */
#define	SIG_DFL	((_p_sig_fn_t) 0)
#define	SIG_IGN	((_p_sig_fn_t) 1)
#define	SIG_ERR ((_p_sig_fn_t) -1)

/*
 * The actual signal values. Using other values with signal
 * produces a SIG_ERR return value.
 *
 * NOTE: SIGINT is produced when the user presses Ctrl-C.
 *       SIGILL has not been tested.
 *       SIGFPE doesn't seem to work?
 *       SIGSEGV does not catch writing to a NULL pointer (that shuts down
 *               your app; can you say "segmentation violation core dump"?).
 *       SIGTERM comes from what kind of termination request exactly?
 *       SIGBREAK is indeed produced by pressing Ctrl-Break.
 *       SIGABRT is produced by calling abort.
 */
#define	SIGINT		2	/* Interactive attention */
#define	SIGILL		4	/* Illegal instruction */
#define	SIGFPE		8	/* Floating point error */
#define	SIGSEGV		11	/* Segmentation violation */
#define	SIGTERM		15	/* Termination request */
#define SIGBREAK	21	/* Control-break */
#define	SIGABRT		22	/* Abnormal termination (abort) */

/*
 * Call signal to set the signal handler for signal sig to the
 * function pointed to by handler. Returns a pointer to the
 * previous handler, or SIG_ERR if an error occurs. Initially
 * unhandled signals defined above will return SIG_DFL.
 */
_p_sig_fn_t	signal(int sig, _p_sig_fn_t handler);

/*
 * Raise the signal indicated by sig. Returns non-zero on success.
 */
int	raise (int sig);

#ifdef	__cplusplus
}
#endif

#endif
