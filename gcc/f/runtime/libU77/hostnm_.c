/* Copyright (C) 1995 Free Software Foundation, Inc.
This file is part of GNU Fortran libU77 library.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Library General Public License as published
by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Fortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with GNU Fortran; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#if HAVE_STRING_H
#  include <string.h>
#else
#  include <strings.h>
#endif
#if HAVE_UNISTD_H
#  include <unistd.h>
#endif
#include <errno.h>		/* for ENOSYS */
#include "f2c.h"

integer G77_hostnm_0 (char *name, ftnlen Lname)
{
    int ret, i;

#if HAVE_GETHOSTNAME
    ret = gethostname (name, Lname);
    if (ret==0) {
	/* Pad with blanks (assuming gethostname will make an error
           return if it can't fit in the null). */
	for (i=strlen(name); i<=Lname; i++)
	    name[i] = ' ';
    }
    return ret;
#else
    return errno = ENOSYS;
#endif
}
