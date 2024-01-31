/* umount.cc

   Copyright 1996 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdio.h>
#include <sys/mount.h>
#include <mntent.h>

int
main(int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s path\n", argv[0]);
      return 1;
    }

  if (umount (argv[1]) != 0)
    {
      perror ("umount");
      return 1;
    }
    
  return 0;
}
