/*
 * timeb.h
 *
 * Support for the UNIX System V ftime system call.
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

#ifndef	_STRICT_ANSI

#ifndef	_TIMEB_H_
#define	_TIMEB_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * TODO: Structure not tested.
 */
struct timeb
{
	long	time;
	short	millitm;
	short	_timezone;
	short	dstflag;
};

/* TODO: Not tested. */
void	_ftime (struct timeb* timebBuffer);

#ifndef	_NO_OLDNAMES
void	ftime (struct timeb* timebBuffer);
#endif	/* Not _NO_OLDNAMES */

#ifdef	__cplusplus
}
#endif

#endif	/* Not _TIMEB_H_ */

#endif	/* Not _STRICT_ANSI */
