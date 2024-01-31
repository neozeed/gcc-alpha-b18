/*
 * types.h
 *
 * The definition of constants, data types and global variables.
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
 *  WITHOUT ANY WARRANTY. ALL WARRENTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAMED. This includes but is not limited to warrenties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef	_TYPES_H_
#define	_TYPES_H_

#ifndef	_TIME_T_
#define	_TIME_T_
typedef	long	time_t;
#endif


#ifndef	_STRICT_ANSI

/* Type for file offsets. This is related to lseek and such, so I would
 * prefer to put it in nonansi, but it is a system dependent type, so
 * suppose sys will do. */
#ifndef	_OFF_T_DEFINED
typedef long _off_t;

#ifndef	_NO_OLDNAMES
#define	off_t	_off_t
#endif

#define	_OFF_T_DEFINED

#endif	/* Not _OFF_T_DEFINED */

#endif	/* Not _STRICT_ANSI */


#endif	/* Not _TYPES_H_ */
