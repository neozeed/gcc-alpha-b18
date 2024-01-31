/* pipe.cc: pipe for WIN32.

   Copyright 1996, 1998 Cygnus Solutions.

   Written by Doug Evans and Steve Chamberlain of Cygnus Support.
   dje@cygnus.com, sac@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"

int
pipe (int filedes[2])
{
  return fhandler_make_pipe (filedes);
}

int
dup (int fd)
{
  return dup2 (fd, myself->hmap.find_unused_handle (0));
}

int
dup2 (int oldfd, int newfd)
{
  return myself->hmap.dup2 (oldfd, newfd);
}
