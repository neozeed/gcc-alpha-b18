/* mount.cc

   Copyright 1996, 1997 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdio.h>
#include <sys/mount.h>
#include <mntent.h>

static void show_mounts (void);
static void reset_mounts (void);

/* FIXME: A copy of this table also lives in path.cc. */
static struct {
  const char *dev;
  const char *path;
  int flags;
} default_mounts[] = {
  { "c:", "/", 0 },
  { "//./a:", "/dev/fd0", MOUNT_SILENT },
  { "//./b:", "/dev/fd1", MOUNT_SILENT },
  { "//./tape0:", "/dev/st0", MOUNT_SILENT },
  { "//./tape1:", "/dev/st1", MOUNT_SILENT },
  { 0 }
};

static void
do_mount (const char *dev, const char *where, int flags)
{
  if (mount (dev, where, flags))
    {
      perror ("mount failed");
      exit (1);
    }
  exit(0);
}

static const char *progname;

static void
usage (void)
{
  fprintf (stderr, "Usage %s [-b] <dospath> <unixpath>\n", progname);
  fprintf (stderr, "-b = text files are equivalent to binary files (newline = \\n)\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "To reset the mount table use: mount --reset\n");
  exit(1);
}

int
main (int argc, const char **argv)
{
  int i;
  int flags = 0;

  progname = argv[0];

  if (argc == 1)
    {
      show_mounts ();
      exit (0);
    }

  for (i = 1; i < argc; ++i)
    {
      if (argv[i][0] != '-')
	break;

      if (strcmp (argv[i], "--reset") == 0)
	{
	  reset_mounts ();
	  exit (0);
	}

      if (strcmp (argv[i], "-b") == 0)
	flags |= MOUNT_BINARY;
      else
	usage ();
    }

  if (i + 2 != argc)
    usage ();

  do_mount (argv[i], argv[i + 1], flags);
  /* NOTREACHED */
  return 0;
}

static void
show_mounts (void)
{
  FILE *m = setmntent ("/-not-used-", "r");
  struct mntent *p;
  char *format = "%-16s %-16s    %-10s  %s\n";

  printf (format, "Device", "Directory", "Type", "Flags");
  while ((p = getmntent (m)) != NULL)
    {
      printf (format,
	      p->mnt_fsname,
	      p->mnt_dir,
	      p->mnt_type,
	      p->mnt_opts);
    }
  endmntent (m);
}

static void
reset_mounts (void)
{
  int i;
  FILE *m = setmntent ("/-not-used-", "r");
  struct mntent *p;

  while ((p = getmntent (m)) != NULL)
    umount (p->mnt_dir);
  endmntent (m);

  for (i = 0; default_mounts[i].dev; ++i)
    mount (default_mounts[i].dev, default_mounts[i].path,
	   default_mounts[i].flags);
}
