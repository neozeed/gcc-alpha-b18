/* shared.cc: shared data area support.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <unistd.h>
#include <stdio.h>
#include "winsup.h"
#include "registry.h"

shared_info NO_COPY *s;

/* The handle of the shared data area.  */
static HANDLE NO_COPY h;

/* Open the shared memory map.  */

static void
open_shared_file_map ()
{
  char *mapname = cygname ("shared", 0);

  h = OpenFileMappingA (FILE_MAP_READ|FILE_MAP_WRITE, FALSE, mapname);

  if (!h)
    {
      SECURITY_ATTRIBUTES sa;
      sa.nLength = sizeof (SECURITY_ATTRIBUTES);
      sa.bInheritHandle = 0;
      sa.lpSecurityDescriptor = get_null_sd ();

      h = CreateFileMappingA ((HANDLE) 0xffffffff,
			      &sa,
			      PAGE_READWRITE,
			      0,
			      sizeof (*s),
			      mapname);

    }

  if (!h)
    {
      system_printf ("open_shared_file_map: CreateFileMappingA\n");
      api_fatal ("terminating");
    }

  s = (shared_info *) MapViewOfFileEx (h, FILE_MAP_READ|FILE_MAP_WRITE,
				       0, 0, 0, (void *) 0xa000000);

  if (!s)
    { 
      /* Probably win95, so try without specifying the address.  */
      s = (shared_info *) MapViewOfFileEx (h, FILE_MAP_READ|FILE_MAP_WRITE,
					   0,0,0,0);
    }

  if (!s)
    {
      system_printf ("open_shared_file_map: MapViewOfFileEx\n");
      api_fatal ("terminating");
    }

  debug_printf ("s = %p, h = %d\n", s, h);

  /* FIXME: I couldn't find anywhere in the documentation a note about
     whether the memory is initialized to zero.  The code assumes it does
     and since this part seems to be working, we'll leave it as is.  */
}

void
shared_info::initialize ()
{
  /* Ya, Win32 provides a way for a dll to watch when it's first loaded.
     We may eventually want to use it but for now we have this.  */
  if (inited)
    return;

  /* Initialize the mount table.  */
  mount.init ();

  /* Initialize the process table.  */
  p.init ();

  /* Initialize the queue of deleted files.  */
  delqueue.init ();

  /* Initialize tty table.  */
  t.init ();

  /* Fetch misc. registry entries.  */

  reg_session reg;

  heap_chunk_in_mb = reg.get_key ().get_int ("heap_chunk_in_mb", 8);
  if (heap_chunk_in_mb < 4)
    {
      heap_chunk_in_mb = 4;
      reg.get_key ().set_int ("heap_chunk_in_mb", heap_chunk_in_mb);
    }

  inited = 1;
}

void
shared_init ()
{
  open_shared_file_map ();

  s->initialize ();
}

void
shared_terminate ()
{
  if (h)
    CloseHandle (h);
}

int
shared_info::heap_chunk_size ()
{
  return heap_chunk_in_mb << 20;
}

/* For apps that wish to access the shared data.  */

shared_info *
cygwin32_getshared ()
{
  return s;
}

/*
 * Function to return a common SECURITY_DESCRIPTOR * that
 * allows all access.
 */

static NO_COPY SECURITY_DESCRIPTOR *null_sdp = 0;

SECURITY_DESCRIPTOR *get_null_sd ()
{
  static NO_COPY SECURITY_DESCRIPTOR sd;
  if (null_sdp == 0)
    {
      InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
      SetSecurityDescriptorDacl (&sd, TRUE, 0, FALSE);
      null_sdp = &sd;
    }
  return null_sdp;
}
