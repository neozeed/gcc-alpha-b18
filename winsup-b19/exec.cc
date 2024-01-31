/* exec.cc: exec system call support.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "process.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

/* This is called _execve and not execve because the real execve is defined
   in libc/posix/execve.c.  It calls us.  */

extern "C"
pid_t
_execve (const char *path, const char *const argv[], const char *const envp[])
{
  return sexecve (NULL, path, argv, envp);
}

extern "C"
int
execl (const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;
  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);
  va_end (args);

  return _execve (path, (char * const  *) argv, *u->envptr);
}

extern "C"
int
execv (const char *path, char * const *argv)
{
  return _execve (path, (char * const *) argv, *u->envptr);
}

/* the same as a standard exec() calls family, but with NT security support */

extern "C"
pid_t
sexecve (HANDLE hToken, const char *path, const char *const argv[], const char *const envp[])
{
  if (path == 0)
    {
      syscall_printf ("path 0\n");
      set_errno(EINVAL);
      return (-1);
    }

  if (argv[0] == 0)
    {
      syscall_printf ("argv[0] is 0\n");
      char **tmp = (char **) &argv[0];
      *tmp = (char *) path;
    }

  if (envp == 0)
    {
      syscall_printf ("envp is 0\n");
      set_errno(EINVAL);
      return (-1);
    }

  syscall_printf ("_execve (%s, %s, %x)\n", path, argv[0], envp);

  /* We do not pass _P_SEARCH_PATH here.  execve doesn't search PATH.  */
  spawn_guts (hToken, path, argv, envp, myself->pid, _P_OVERLAY);

  /* Errno should be set by spawn_guts.  */
  return -1;
}

extern "C"
int
sexecl (HANDLE hToken, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  va_end (args);

  return sexecve (hToken, path, (char * const  *) argv, *u->envptr);
}

extern "C"
int
sexecle (HANDLE hToken, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char * const *envp;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
    argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  envp = va_arg (args, const char * const *);
  va_end (args);

  return sexecve(hToken, path, (char * const *) argv, (char * const *) envp);
}

extern "C"
int
sexeclp (HANDLE hToken, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  va_end (args);

  return sexecvpe (hToken, path, (const char * const *) argv, *u->envptr);
}

extern "C"
int
sexeclpe (HANDLE hToken, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char * const *envp;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
    argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  envp = va_arg (args, const char * const *);
  va_end (args);

  return sexecvpe (hToken, path, argv, envp);
}

extern "C"
int
sexecv (HANDLE hToken, const char *path, const char * const *argv)
{
  return sexecve (hToken, path, argv, *u->envptr);
}

extern "C"
int
sexecp (HANDLE hToken, const char *path, const char * const *argv)
{
  return sexecvpe (hToken, path, argv, *u->envptr);
}

static NO_COPY char path_delim;
#define PATH_DELIM path_delim

/*
 * Copy string, until c or <nul> is encountered.
 * NUL-terminate the destination string (s1).
 */

static char *
strccpy (char *s1, char *s2, char c)
{
  char *dest = s1;

  while (*s2 && *s2 != c)
    *s1++ = *s2++;
  *s1 = 0;

  return dest;
}

extern "C"
int
sexecvpe (HANDLE hToken, const char *file, const char * const *argv, const char *const *envp)
{
  char *path = getenv ("PATH");
  char buf[MAXNAMLEN];
  int ret;

  /* If $PATH doesn't exist, just pass FILE on unchanged.  */
  if (!path)
    return sexecve (hToken, file, argv, envp);

  /* If FILE contains a directory, don't search $PATH.  */
  if (strchr (file, '/') || strchr (file, '\\'))
    return sexecve (hToken, file, argv, envp);

  /* If a drive letter is passed, the path is still an absolute one.
     Technically this isn't true, but cygwin32 is currently defined so
     that it is.  */
  if ((isalpha (file[0]) && file[1] == ':') || file[0] == '\\')
    return sexecve (hToken, file, argv, envp);

  path_delim = posix_path_list_p (path) ? ':' : ';';

  while (*path)
    {
      strccpy (buf, path, PATH_DELIM);
      /* An empty entry means the current directory.  */
      if (*buf != 0)
	strcat (buf, "/");
      strcat (buf, file);
      ret = sexecve (hToken, buf, argv, envp);
      if (ret == -1 && get_errno() != ENOENT)
	return -1;
      if(ret != -1)
	return ret;
      while (*path && *path != PATH_DELIM)
	path++;
      if (*path == PATH_DELIM)
	path++;			/* skip over delim */
    }

  return -1;
}


