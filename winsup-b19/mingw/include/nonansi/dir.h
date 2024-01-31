/*
 * dir.h
 *
 * Functions for working with directories and path names.
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

#ifndef _STRICT_ANSI

#ifndef _DIR_H_
#define	_DIR_H_

#include <stdio.h>	/* To get FILENAME_MAX... ugly. */
#include <sys/types.h>	/* To get time_t. */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Attributes of files as returned by _findfirst et al.
 */
#define	_A_NORMAL	0x00000000
#define	_A_RDONLY	0x00000001
#define	_A_HIDDEN	0x00000002
#define	_A_SYSTEM	0x00000004
#define	_A_VOLID	0x00000008
#define	_A_SUBDIR	0x00000010
#define	_A_ARCH		0x00000020

#ifndef	_FSIZE_T_DEFINED
typedef	unsigned long	_fsize_t;
#define _FSIZE_T_DEFINED
#endif

/*
 * The following structure is filled in by _findfirst or _findnext when
 * they succeed in finding a match.
 */
struct _finddata_t
{
	unsigned	attrib;		/* Attributes, see constants above. */
	time_t		time_create;
	time_t		time_access;	/* always midnight local time */
	time_t		time_write;
	_fsize_t	size;
	char		name[FILENAME_MAX];	/* may include spaces. */
};

/*
 * Functions for searching for files. _findfirst returns -1 if no match
 * is found. Otherwise it returns a handle to be used in _findnext and
 * _findclose calls. _findnext also returns -1 if no match could be found,
 * and 0 if a match was found. Call _findclose when you are finished.
 */
int	_findfirst (const char* szFilespec, struct _finddata_t* find);
int	_findnext (int nHandle, struct _finddata_t* find);
int	_findclose (int nHandle);

int	_chdir (const char* szPath);
char*	_getcwd (char* caBuffer, int nBufferSize);
int	_mkdir (const char* szPath);
char*	_mktemp (char* szTemplate);
int	_rmdir (const char* szPath);


#ifndef _NO_OLDNAMES

int	chdir (const char* szPath);
char*	getcwd (char* caBuffer, int nBufferSize);
int	mkdir (const char* szPath);
char*	mktemp (char* szTemplate);
int	rmdir (const char* szPath);

#endif /* Not _NO_OLDNAMES */


#ifdef	__cplusplus
}
#endif

#endif	/* Not _DIR_H_ */

#endif	/* Not _STRICT_ANSI */
