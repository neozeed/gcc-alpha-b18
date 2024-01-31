/*
 * stdlib.h
 *
 * Definitions for common types, variables, and functions.
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

#ifndef _STDLIB_H_
#define _STDLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This seems like a convenient place to declare these variables, which
 * give programs using WinMain (or main for that matter) access to main-ish
 * argc and argv. _environ is a pointer to a table of environment variables.
 * NOTE: Strings in argv and environ are ANSI strings.
 */
extern int	__argc;
extern char**	__argv;
extern char**	_environ;

#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>

#ifdef	__GNUC__
#define	_ATTRIB_NORETURN	__attribute__ ((noreturn))
#else	/* Not __GNUC__ */
#define	_ATTRIB_NORETURN
#endif	/* __GNUC__ */

double	atof	(const char* szNumber);
int	atoi	(const char* szNumber);
long	atol	(const char* szNumber);


double	strtod	(const char* szNumber, char** pszAfterNumber);
double	wcstod	(const wchar_t* wsNumber, wchar_t** pwsAfterNumber);
long	strtol	(const char* szNumber, char** pszAfterNumber, int nBase);
long	wcstol	(const wchar_t* wsNumber, wchar_t** pwsAfterNumber, int nBase);

unsigned long	strtoul	(const char* szNumber, char** pszAfterNumber,
			int nBase);
unsigned long	wcstoul (const wchar_t* wsNumber, wchar_t** pwsAfterNumber,
			int nBase);

size_t	wcstombs	(char* mbsDest, const wchar_t* wsConvert, size_t size);
int	wctomb		(char* mbDest, wchar_t wc);

int	mblen		(const char* mbs, size_t sizeString);
size_t	mbstowcs	(wchar_t* wcaDest, const char* mbsConvert,
			 size_t size);
int	mbtowc		(wchar_t* wcDest, const char* mbConvert, size_t size);


/*
 * RAND_MAX is the maximum value that may be returned by rand.
 * The minimum is zero.
 */
#define	RAND_MAX	0x7FFF

int	rand	();
void	srand	(unsigned int nSeed);


void*	calloc	(size_t sizeObjCnt, size_t sizeObject);
void*	malloc	(size_t	sizeObject);
void*	realloc	(void* pObject, size_t sizeNew);
void*	free	(void* pObject);

/* These values may be used as exit status codes. */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	-1

void	abort	() _ATTRIB_NORETURN;
void	exit	(int nStatus) _ATTRIB_NORETURN;
int	atexit	(void (*pfuncExitProcessing)());

int	system	(const char* szCommand);
char*	getenv	(const char* szVarName);

typedef	int (*_pfunccmp_t)(const void*, const void*);

void*	bsearch	(const void* pKey, const void* pBase, size_t cntObjects,
		size_t sizeObject, _pfunccmp_t pfuncCmp);
void	qsort	(const void* pBase, size_t cntObjects, size_t sizeObject,
		_pfunccmp_t pfuncCmp);

int	abs	(int n);
long	labs	(long n);

/*
 * div_t and ldiv_t are structures used to return the results of div and
 * ldiv.
 */
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

div_t	div	(int nNumerator, int nDenominator);
ldiv_t	ldiv	(long lNumerator, long lDenominator);


#ifndef	_STRICT_ANSI

/*
 * NOTE: Officially the three following functions are obsolete. The Win32 API
 *       functions SetErrorMode, Beep and Sleep are their replacements.
 */
void	_beep (unsigned int, unsigned int);
void	_seterrormode (int nMode);
void	_sleep (unsigned long ulTime);

void	_exit	(int nStatus) _ATTRIB_NORETURN;

int	_putenv	(const char* szNameEqValue);
void	_searchenv (const char* szFileName, const char* szVar,
		char* szFullPathBuf);

#ifndef	_NO_OLDNAMES
int	putenv (const char* szNameEqValue);
void	searchenv (const char* szFileName, const char* szVar,
		char* szFullPathBuf);
#endif	/* Not _NO_OLDNAMES */

#endif	/* Not _STRICT_ANSI */

/*
 * Undefine the no return attribute used in some function definitions
 */
#undef	_ATTRIB_NORETURN

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H_ */
