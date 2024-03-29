/* execle.c */

/* This and the other exec*.c files in this directory require 
   the target to provide the _execve syscall.  */

#include <_ansi.h>
#include <unistd.h>

#ifdef _HAVE_STDC

#include <stdarg.h>

int
execle (_CONST char *path, _CONST char *arg0, ...)

#else

#include <varargs.h>

int
execle (path, arg0, va_alist)
     _CONST char *path;
     _CONST char *arg0;
     va_dcl

#endif

{
  int i;
  va_list args;
  _CONST char * _CONST *envp;
  _CONST char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;
  do
    argv[i] = va_arg (args, _CONST char *);
  while (argv[i++] != NULL);
  envp = va_arg (args, _CONST char * _CONST *);
  va_end (args);

  return _execve (path, (char * _CONST *) argv, (char * _CONST *) envp);
}
