/* 
 * process.h
 *
 * Function calls for spawning child processes.
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

#ifndef	_PROCESS_H_
#define	_PROCESS_H_

/*
 * This file is not part of ANSI.
 */
#ifndef	_STRICT_ANSI

#ifdef	__cplusplus
extern "C" {
#endif

void	_cexit();
void	_c_exit();

/*
 * TODO: Constants WAIT_CHILD and WAIT_GRANDCHILD.
 */
int	_cwait (int* pnStatus, int nPID, int nAction);

int	_getpid();

int	_execl		(const char* szPath, const char* szArgv0, ...);
int	_execle		(const char* szPath, const char* szArgv0, ...);
int	_execlp		(const char* szPath, const char* szArgv0, ...);
int	_execlpe	(const char* szPath, const char* szArgv0, ...);
int	_execv		(const char* szPath, char* const* szaArgv);
int	_execve		(const char* szPath, char* const* szaArgv,
			 char* const* szaEnv);
int	_execvp		(const char* szPath, char* const* szaArgv);
int	_execvpe	(const char* szPath, char* const* szaArgv,
			 char* const* szaEnv);

/*
 * TODO: Mode constants P_... for spawn functions.
 */

int	_spawnl		(int nMode, const char* szPath, const char* szArgv0,
			 ...);
int	_spawnle	(int nMode, const char* szPath, const char* szArgv0,
			 ...);
int	_spawnlp	(int nMode, const char* szPath, const char* szArgv0,
			 ...);
int	_spawnlpe	(int nMode, const char* szPath, const char* szArgv0,
			 ...);
int	_spawnv		(int nMode, const char* szPath, char* const* szaArgv);
int	_spawnve	(int nMode, const char* szPath, char* const* szaArgv,
			 char* const* szaEnv);
int	_spawnvp	(int nMode, const char* szPath, char* const* szaArgv);
int	_spawnvpe	(int nMode, const char* szPath, char* const* szaArgv,
			 char* const* szaEnv);

/*
 * The functions _beginthreadex and _endthreadex are not provided by CRTDLL.
 * NOTE: Apparently _endthread calls CloseHandle on the handle of the thread,
 * making for race conditions if you are not careful. Basically you have to
 * make sure that no-one is going to do *anything* with the thread handle
 * after the thread calls _endthread or returns from the thread function.
 *
 * NOTE: No old names for these functions. Use the underscore.
 */
unsigned long
	_beginthread	(void (__cdecl *pfuncStart)(void *),
			 unsigned unStackSize, void* pArgList);
void	_endthread	();


#ifndef	_NO_OLDNAMES
/*
 * Functions without the leading underscore, for portability. These functions
 * live in liboldnames.a.
 * NOTE: execl... and spawnl... are more than simple wrappers, and they
 * actually end up calling execv... or spawnv... (and allocating memory).
 */
int	cwait (int* pnStatus, int nPID, int nAction);
int	getpid ();
int	execl (const char* szPath, const char* szArgv0, ...);
int	execle (const char* szPath, const char* szArgv0, ...);
int	execlp (const char* szPath, const char* szArgv0, ...);
int	execlpe (const char* szPath, const char* szArgv0, ...);
int	execv (const char* szPath, char* const* szaArgv);
int	execve (const char* szPath, char* const* szaArgv, char* const* szaEnv);
int	execvp (const char* szPath, char* const* szaArgv);
int	execvpe (const char* szPath, char* const* szaArgv,
	         char* const* szaEnv);
int	spawnl (int nMode, const char* szPath, const char* szArgv0, ...);
int	spawnle (int nMode, const char* szPath, const char* szArgv0, ...);
int	spawnlp (int nMode, const char* szPath, const char* szArgv0, ...);
int	spawnlpe (int nMode, const char* szPath, const char* szArgv0, ...);
int	spawnv (int nMode, const char* szPath, char* const* szaArgv);
int	spawnve (int nMode, const char* szPath, char* const* szaArgv,
	         char* const* szaEnv);
int	spawnvp (int nMode, const char* szPath, char* const* szaArgv);
int	spawnvpe (int nMode, const char* szPath, char* const* szaArgv,
	          char* const* szaEnv);
#endif	/* Not _NO_OLDNAMES */

#ifdef	__cplusplus
}
#endif

#endif	/* Not _STRICT_ANSI */

#endif	/* _PROCESS_H_ not defined */
