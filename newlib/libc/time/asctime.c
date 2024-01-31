/*
 * asctime.c
 * Original Author:	G. Haley
 *
 * Converts the broken down time in the structure pointed to by tim_p into a
 * string of the form
 *
 * Wed Jun 15 11:38:07 1988\n\0
 *
 * Returns a pointer to the string.
 */

/*
FUNCTION
<<asctime>>---format time as string

INDEX
	asctime
INDEX
	_asctime_r

ANSI_SYNOPSIS
	#include <time.h>
	char *asctime(const struct tm *<[clock]>);
	char *asctime_r(const struct tm *<[clock]>, char *<[buf]>);

TRAD_SYNOPSIS
	#include <time.h>
	char *asctime(<[clock]>)
	struct tm *<[clock]>;
	char *asctime_r(<[clock]>)
	struct tm *<[clock]>;
	char *<[buf]>;

DESCRIPTION
Format the time value at <[clock]> into a string of the form
. Wed Jun 15 11:38:07 1988\n\0
The string is generated in a static buffer; each call to <<asctime>>
overwrites the string generated by previous calls.

RETURNS
A pointer to the string containing a formatted timestamp.

PORTABILITY
ANSI C requires <<asctime>>.

<<asctime>> requires no supporting OS subroutines.
*/

#include <time.h>

#ifndef _REENT_ONLY

char *
_DEFUN (asctime, (tim_p),
	_CONST struct tm *tim_p)
{
  static char buf[26];
  return asctime_r (tim_p, buf);
}

#endif
