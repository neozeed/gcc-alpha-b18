/*
 * oldnames.c
 *
 * Some wrapper functions for those old name functions whose appropriate
 * equivalents are not simply underscore prefixed.
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

#include <ctype.h>
#include <string.h>



/**************************************************************************
 * Oldnames from ANSI header ctype.h
 **************************************************************************/

int
isascii (int c)
{
	return __isascii(c);
}

int
toascii (int c)
{
	return __toascii(c);
}

int
iscsymf (int c)
{
	return __iscsymf(c);
}

int
iscsym (int c)
{
	return __iscsym(c);
}



/**************************************************************************
 * Oldnames from ANSI header string.h
 **************************************************************************/

int
strcasecmp (const char* sz1, const char* sz2)
{
	return _stricmp (sz1, sz2);
}

int
strncasecmp	(const char* sz1, const char* sz2, size_t sizeMaxCompare)
{
	return _strnicmp (sz1, sz2, sizeMaxCompare);
}

int
wcscmpi (const wchar_t* ws1, const wchar_t* ws2)
{
	return _wcsicmp (ws1, ws2);
}

