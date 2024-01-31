/*
 * malloc.h
 *
 * Support for programs which want to use malloc.h to get memory management
 * functions. Unless you absolutely need some of these functions and they are
 * not in the ANSI headers you should use the ANSI standard header files
 * instead.
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

#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <alloc.h>

#ifdef	__cplusplus
extern "C" {
#endif

int	_heapchk ();	/* Verify heap integrety. */
int	_heapmin ();	/* Return unused heap to the OS. */
int	_heapset (unsigned int unFill);
size_t	_msize (void* pBlock);

#ifdef __cplusplus
}
#endif

#endif /* Not _MALLOC_H_ */

#endif /* Not _STRICT_ANSI */
