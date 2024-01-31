/* dirsearch.cc: Posix directory reading routines

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include "winsup.h"

#define _COMPILING_NEWLIB
#include "dirent.h"

extern "C"
DIR *
opendir (const char *dirname)
{
  int len;
  DIR *dir;
  DIR *res = 0;
  struct stat statbuf;

  path_conv real_dirname (dirname);

  if (real_dirname.error)
    {
      set_errno (real_dirname.error);
      goto failed;
    }

  if (stat (dirname, &statbuf) == -1)
    goto failed;

  if (!(statbuf.st_mode & S_IFDIR))
    {
      set_errno (ENOTDIR);
      goto failed;
    }

  len = strlen (real_dirname.get_win32 ());
  if (len > MAX_PATH - 3)
    {
      set_errno (ENAMETOOLONG);
      goto failed;
    }

  if ((dir = (DIR *) malloc (sizeof (DIR))) == NULL)
    {
      set_errno (ENOMEM);
      goto failed;
    }
  if ((dir->__d_dirname = (char *) malloc (len + 3)) == NULL)
    {
      free (dir);
      set_errno (ENOMEM);
      goto failed;
    }
  if ((dir->__d_dirent = (struct dirent *) malloc (sizeof (struct dirent))) == NULL)
    {
      free (dir->__d_dirname);
      free (dir);
      set_errno (ENOMEM);
      goto failed;
    }
  strcpy (dir->__d_dirname, real_dirname.get_win32 ());
  /* FindFirstFile doesn't seem to like duplicate /'s. */
  len = strlen (dir->__d_dirname);
  if (len == 0 || SLASH_P (dir->__d_dirname[len - 1]))
    strcat (dir->__d_dirname, "*");
  else
    strcat (dir->__d_dirname, "/*");  /**/
  dir->__d_cookie = __DIRENT_COOKIE;
  dir->__d_find_first_called = 0;
  dir->__d_u.__d_data.__open_p = 0;
  dir->__d_dirhash = hash_path_name (0, real_dirname.get_win32 ());

  res = dir;

failed:
  syscall_printf ("%p = opendir (%s)\n", res, dirname);
  return res;
}

extern "C"
struct dirent *
readdir (DIR * dir)
{
  WIN32_FIND_DATA buf;
  HANDLE handle;
  struct dirent *res = 0;
  int reason;
  int prior_errno;

  if (dir->__d_cookie != __DIRENT_COOKIE)
    {
      set_errno (EBADF);
      syscall_printf ("%p = readdir (%p)\n", res, dir);
      return res;
    }

  if (dir->__d_find_first_called)
    {
      if (FindNextFileA (dir->__d_u.__d_data.__handle, &buf) == 0)
	{
	  prior_errno = get_errno();
	  __seterrno ();
	  /* posix says you shouldn't set errno when readdir can't
	     find any more files; if another error we leave it set. */
	  if (get_errno() == ENMFILE)
	      set_errno(prior_errno);
	  syscall_printf ("%p = readdir (%p)\n", res, dir);
	  return res;
	}
    }
  else
    {
      handle = FindFirstFileA (dir->__d_dirname, &buf);

      if (handle == INVALID_HANDLE_VALUE) 	  /* return is INVALID_HANDLE_VALUE */
	{
	  /* It's possible that someone else deleted or emptied the directory
	     or some such between the opendir () call and here.  */
	  prior_errno = get_errno();
	  __seterrno ();
	  /* posix says you shouldn't set errno when readdir can't
	     find any more files; if another error we leave it set. */
	  if (get_errno() == ENMFILE)
	      set_errno(prior_errno);
	  syscall_printf ("%p = readdir (%p)\n", res, dir);
	  return res;
	}
      dir->__d_find_first_called = 1;
      dir->__d_u.__d_data.__handle = handle;
      dir->__d_u.__d_data.__open_p = 1;
    }

  /* We get here if `buf' contains valid data.  */
  strcpy (dir->__d_dirent->d_name, buf.cFileName);

  /* Compute d_ino by combining filename hash with the directory hash
     (which was stored in dir->__d_dirhash when opendir was called). */
  dir->__d_dirent->d_ino = hash_path_name (dir->__d_dirhash, buf.cFileName);

  res = dir->__d_dirent;
  syscall_printf ("%p = readdir (%p) (%s)\n",
		  &dir->__d_dirent, dir, buf.cFileName);
  return res;
}

extern "C"
void
rewinddir (DIR * dir)
{
  syscall_printf ("rewinddir (%p)\n", dir);

  if (dir->__d_cookie != __DIRENT_COOKIE)
    return;

  dir->__d_find_first_called = 0;
}

extern "C"
int
closedir (DIR * dir)
{
  if (dir->__d_cookie != __DIRENT_COOKIE)
    {
      set_errno (EBADF);
      syscall_printf ("-1 = closedir (%p)\n", dir);
      return -1;
    }

  if (dir->__d_find_first_called && FindClose (dir->__d_u.__d_data.__handle) == 0)
    {
      __seterrno ();
      syscall_printf ("-1 = closedir (%p)\n", dir);
      return -1;
    }

  /* Reset the marker in case the caller tries to use `dir' again.  */
  dir->__d_cookie = 0;

  free (dir->__d_dirname);
  free (dir->__d_dirent);
  free (dir);
  syscall_printf ("0 = closedir (%p)\n", dir);
  return 0;
}


