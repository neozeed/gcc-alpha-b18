/* pinfo.cc: process table support

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include <time.h>
#include "winsup.h"

pinfo NO_COPY *myself = NULL;

/* Initialize the process table.
   This is done once when the dll is first loaded.  */

void
pinfo_list::init (void)
{
  next_pid_index = 0;	// Which element in the pinfo list to begin using

  /* We assume the shared data area is already initialized to zeros.
     Note that SIG_DFL is zero.  */
}

/* Initialize the process table entry for the current task.
   This is not called for fork'd tasks, only exec'd ones.  */

/* FIXME: Process table lookups may need to be sped up some day.  */

void
pinfo_init (void)
{
  DWORD thisProcessId = GetCurrentProcessId ();

  /*
   * We need to lock the process table here to be safe from
   * manipulation by a fork in another process.
   */

  myself = NULL;

  /* Lookup dwSpawnedProcessId in table.  */
  for (int i = 0; i < s->p.size (); i++)
    if (s->p.vec[i].dwSpawnedProcessId == thisProcessId &&
	s->p.vec[i].process_state != PID_NOT_IN_USE)
      {
	myself = s->p.vec + i;
	myself->dwSpawnedProcessId = 0;
	break;
      }

  if (myself)
    {
      /* The process was execed.  Reuse entry from the original
	 owner of this pid.
       */
      environ_init ();		/* Needs u->self but affects calls below */

      /* spawn has already set up a pid structure for us so we'll use that */
      
      (void) lock_pinfo_for_update (INFINITE);
      myself->process_state |= PID_CYGPARENT;
      myself->start_time = time (NULL); /* Register our starting time. */

      /*
       * The value in myself->hmap.vec will be garbage as it
       * will point into our parent's address space. Allocate space
       * for getdtablesize() file descriptors and copy from
       * STARTUPINFO structure.
       */
      STARTUPINFO si;

      GetStartupInfo (&si);
      if (si.cbReserved2 == 0 || si.lpReserved2 == NULL)
	api_fatal ("Can't inherit fd table\n");
      else
	{
	  LPBYTE b =
	    myself->hmap.de_linearize_fd_array (si.lpReserved2 + sizeof(int));
	  if (b && *b)
	    old_title = (char *)b;
	}

      unlock_pinfo ();
      debug_printf ("new self->hmap.vec = %x\n", myself->hmap.vec);
    }
  else
    {
      /* Invent our own pid.  */

      (void) lock_pinfo_for_update (INFINITE);
      if (!(myself = s->p.allocate_pid ()))
	api_fatal ("No more processes");

      myself->start_time = time (NULL); /* Register our starting time. */

      myself->ppid = myself->pid;
      myself->sid  = myself->pid;
      myself->pgid = 0;
      myself->ctty = -1;
      myself->uid = USHRT_MAX;
      unlock_pinfo ();

      environ_init ();		/* call after myself has been set up */
    }

  debug_printf ("pid == %d, pgid == %d\n", myself->pid, myself->pgid);
}

/* [] operator.  This is the mechanism for table lookups.  */

pinfo *
pinfo_list::operator [] (pid_t arg)
{
  pinfo *p;
  return ((arg -= PBASE) < 0 || arg >= size() ||
	  (p = vec + arg)->process_state == PID_NOT_IN_USE) ? NULL : p;
}

pinfo *
procinfo (int pid)
{
  return s->p[pid];
}

#ifdef DEBUGGING
/*
 * Code to lock/unlock the process table.
 */

int
lpfu (char *func, int ln, DWORD timeout)
{
  int rc;
  DWORD t;

  debug_printf ("timeout %d, pinfo_mutex = %p\n", timeout, pinfo_mutex);
  t = (timeout == INFINITE) ? 60000 : timeout;
  SetLastError(0);
  while ((rc = WaitForSingleObject (pinfo_mutex, t)) != WAIT_OBJECT_0)
    {
      if (rc == WAIT_ABANDONED_0)
	break;
      system_printf ("lock_pinfo_for_update: %s:%d having problems getting lock\n", 
		     func, ln);
      system_printf ("lock_pinfo_for_update: *** %src = %d, err = %d\n",
		     s->p.lock_info, rc, GetLastError());
      if (t == timeout)
	break;
     }

  __small_sprintf (s->p.lock_info, "%s(%d), pid %d ", func, ln,
		   (u && myself) ? myself->pid : -1);
  return rc;
}

