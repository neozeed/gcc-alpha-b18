/*
 * direct.h
 *
 * Functions for manipulating paths and directories (included from dir.h)
 * plus functions for setting the current drive.
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

#ifndef	_DIRECT_H_
#define	_DIRECT_H_

#include <dir.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * You really shouldn't be using these. Use the Win32 API functions instead.
 * However, it does make it easier to port older code.
 */
int	_chdrive (int nDrive);
char*	_getdcwd (int nDrive, char* caBuffer, int nBufLen);

#ifdef	__cplusplus
}
#endif

#endif	/* Not _DIRECT_H_ */

#endif	/* Not _STRICT_ANSI */
