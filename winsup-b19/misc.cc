/* misc.cc: misc. non-posix routines.  

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

/* This file contains various routines that various applications need
   that aren't found in Posix.  They're kept here instead of files
   that also contain Posix routines to avoid namespace pollution.  */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#include "winsup.h"

extern "C"
int
creat (const char *path, mode_t mode)
{
  return open (path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

extern "C"
void
__assertfail ()
{
  exit (99);
}

extern "C"
int
getw (FILE *fp)
{
  int w, ret;
  ret = fread(&w, sizeof(int), 1, fp);
  if(feof(fp) || ferror(fp))
    return EOF;
  return w;
}

extern "C"
int
putw (int w, FILE *fp)
{
  int ret;
  ret = fwrite(&w, sizeof(int), 1, fp);
  if(feof(fp) || ferror(fp))
    return -1;
  return 0;
}

extern "C"
int
wcscmp (wchar_t *s1, wchar_t *s2)
{
  while (*s1  && *s1 == *s2)
    {
      s1++;
      s2++;
    }

  return (*(unsigned short *) s1) - (*(unsigned short *) s2);
}

extern "C"
int
wcslen (wchar_t *s1)
{
  int l = 0;
  while (s1[l])
    l++;
  return l;
}

/* FIXME
   to do this right, maybe work out the usoft va_list machine
   and use wsvprintfW instead
*/
extern "C"
int
wprintf (const char *fmt, ...)
{
  va_list ap;
  int ret;

  va_start (ap, fmt);
  ret = vprintf (fmt, ap);
  va_end (ap);
  return ret;
}

extern "C"
int
vhangup ()
{
  set_errno (ENOSYS);
  return -1;
}

extern "C"
_PTR
memccpy (_PTR out, const _PTR in , int c, size_t len)
{
  const char *inc = (char *) in;
  char *outc = (char *) out;

  while (len)
    {
      char x = *inc++;
      *outc++ = x;
      if (x == c)
	return outc;
      len --;
    }
  return 0;
}

extern "C"
int
nice (int incr) 
{
  DWORD pri[] =
    {
      IDLE_PRIORITY_CLASS,
      IDLE_PRIORITY_CLASS,
      NORMAL_PRIORITY_CLASS,
      HIGH_PRIORITY_CLASS,
      REALTIME_PRIORITY_CLASS,
      REALTIME_PRIORITY_CLASS
    };
  int index = 2;

  switch (GetPriorityClass (GetCurrentProcess ()))
    {
      case IDLE_PRIORITY_CLASS:
        index = 1;
        break;
      case NORMAL_PRIORITY_CLASS:
        index = 2;
        break;
      case HIGH_PRIORITY_CLASS:
        index = 3;
        break;
      case REALTIME_PRIORITY_CLASS:
        index = 4;
        break;
    }
  if (incr > 0)
    incr = -1;
  else if (incr < 0)
    incr = 1;

  if (SetPriorityClass (GetCurrentProcess(), pri[index+incr]) == FALSE)
    {
      __seterrno();
      return -1;
    }

  return 0;
}

/*
 * Find the first bit set in I. 
 */

extern "C"
int
ffs (int i)
{
  static const unsigned char table[] =
    {
      0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
    };
  unsigned long int a;
  unsigned long int x = i & -i;

  a = x <= 0xffff ? (x <= 0xff ? 0 : 8) : (x <= 0xffffff ?  16 : 24);

  return table[x >> a] + a;
}

/*
 * swab... enuf said.
 */

extern "C"
void
swab (const void *src, void *dst, ssize_t n)
{
  const char *from = (const char *)src;
  char *to = (char *)dst;

  while (n > 1)
    {
      const char b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}



extern
char *
cygname (char *s, int num)
{
  static NO_COPY char buf[MAX_PATH];
  extern char cygwin_dll_id[];

  sprintf (buf, "%s.%s.%d", cygwin_dll_id, s, num);
  return buf;
}

extern "C"
void
login (struct utmp *ut)
{
  register int fd;
  int tty;

  tty = ttyslot();
  if (tty >= 0 && (fd = open(_PATH_UTMP, O_WRONLY|O_CREAT|O_BINARY, 0644)) >= 0)
    {
      (void)lseek(fd, (long)(tty * sizeof(struct utmp)), SEEK_SET);
      (void)write(fd, (char *)ut, sizeof(struct utmp));
      (void)close(fd);
    }
  if ((fd = open(_PATH_WTMP, O_WRONLY|O_APPEND|O_BINARY, 0)) >= 0)
    {
      (void)write(fd, (char *)ut, sizeof(struct utmp));
      (void)close(fd);
    }
}

/* It isn't possible to use unix-style I/O function in logout code because
cygwin's I/O subsystem may be inaccesable at logout() call time.
*/
extern "C"
int
logout (char *line)
{
  int success = 0;
  HANDLE ut_fd;

  path_conv win32_path (_PATH_UTMP);
  if (win32_path.error)
    {
      return 0;
    }

  ut_fd = CreateFile (win32_path.get_win32 (),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
  if (ut_fd != INVALID_HANDLE_VALUE)
    {
      struct utmp *ut;
      struct utmp ut_buf[100];
      off_t pos = 0;		/* Position in file */
      unsigned int rd;

      while (!success && ReadFile (ut_fd, ut_buf, sizeof ut_buf, &rd, NULL) &&
			rd != 0)
	{
	  struct utmp *ut_end = (struct utmp *)((char *)ut_buf + rd);

	  for (ut = ut_buf; ut < ut_end; ut++, pos += sizeof *ut)
	    if (ut->ut_name[0]
		&& strncmp (ut->ut_line, line, sizeof ut->ut_line) == 0)
	      /* Found the entry for LINE; mark it as logged out.  */
	      {
		/* Zero out entries describing who's logged in.  */
		bzero (ut->ut_name, sizeof ut->ut_name);
		bzero (ut->ut_host, sizeof ut->ut_host);
		time (&ut->ut_time);
		
		/* Now seek back to the position in utmp at which UT occured,
		   and write the new version of UT there.  */
		if (SetFilePointer (ut_fd, pos, 0, FILE_BEGIN) != -1
		    && WriteFile (ut_fd, (char *)ut, sizeof (*ut), &rd, NULL))
		  {
		    success = 1;
		    break;
		  }
	      }
	}

      CloseHandle (ut_fd);
    }

  return success;
}
