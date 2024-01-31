/* delqueue.cc

   Copyright 1996, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"

/* FIXME: this delqueue module is very flawed and should be rewritten.
	First, having an array of a fixed size for keeping track of the
	unlinked but not yet deleted files is bad.  Second, some programs
	will unlink files and then create a new one in the same location
	and this behavior is not supported in the current code.  Probably
	we should find a move/rename function that will work on open files,
	and move delqueue files to some special location or some such
	hack... */

void
delqueue_item::process ()
{
  if (inuse)
    {
      if (DeleteFileA (name))
	{
	  syscall_printf ("Deleted %s\n", name);
	  inuse = 0;
	}
      else
	{
	  int res = GetLastError ();
	  if (res == ERROR_SHARING_VIOLATION)
	    {
	      /* File still inuse, that's ok */
	      syscall_printf ("Still using %s\n", name);
	    }
	  else
	    {
	      syscall_printf ("Hmm, don't know what to do with  %s\n", name);
	    }
	}
    }
}

void
delqueue_list::init ()
{
  for (int i = 0; i < MAX_DELQUEUES_PENDING; i++)
    {
      dqueue[i].init ();
    }
}

void
delqueue_item::init ()
{
  inuse = 0;
}

int
delqueue_item::add (const char *dosname)
{
  char *end;
  if (inuse)
    return 0;

  GetFullPathName (dosname, sizeof (name), name, &end);
  inuse = 1;
  return 1;
}

void
delqueue_list::queue_file (const char *dosname)
{
  for (int i = 0; i < MAX_DELQUEUES_PENDING; i++)
    {
      if (dqueue[i].add (dosname))
	return;
    }

  small_printf ("Out of queue slots!!\n");
}

void
delqueue_list::process_queue ()
{
  syscall_printf ("Running delqueue\n");
  for (int i = 0; i < MAX_DELQUEUES_PENDING; i++)
    {
      dqueue[i].process ();
    }
}