void
unlock_pinfo (void)
{

  debug_printf ("handle %d\n", pinfo_mutex);

  if (!s->p.lock_info[0])
    system_printf ("unlock_pinfo: lock_info not set?\n");
  else
    strcat (s->p.lock_info, " unlocked ");
  ReleaseMutex (pinfo_mutex);
}
#else
/*
 * Code to lock/unlock the process table.
 */

int
lock_pinfo_for_update (DWORD timeout)
{
  int rc;
  DWORD t;

  debug_printf ("timeout %d, pinfo_mutex = %p\n", timeout, pinfo_mutex);
  t = (timeout == INFINITE) ? 60000 : timeout;
  SetLastError(0);
  while ((rc = WaitForSingleObject (pinfo_mutex, t)) != WAIT_OBJECT_0)
    {
      if (rc == WAIT_ABANDONED_0)
	break;
      system_printf ("lock_pinfo_for_update: rc = %d, err = %d\n", rc,
		     GetLastError());
      if (t == timeout)
	break;
     }

  return rc;
}

void
unlock_pinfo (void)
{

  debug_printf ("handle %d\n", pinfo_mutex);

  ReleaseMutex (pinfo_mutex);
}
#endif

/* Allocate a process table entry.  */

pinfo *
pinfo_list::allocate_pid (void)
{
  pinfo *p;

  /* Find an empty slot in the process table.
     We could use a linked list, and maybe eventually we will.  The process
     table is in the shared data space and thus is susceptible to corruption.
     The amount of time spent scanning the table is presumably quite small
     compared with the total time to create a process.

     Start looking at the next available slot in the pinfo list and scan
     forward sequentially until an empty slot is found.  If the end of the
     table is hit, wrap.

     If all else fails, sweep through the loop looking for processes that
     may have died abnormally without registering themselves as "dead".
     Clear out these pinfo structures.  Then scan the table again.
  */

  for (int tries = 0; ; tries++)
    {
      for (pinfo *b = vec + next_pid_index, *e = vec + size (); b != e;
	   e = b, b = vec)
	for (p = b; p < e; p++)
	  if (p->process_state == PID_NOT_IN_USE)
	    {
	      debug_printf ("found empty slot %d\n", p - vec);
	      goto gotit;
	    }

      if (tries > 0)
	break;

      debug_printf ("clearing out deadwood\n");

      for (p = vec; p < vec + size(); p++)
	proc_exists (p);
    }

  /* The process table is full.  */
  debug_printf ("process table is full\n");

  return NULL;

gotit:
  memset (p, 0, PINFO_ZERO);
  next_pid_index = p - vec;

  /* Set new pid based on the position of this element in the pinfo list */
  p->pid = PBASE + next_pid_index;

  /* Determine next slot to consider */
  if (++next_pid_index >= size())
    next_pid_index = 0;

  /* Allocate the file descriptor table in hmap. We do this so that
   * the number of fd's per process can be changed.
   */
  if (!(p->hmap.vec = new hinfo [getdtablesize ()]))
    api_fatal ("pinfo_list::allocate_pid() - out of memory\n");

  p->hmap.clearout ();
  p->process_state = PID_IN_USE;
  debug_printf ("pid %d, state %x\n", p->pid, p->process_state);
  return p;
}

void
pinfo::record_death_nolock (void)
{
  if (myself->dwProcessId == GetCurrentProcessId () && !alive_parent (myself))
    {
      process_state = PID_NOT_IN_USE;
      hProcess = NULL;
    }
}

void
pinfo::record_death (void)
{
  (void) lock_pinfo_for_update (INFINITE);

  record_death_nolock ();

//unlock_pinfo ();	// Lock until ExitProcess or suffer a race
}

void
pinfo::init_from_exec (void)
{
  /* Close all the close_on exec things and duplicate the rest into
     the child's space  */

  /* memset (&reent_data, 0, sizeof (reent_data));*/
  debug_printf ("in init_from_exec\n");

  hmap.dup_for_exec ();
}

/* This function is exported from the DLL.  Programs can call it to
   convert a Windows process ID into a cygwin process ID.  */

extern "C" pid_t
cygwin32_winpid_to_pid (int winpid)
{
  for (int i = 0; i < s->p.size (); i++)
    {
      pinfo *p = &s->p.vec[i];

      if (p->process_state == PID_NOT_IN_USE)
        continue;

      if (p->dwProcessId == winpid)
	return p->pid;
    }

  set_errno (ESRCH);
  return (pid_t) -1;
}
