/* ioctl.cc: ioctl routines. 

   Copyright 1996, 1998 Cygnus Solutions.

   Written by Doug Evans of Cygnus Support
   dje@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "sys/termios.h"

int
ioctl (int fd, int cmd, void *buf)
{
  if (NOT_OPEN_FD(fd))
    {
      set_errno (EBADF);
      return -1;
    }

  return myself->hmap[fd].h->ioctl (cmd, buf);
}
