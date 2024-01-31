/* smallprint.c: small print routines for WIN32

   Copyright 1996, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include "syscalls.h"

static char *
rn (char *dst, int base, int dosign, int val, int len, int pad)
{
  /* longest number is 4294967295, 10 digits */
  unsigned uval;
  char res[10];
  static const char str[16] = "0123456789ABCDEF";
  int l = 0;

  if (dosign && val < 0)
    {
      *dst++ = '-';
      uval = -val;
    }
  else
    {
      uval = val;
    }
  do
    {
      res[l++] = str[uval % base];
      uval /= base;
    }
  while (uval);

  while (len -- > l)
    *dst++ = pad;

  while (l > 0)
    {
      *dst++ = res[--l];
    }

  return dst;
}

int
__small_vsprintf (char *dst, const char *fmt, va_list ap)
{
  char *orig = dst;
  char *s;

  while (*fmt)
    {
      if (*fmt != '%')
	*dst++ = *fmt++;
      else
	{
	  int len = 0;
	  char pad = ' ';

	  fmt++;

	  if (*fmt == '0') 
	    {
	      pad = '0';
	      fmt++;
	    }
	  
	  if (*fmt >= '1' && *fmt <= '9')
	    len = *fmt++ - '0';

	  switch (*fmt++)
	    {
	    case 'c':
	      {
		int c = va_arg (ap,int);
		if (c > ' ' && c <= 127)
		  *dst++ = c;
		else
		  {
		    *dst++ = '0';
		    *dst++ = 'x';
		    dst = rn (dst, 16, 0, c, len, pad);
		  }
	      }
	      break;
	    case 'd':
	      dst = rn (dst, 10, 1, va_arg (ap, int), len, pad);
	      break;
	    case 'u':
	      dst = rn (dst, 10, 0, va_arg (ap, int), len, pad);
	      break;
	    case 'p':
	      *dst++ = '0';
	      *dst++ = 'x';
	      /* fall through */
	    case 'x':
	      dst = rn (dst, 16, 0, va_arg (ap, int), len, pad);
	      break;
	    case 's':
	      s = va_arg (ap, char *);
	      while (*s)
		*dst++ = *s++;
	      break;
	    case 'F':
	    {
	      char *p, *pe;
	      s = va_arg (ap, char *);
              for (p = s; pe = strchr (p, '('); p = pe + 1)
                if (isalnum (pe[-1]) || pe[-1] == '_')
                  break;
              if (!pe)
		pe = strchr (s, '\0');
	      for (p = pe; p > s; p--)
		if (*p == ' ')
		  {
		    p++;
		    break;
		  }
	      while (p < pe)
		*dst++ = *p++;
	      break;
	    }
	    default:
	      *dst++ = '?';
	      *dst++ = fmt[-1];
	    }
	}
    }
  *dst = 0;
  return dst - orig;
}

int
__small_sprintf (char *dst, const char *fmt,...)
{
  int r;
  va_list ap;
  va_start (ap, fmt);
  r = __small_vsprintf (dst, fmt, ap);
  va_end (ap);
  return r;
}
