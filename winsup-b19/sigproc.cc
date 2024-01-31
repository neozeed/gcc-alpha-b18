/* sigproc.cc: inter/intra signal and sub process handler

   Copyright 1997, 1998 Cygnus Solutions.

   Written by Christopher Faylor <cgf@bbc.com>

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/wait.h>
#include <sys/errno.h>
#include <stdlib.h>
#include "winsup.h"

/*
 * Convenience defines
 */
#define WBSD		   20000 // Wait for signal dispatch mutex
#define WSSC		   60000 // Wait for signal completion
#define WPSP		   40000 // Wait for proc_subproc mutex
#define WSPX		   20000 // Wait for wait_sig to terminate
#define WWSP		   20000 // Wait for wait_subproc to terminate

#define WAIT_SIG_PRIORITY		THREAD_PRIORITY_HIGHEST

#define TOTSIGS	(NSIG + __SIGOFFSET)

#ifdef DEBUGGING
/* Display serious errors on the console and in a strace file, if appropriate.
 */
#define alert_printf(fmt, args...) \
  ({ \
    system_printf ("%s: [%s] " fmt , __FUNCTION__ , threadname () , ## args); \
    sigproc_printf ("[%s] " fmt , threadname () , ## args); \
  })

#define sip_printf(fmt, args...) \
    sigproc_printf ("[%s] " fmt , threadname () , ## args)
#else
/* Display serious errors on the console and in a strace file, if appropriate.
 */
#define alert_printf(fmt, args...) \
  ({ \
    system_printf ("%s: " fmt , __FUNCTION__ , ## args); \
    sigproc_printf (fmt , ## args); \
  })

#define sip_printf(fmt, args...) sigproc_printf (fmt , ## args)
#endif

/* How to determine if a process is accepting messages.
 */
#define proc_alive(p) \
  (((p)->process_state & (PID_ACTIVE | PID_IN_USE)) ==\
   (PID_ACTIVE | PID_IN_USE))

#define wake_wait_subproc SetEvent (events[0])

/*
 * Global variables
 */

/*
 * Common variables
 */


/* How long to wait for message/signals.  Normally this is infinite.
 * On termination, however, these are set to zero as a flag to exit.
 */

#define Static static NO_COPY
Static DWORD proc_loop_wait = INFINITE;	// Wait for subprocesses to exit
Static DWORD sig_loop_wait = INFINITE;	// Wait for signals to arrive

Static HANDLE sigcatch_nonmain = NULL;	// The semaphore signaled when
					//  signals are available for
					//  processing from non-main thread
Static HANDLE sigcatch_main = NULL;	// Signalled when main thread sends a
					//  signal
Static HANDLE sigcatch_nosync = NULL;	// Signal wait_sig to scan sigtodo
					//  but not to bother with any
					//  synchronization
Static HANDLE sigcomplete_main = NULL;	// Event signaled when a signal has
					//  finished processing for the main
					//  thread
Static HANDLE sigcomplete_nonmain = NULL;// Semaphore raised for non-main
					//  threads when a signal has finished
					//  processing
Static HANDLE sig_was_dispatched = NULL;// Event signaled when a signal has
					//  resulted in a user-specified
					//  function call
Static HANDLE hwait_sig = NULL;		// Handle of wait_sig thread
Static HANDLE hwait_subproc = NULL;	// Handoe of sig_subproc thread

Static DWORD maintid = 0;		// Main thread id
Static DWORD sigtid = 0;		// Signal thread id
Static DWORD proctid = 0;		// Process thread id

Static HANDLE wait_sig_inited = NULL;	// Control synchronization of
				   	//  message queue startup
Static HANDLE sync_proc_subproc = NULL;	// Control access to
					//  subproc stuff

/* Used by WaitForMultipleObjects.  These are handles to child processes.
 */
Static HANDLE events[PSIZE + 1];	// All my children's handles++
#define hchildren (events + 1)		// Where the children handles begin
Static pinfo *pchildren[PSIZE]; 	// All my children info
Static pinfo *zombies[PSIZE];		// All my deceased children info
Static int nchildren = 0;		// Number of active children
Static int nzombies = 0;		// Number of deceased children

Static waitq waitq_head = {0};		// Start of queue for wait'ing threads
Static waitq waitq_main;		// Storage for main thread
Static SECURITY_ATTRIBUTES sa;		// Standard "all" security

/* Functions
 */
static int checkstate (waitq *);
static BOOL __inline get_proc_lock (DWORD, DWORD);
static HANDLE getsem (pinfo *, char *, int, int);
static void proc_strace (void);
static void remove_child (int);
static void remove_zombie (int);
static DWORD wait_sig (VOID *arg);
static int stopped_or_terminated (waitq *, pinfo *);
#ifdef DEBUGGING
static char *threadname (void);
#endif
static DWORD wait_subproc (VOID *);
static void zap_subproc (pinfo *);

/* Determine if the parent process is alive.
 */

BOOL
alive_parent (pinfo *p)
{
  DWORD res;
  if (!(p)->parent_alive)
    {
      debug_printf ("No parent_alive mutex\n");
      res = FALSE;
    }
  else
    for (int i = 0; i < 2; i++)
      switch (res = WaitForSingleObject ((p)->parent_alive, 0))
	{
	  case WAIT_OBJECT_0:
	    debug_printf ("parent dead.\n");
	    res = FALSE;
	    break;
	  case WAIT_TIMEOUT:
	    debug_printf ("parent still alive\n");
	    res = TRUE;
	    break;
	  case WAIT_FAILED:
	    DWORD werr = GetLastError ();
	    if (werr == ERROR_INVALID_HANDLE && i == 0)
	      continue;
	    system_printf ("WFSO for parent_alive(%p) failed, error = %d\n",
			   (p)->parent_alive, werr);
	    res = FALSE;
	    break;
	}
  return res;
}

/* Test to determine if a process really exists and is processing
 * signals.
 */
BOOL
proc_exists (pinfo *p)
{
  HANDLE h;

  if (p == NULL)
    return FALSE;

  if (p == myself)
    return TRUE;

  if (p->process_state == PID_NOT_IN_USE || !p->dwProcessId)
    return FALSE;

  sip_printf ("checking for existence of pid %d, window pid %d\n", p->pid,
	      p->dwProcessId);
  if (p->parent_alive && p->ppid == myself->pid && p->hProcess != NULL)
    {
      sip_printf ("it's mine, process_state %x\n", p->process_state);
      return ISSTATE(p, PID_INITIALIZING) || proc_alive (p);
    }
  if ((h = OpenProcess (STANDARD_RIGHTS_REQUIRED, FALSE, p->dwProcessId))
      != NULL)
    {
      sip_printf ("it exists\n");
      CloseHandle (h);
      return ISSTATE(p, PID_INITIALIZING) || proc_alive (p);
    }

  sip_printf ("it doesn't exist\n");
  /* If the parent pid does not exist, clean this process out of the pinfo
   * table.  It must have died abnormally.
   */
  if (!p->parent_alive || !proc_exists (procinfo (p->ppid)))
    {
      p->hProcess = NULL;
      p->process_state = PID_NOT_IN_USE;
    }
  return FALSE;
}

/* Handle all subprocess requests
 */
#define vchild ((pinfo *) val)
int
proc_subproc (DWORD what, DWORD val)
{
  int rcw, rc = 1;
  int i, potential_match;
  DWORD exitcode;
  pinfo *child;
  waitq *w;

#define wval	 ((waitq *) val)

  sip_printf ("args: %x, %d\n", what, val);

  block_sig_dispatch ();		// No signals please

  if (!get_proc_lock (what, val))	// Serialize access to this function
    {
      sip_printf ("I am not ready\n");
      goto out1;
    }

  switch (what)
    {
    /* Add a new subprocess to the children arrays.
     * (usually called from the main thread)
     */
    case PROC_ADDCHILD:
      if (nchildren >= PSIZE - 1)
	alert_printf ("nchildren too large %d\n", nchildren);
      if (WaitForSingleObject (vchild->hProcess, 0) != WAIT_TIMEOUT)
	{
	  alert_printf ("invalid process handle %p.  pid %d, win pid %d\n",
			vchild->hProcess, vchild->pid, vchild->dwProcessId);
	  rc = 0;
	  break;
	}

      pchildren[nchildren] = vchild;
      hchildren[nchildren] = vchild->hProcess;
      sip_printf ("added pid %d to wait list, slot %d, winpid = %d\n",
		  vchild->pid, nchildren, vchild->dwProcessId); 

      /* Child inherits the wait_subproc handle.  It is used to determine if
       * the parent is still alive and processing subprocess termination.
       * If its parent is not alive, then the child will handle the task
       * of removing itself from the pinfo list.
       */
      vchild->parent_alive = hwait_subproc;
      nchildren++;
      wake_wait_subproc;
      break;

    /* A child is in the stopped state.  Scan wait() queue to see if anyone
     * should be notified.  (Called from wait_sig thread)
     */
    case PROC_CHILDSTOPPED:
      child = myself;		// Just to avoid accidental NULL dereference
      sip_printf ("Received stopped notification\n");
      goto scan_wait;

    /* A child process had terminated.
     * Possibly this is just due to an exec().  Cygwin implements an exec()
     * as a "handoff" from one windows process to another.  If child->hProcess
     * is different from what is recorded in hchildren, then this is an exec().
     * Otherwise this is a normal child termination event.
     * (called from wait_subproc thread)
     */
    case PROC_CHILDTERMINATED:
      rc = 0;
      child = pchildren[val];
      if (GetExitCodeProcess (hchildren[val], &exitcode) &&
	  hchildren[val] != child->hProcess)
	{
	  sip_printf ("pid %d[%d], reparented old hProcess %p, new %p\n",
		      child->pid, val, hchildren[val], child->hProcess);
	  CloseHandle (hchildren[val]);
	  hchildren[val] = child->hProcess; /* Filled out by child */
	  wake_wait_subproc;
	  break;			// This was an exec()
	}

      sip_printf ("pid %d[%d] terminated, handle %p, nchildren = %d, nzombies = %d\n",
		  child->pid, val, hchildren[val], nchildren, nzombies);
      remove_child (val);		// Remove from children arrays
      zombies[nzombies++] = child;	// Add to zombie array
      wake_wait_subproc;		// Notify wait_subproc thread that
					//  nchildren has changed.
      child->process_state = PID_ZOMBIE;// Walking dead
      if (!proc_loop_wait)		// Don't bother if wait_subproc is
	break;				//  exiting

      /* The POSIX spec seems to subtly imply that a SIGCHLD should be
       * sent prior to any wait()s being activated.  So, allow recursively
       * calling this function, and send a SIGCHLD to ourself.
       */
      (void) ReleaseMutex (sync_proc_subproc);
      rc = sig_send (NULL, SIGCHLD);
      if (!get_proc_lock (what, val))	// Get the lock again
	goto out1;			// Ouch.

    scan_wait:
      /* Scan the linked list of wait()ing threads.  If a wait's parameters
       * match this pid, then activate it.
       */
      for (w = &waitq_head; w->next != NULL; w = w->next)
	{
	  if ((potential_match = checkstate (w)) > 0)
	    sip_printf ("released waiting thread\n");
	  else if (potential_match < 0)
	    sip_printf ("only found non-terminated children\n");
	  else if (potential_match == 0)		// nothing matched
	    {
	      sip_printf ("waiting thread found no children\n");
	      HANDLE oldw = w->next->ev;
	      w->next->ev = NULL;
	      if (!SetEvent (oldw))
		alert_printf ("Couldn't wake up wait event, error = %d\n",
			      GetLastError ());
	      w->next = w->next->next;
	    }
	  if (w->next == NULL)
	    break;
	}

      sip_printf ("finished processing terminated/stopped child\n");
      break;

    /* Clear all waiting threads.  Called from exceptions.cc prior to
     * the main thread's dispatch to a signal handler function.
     * (called from wait_sig thread)
     */
    case PROC_CLEARWAIT:
      /* Clear all "wait"ing threads. */
      sip_printf ("clear waiting threads\n");
      for (w = &waitq_head; w->next != NULL; w = w->next)
	{
	  sip_printf ("clearing waiting thread, pid waited for = %d\n",
		      w->next->pid);
	  w->next->status = -1;		/* flag that a signal was received */
	  if (!SetEvent (w->next->ev))
	    alert_printf ("Couldn't wake up wait event, error = %d\n",
			  GetLastError ());
	}
      waitq_head.next = NULL;
      sip_printf ("finished clearing\n");
      break;

    /* Handle a wait4() operation.  Allocates an event for the calling
     * thread which is signaled when the appropriate pid exits or stops.
     * (usually called from the main thread)
     */
    case PROC_WAIT:
      wval->ev = NULL;		// Don't know event flag yet

      if (wval->pid <= 0)
	child = NULL;		// Not looking for a specific pid
      else if ((child = procinfo (wval->pid)) == NULL)
	goto out;		// invalid pid.  flag no such child

      wval->status = 0;		// Don't know status yet

      /* Put waitq structure at the end of a linked list. */
      for (w = &waitq_head; w->next != NULL; w = w->next)
	if (w->next == wval && (w->next = w->next->next) == NULL)
	  break;

      wval->next = NULL;	/* This will be last in the list */
      sip_printf ("wval->pid %d, wval->options %d\n", wval->pid, wval->options);

      /* If the first time for this thread, create a new event, otherwise
       * reset the event.
       */
      if ((wval->ev = wval->thread_ev) == NULL)
	wval->ev = wval->thread_ev = CreateEvent (&sa, FALSE, FALSE, NULL);
      ResetEvent (wval->ev);

      /* Scan list of children to see if any have died.
       * If so, the event flag is set so that the wait* ()
       * process will return immediately.
       *
       * If no children were found and the wait option was WNOHANG,
       * then set the pid to 0 and remove the waitq value from
       * consideration.
       */
      w->next = wval;		/* set at end of wait queue */
      if ((potential_match = checkstate (w)) <= 0)
	{
	  if (!potential_match)
	    {
	      w->next = NULL;		// don't want to keep looking
	      wval->ev = NULL;		// flag that there are no children
	      sip_printf ("no appropriate children, %p, %p\n",
			  wval->thread_ev, wval->ev);
	    }
	  else if (wval->options & WNOHANG)
	    {
	      w->next = NULL;		// don't want to keep looking
	      wval->pid = 0;		// didn't find a pid
	      if (!SetEvent (wval->ev))	// wake up wait4 () immediately
		alert_printf ("Couldn't wake up wait event, error = %d\n",
			      GetLastError ());
	      sip_printf ("WNOHANG and no terminated children, %p, %p\n",
			  wval->thread_ev, wval->ev);
	    }
	}
      if (w->next != NULL)
	sip_printf ("wait activated %p, %p\n", wval->thread_ev, wval->ev);
      else if (wval->ev != NULL)
	sip_printf ("wait activated %p.  Reaped zombie.\n", wval->ev);
      else
	sip_printf ("wait not activated %p, %p\n", wval->thread_ev, wval->ev);
      break;
  }

out:
  (void) ReleaseMutex (sync_proc_subproc);	// Release the lock
out1:
  allow_sig_dispatch ();			// Allow signals
  sip_printf ("returning %d\n", rc);
  return rc;
}

/* Terminate the wait_subproc thread.
 * Called on process exit.
 * Also called by spawn_guts to disassociate any subprocesses from this
 * process.  Subprocesses will then know to clean up after themselves and
 * will not become zombies.
 */
void
proc_terminate (void)
{
  sip_printf ("nchildren = %d, nzombies = %d\n", nchildren, nzombies);
  if (hwait_subproc)
    {
      int rc;
      block_sig_dispatch ();	// No signals allowed.  Sensitive negotiations.
      lock_pinfo_for_update (INFINITE);
      proc_loop_wait = 0;	// Tell wait_subproc thread to exit
      wake_wait_subproc;	// Wake wait_subproc loop

      /* Wait for wait_subproc thread to exit (but not *too* long) */
      if ((rc = WaitForSingleObject (hwait_subproc, WWSP)) != WAIT_OBJECT_0)
	if (rc == WAIT_TIMEOUT)
	  alert_printf ("WFSO(hwait_subproc) timed out\n");
	else
	  alert_printf ("WFSO(hwait_subproc), rc %d, error %d\n",
			rc, GetLastError ());
      CloseHandle (hwait_subproc);
      hwait_subproc = NULL;

      (void) WaitForSingleObject (sync_proc_subproc, WPSP);
      (void) proc_subproc (PROC_CLEARWAIT, 0);

      /* Clean out zombie processes from the pid list. */
      for (int i = 0; i < nzombies; i++)
	{
	  pinfo *child;
	  if ((child = zombies[i])->hProcess)
	    {
	      CloseHandle (child->hProcess);
	      child->hProcess = NULL;
	    }
	  child->process_state = PID_NOT_IN_USE;
	}

      /* Disassociate my subprocesses */
      for (int i = 0; i < nchildren; i++)
	{
	  DWORD r;
	  pinfo *child;
	  if ((child = pchildren[i])->process_state == PID_NOT_IN_USE)
	    continue;		// Should never happen
	  if (!child->hProcess)
	    sip_printf ("%d(%d) hProcess cleared already?\n", child->pid,
			child->dwProcessId);
	  else if (proc_exists (child))
	    {
	      sip_printf ("%d(%d) closing active child handle\n", child->pid,
			  child->dwProcessId);
	      CloseHandle (child->hProcess);
	      child->hProcess = NULL;
	    }
	  else
	    {
	      sip_printf ("%d(%d) doesn't exist\n", child->pid,
			  child->dwProcessId);
	      zap_subproc (child);
	      continue;
	    }
	  child->ppid = 1;
	  child->parent_alive = NULL;
	  if (child->pgid == myself->pid)
	    child->process_state |= PID_ORPHANED;
	}
      nchildren = nzombies = 0;

      /* Attempt to close and release sync_proc_subproc in a
       * non-raceable manner.
       */
      HANDLE h = sync_proc_subproc;
      sync_proc_subproc = NULL;
      ReleaseMutex (h);
      CloseHandle (h);
      unlock_pinfo ();
      allow_sig_dispatch ();
    }
  sip_printf ("leaving\n");
}

/* Clear pending signal from the sigtodo array
 */
void
sig_clear (int sig)
{
  (void) InterlockedExchange (sigtodo (myself, sig), 0L);
  return;
}

/* Force the wait_sig thread to wake up and scan the sigtodo array.
 */
void
sig_dispatch_pending (void)
{
  sip_printf ("entering\n");
  if (!hwait_sig)
    return;

  /* Wait for wait_sig to finish initializing, if appropriate */
  if (wait_sig_inited)
    {
      (void) WaitForSingleObject (wait_sig_inited, INFINITE);
      (void) CloseHandle (wait_sig_inited);
      wait_sig_inited = NULL;
    }

  if (ReleaseSemaphore (sigcatch_nosync, 1, NULL))
    Sleep (0);
  else if (!hwait_sig)
    sip_printf ("I'm going away now\n");
  else
    alert_printf ("error %d releasing sigcatch_nosync(%p)\n",
		  GetLastError (), sigcatch_nosync);
  return;
}

/* Message initialization.  Called from dll_crt0_1
 *
 * This routine starts the signal handling thread.  The wait_sig_inited
 * event is used to signal that the thread is ready to handle signals.
 * We don't wait for this during initialization but instead detect it
 * in sig_send to gain a little concurrency.
 */
void
sigproc_init (void)
{
  DWORD tid;

  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = FALSE;
  wait_sig_inited = CreateEvent (&sa, FALSE, FALSE, NULL);

  if (!(hwait_sig = CreateThread (&sa, 0, wait_sig, NULL, 0, &sigtid)))
    {
      alert_printf ("cannot create wait_sig thread, error = %d\n",
		    GetLastError ());
      api_fatal ("terminating");
    }

  /* sync_proc_subproc is used by proc_subproc.  It serialises
   * access to the children and zombie arrays.
   */
  if ((sync_proc_subproc = CreateMutex (&sa, FALSE, NULL)) == NULL)
    {
      alert_printf ("cannot create sync_proc_subproc mutex, error = %d\n",
		  GetLastError ());
      api_fatal ("terminating");
    }

  /* Initialize waitq structure for main thread.  A waitq structure is
   * allocated for each thread that executes a wait to allow multiple threads
   * to perform waits.  Pre-allocate a waitq structure for the main thread.
   */
  waitq *w;
  if ((w = (waitq *) TlsGetValue (waitq_storage)) == NULL)
    {
      w = &waitq_main;
      TlsSetValue (waitq_storage, (LPVOID) w);
    }
  memset (w, 0, sizeof *w);	// Just to be safe

  maintid = GetCurrentThreadId ();// For use in determining if signals
				  //  should be blocked.
  sip_printf ("process/signal handling enabled(%x)\n",
	      myself->process_state);
  return;
}

/* Called on process termination to terminate signal and process threads.
 */
void
sigproc_terminate (void)
{
  if (!sig_loop_wait)
    sip_printf ("sigproc_terminate: sigproc handling not active\n");
  else
    {
      int rc;
      sigproc_printf ("entering\n");
      block_sig_dispatch ();		// Avoid all signals while doing this
      /* If !hwait_sig, then the process probably hasn't even finished
       * its initialization phase.
       */
      if (hwait_sig)
	{
	  sig_loop_wait = 0;		// Tell wait_sig to exit when it is
					//  finished with anything it is doing
	  sig_dispatch_pending ();	// Wake up wait_sig

	  /* Wait for the wait_sig thread to exit */

	  if ((rc = WaitForSingleObject (hwait_sig, WSPX)) != WAIT_OBJECT_0)
	    alert_printf ("WFSO(hwait_sig) failed, rc = %d, err = %d\n",
			  rc, GetLastError ());
	  CloseHandle (hwait_sig);
	  hwait_sig = NULL;
	  CloseHandle (sigcatch_main);
	  CloseHandle (sigcatch_nonmain);
	  CloseHandle (sigcatch_nosync);
	  CloseHandle (sigcomplete_main);
	  CloseHandle (sigcomplete_nonmain);
	  CloseHandle (sig_was_dispatched);
	}
      proc_terminate ();		// Terminate process handling thread
      sip_printf ("done\n");
    }

  return;
}

/* Send a signal to another process by raising its signal semaphore.
 * If pinfo *p == NULL, send to the current process.
 * If sending to this process, wait for notification that a signal has
 * completed before returning.
 * If not sending to this process, grab the sig_dispatch mutex to prevent
 * the signal handler from dispatching to a function which may never return.
 * Otherwise, we'd get handle leaks.
 */
int
sig_send (pinfo *p, int sig)
{
  int rc = 1;
  DWORD tid = GetCurrentThreadId ();
  BOOL its_me;
  HANDLE thiscatch = NULL;
  HANDLE thiscomplete;

  /* FIXME: need to protect access of pinfo -- there's currently a
     serious race condition here even though it doesn't seem to be
     actively biting us now. */

  if (its_me = (p == NULL || p == myself))
    {
      if (!sig_loop_wait || !hwait_sig)
	goto out;		// Either exiting or not yet initializing
      /* See if this is the first signal call after initialization.
       * If so, wait for notification that all initialization has completed.
       * Then set the handle to NULL to avoid checking this again.
       */
      if (wait_sig_inited)
	{
	  (void) WaitForSingleObject (wait_sig_inited, INFINITE);
	  (void) CloseHandle (wait_sig_inited);
	  wait_sig_inited = NULL;
	}
      p = myself;
    }

  /* It is possible that the process is not yet ready to receive messages
   * or that it has exited.  Detect this.
   */
  if (!proc_alive (p))	/* Is the process accepting messages? */
    {
      sip_printf ("invalid pid %d(%x), signal %d\n",
		  p->pid, p->process_state, sig);
      set_errno (ESRCH);
      goto out;
    }

  sip_printf ("pid %d, signal %d, its_me %d\n", p->pid, sig, its_me);

  if (its_me)
    {
      if (sig == __SIGSUSPEND)
	{
	  thiscatch = sigcatch_nosync;
	  ResetEvent (sig_was_dispatched);
	}
      else if (tid != maintid)
	{
	  thiscatch = sigcatch_nonmain;
	  thiscomplete = sigcomplete_nonmain;
	}
      else
	{
	  thiscatch = sigcatch_main;
	  thiscomplete = sigcomplete_main;
	  ResetEvent (thiscatch);
	}
    }
  else if ((thiscatch = getsem (p, "sigcatch", 0, 0)))
    block_sig_dispatch ();	// We've got the handle, don't allow signals
				//  (see above)
  else
    goto out;			// Couldn't get the semaphore.  getsem issued
				//  an error, if appropriate.

  /* Increment the sigtodo array to signify which signal to assert.
   */
  (void) InterlockedIncrement (sigtodo (p, sig));

  /* Notify the process that a signal has arrived.
   */
  if (!ReleaseSemaphore (thiscatch, 1, NULL))
    {
      /* Couldn't signal the semaphore.  This probably means that the
       * process is exiting.
       */
      if (!its_me)
	{
	  CloseHandle (thiscatch);
	  allow_sig_dispatch ();
	}
      else
	{
	  // (void) ResumeThread (hwait_sig);
	  if (!hwait_sig)
	    sip_printf ("I'm going away now\n");
	  else
	    alert_printf ("error sending signal(%d) to pid %d, error = %d\n",
			  sig, p->pid, GetLastError ());
	}
      goto out;
    }

  /* No need to wait for signal completion unless this was a signal to
   * this process.
   *
   * If it was a signal to this process, wait for a dispatched signal
   * if this was __SIGSUSPEND.  Otherwise just wait for the wait_sig to
   * signal that it has finished processing the signal.
   */
  if (!its_me)
    {
      CloseHandle (thiscatch);
      sip_printf ("Not waiting for sigcomplete.  its_me %d sig %d\n",
		  its_me, sig);
      allow_sig_dispatch ();
      rc = WAIT_OBJECT_0;
    }
  else if (sig == __SIGSUSPEND)
    {
      sip_printf ("Waiting for sig_was_dispatched\n");
      ReleaseMutex (sig_dispatch);
      rc = WaitForSingleObject (sig_was_dispatched, INFINITE);
    }
  else
    {
      sip_printf ("Waiting for thiscomplete\n");
      rc = WaitForSingleObject (thiscomplete, WSSC);
    }

  if (rc == WAIT_OBJECT_0)
    rc = 0;		// Successful exit
  else
    {
      alert_printf ("wait for %s_complete event failed, sig %d, rc %d, error %d\n",
		    (sig == __SIGSUSPEND) ? "suspend" : "sig", sig, rc,
		    GetLastError ());
      set_errno (ENOSYS);
      rc = -1;
    }

out:
  sip_printf ("returning %d from sending signal %d\n", rc, sig);
  return rc;
}

/* Set pending signal from the sigtodo array
 */
void
sig_set_pending (int sig)
{
  (void) InterlockedIncrement (sigtodo (myself, sig));
  return;
}

/* Initialize the wait_subproc thread.
 * Called from fork() or spawn() to initialize the handling of subprocesses.
 */
void
subproc_init (void)
{
  if (hwait_subproc)
    return;

  SECURITY_ATTRIBUTES sa2;
  sa2.nLength = sizeof (sa2);
  sa2.lpSecurityDescriptor = NULL;
  sa2.bInheritHandle = TRUE;

  /* A "wakeup" handle which can be toggled to make wait_subproc reexamine
   * the hchildren array.
   */
  events[0] = CreateEvent (&sa, FALSE, FALSE, NULL);
  if (!(hwait_subproc = CreateThread (&sa2, 0, wait_subproc, NULL, 0,
				      &proctid)))
    alert_printf ("cannot create wait_subproc thread, error = %d\n",
		  GetLastError ());
  sip_printf ("started wait_subproc thread %p,%p\n",
	      hwait_subproc, proctid);
}

/* Allow sig_handle to dispatch signals to their handler functions.
 */
void
allow_sig_dispatch (void)
{
  DWORD tid;
  /* There is no need to worry about being interrupted by a signal if
   * we are not executing in the main thread since only the main thread
   * will be interrupted.
   */
  if (hwait_sig == NULL)
    sip_printf ("process is exiting\n");
  else if ((tid = GetCurrentThreadId ()) != maintid)
    sip_printf ("current thread id %p != maintid %p\n", tid, maintid);
  else
    {
      sip_printf ("releasing sig_dispatch mutex (%p)\n", sig_dispatch);
      ReleaseMutex (sig_dispatch);
      sig_dispatch_pending ();
    }
}

/* Block sig_handle from dispatching signals to their handler functions.
 */
void
block_sig_dispatch (void)
{
  /* There is no need to worry about being interrupted by a signal if
   * we are not executing in the main thread since only the main thread
   * will be interrupted.
   */
  if (hwait_sig == NULL)
    sip_printf ("process is exiting\n");
  else if (GetCurrentThreadId () != maintid)
    sip_printf ("current thread id %p != maintid %p\n",
		GetCurrentThreadId (), maintid);
  else
    {
      sip_printf ("waiting for sig_dispatch (%p)\n", sig_dispatch);
      if (WaitForSingleObject (sig_dispatch, WBSD) != WAIT_OBJECT_0)
	alert_printf ("WFSO(sig_dispatch<%p>) failed, error = %d\n",
		      sig_dispatch, GetLastError ());
    }
}

/* Check the state of all of our children to see if any are stopped or
 * terminated.
 */
static int
checkstate (waitq *w)
{
  int i, x, potential_match = 0;
  pinfo *child;

  sip_printf ("nchildren = %d, nzombies = %d\n", nchildren, nzombies);

  /* Check already dead processes first to see if they match the criteria
   * given in w->next.
   */
  for (i = 0; i < nzombies; i++)
    if ((x = stopped_or_terminated (w, child = zombies[i])) < 0)
      potential_match = -1;
    else if (x > 0)
      {
	remove_zombie (i);
	potential_match = 1;
	goto out;
      }

  sip_printf ("checking alive children\n");

  /* No dead terminated children matched.  Check for stopped children. */
  for (i = 0; i < nchildren; i++)
    if ((x = stopped_or_terminated (w, pchildren[i])) < 0)
      potential_match = -1;
    else if (x > 0)
      {
	potential_match = 1;
	break;
      }

out:
  sip_printf ("returning %d\n", potential_match);
  return potential_match;
}

/* Get or create a process specific semaphore used in message passing.
 */
static HANDLE
getsem (pinfo *p, char *s, int init, int max)
{
  HANDLE h;

  if (p != NULL && !proc_alive (p))
    {
      set_errno (ESRCH);
      return NULL;
    }

  SetLastError (0);
  if (p == NULL)
    {
      DWORD winpid = GetCurrentProcessId ();
      h = CreateSemaphore (&sa, init, max, s = cygname (s, winpid));
      p = myself;
    }
  else
    {
      h = OpenSemaphore (SEMAPHORE_ALL_ACCESS, FALSE,
			 s = cygname (s, p->dwProcessId));

      if (h == NULL)
	{
	  if (GetLastError () == ERROR_FILE_NOT_FOUND && !proc_exists (p))
	    set_errno (ESRCH);
	  else
	    set_errno (EPERM);
	  return NULL;
	}
    }

  if (!h)
    {
      int err = GetLastError ();
      alert_printf ("can't %s %s, error = %d\n",
		    p == NULL ? "create" : "open", s, err);
      set_errno (ESRCH);
    }
  return h;
}



/* Get the sync_proc_subproc mutex to control access to
 * children, zombie arrays.
 * Attempt to handle case where process is exiting as we try to grab
 * the mutex.
 */
static BOOL __inline
get_proc_lock (DWORD what, DWORD val)
{
  DWORD rc;
  Static int lastwhat = -1;

  if (!sync_proc_subproc)
    return FALSE;
  if ((rc = WaitForSingleObject (sync_proc_subproc, WPSP)) == WAIT_OBJECT_0)
    {
      lastwhat = what;
      return TRUE;
    }
  if (!sync_proc_subproc)
    return FALSE;
  alert_printf ("WFSO(sync_proc_subproc) %d for(%d,%d), err %d, last %d\n",
		rc, what, val, GetLastError (), lastwhat);
  return TRUE;
}

/* Send __SIGSTRACE signal to children.
 */
static void
proc_strace (void)
{
  for (int i = 0; i < nchildren; i++)
    sip_printf ("child %d, handle %p, has not terminated\n",
		pchildren[i]->pid, hchildren[i]);
  for (int i = 0; i < nzombies; i++)
    sip_printf ("child %d, handle %p, has terminated\n", zombies[i]->pid,
		zombies[i]->hProcess);

  strace_dump ();
  for (int i = 0; i < nchildren; i++)
    sig_send (pchildren[i], __SIGSTRACE);
}

/* Remove a child from pchildren/hchildren by swapping it with the
 * last child in the list.
 */
static void
remove_child (int ci)
{
  sip_printf ("removing [%d], pid %d, handle %p, nchildren %d\n",
	      ci, pchildren[ci]->pid, hchildren[ci], nchildren);
  if (ci < --nchildren)
    {
      pchildren[ci] = pchildren[nchildren];
      hchildren[ci] = hchildren[nchildren];
    }

  return;
}

/* Remove a zombie from zombies by swapping it with the last child in the list.
 */
static void
remove_zombie (int ci)
{
  sip_printf ("removing %d, pid %d, nzombies %d\n", ci, zombies[ci]->pid,
	      nzombies);
  if (ci < --nzombies)
    zombies[ci] = zombies[nzombies];

  return;
}

/* Check status of child process vs. waitq member.
 *
 * parent_w is the pointer to the parent of the waitq member in question.
 * child is the subprocess being considered.
 *
 * Returns
 *   1 if stopped or terminated child matches parent_w->next criteria
 *  -1 if a non-stopped/terminated child matches parent_w->next criteria
 *   0 if child does not match parent_w->next criteria
 */
static int
stopped_or_terminated (waitq *parent_w, pinfo *child)
{
  int potential_match;
  waitq *w = parent_w->next;

  sip_printf ("considering pid %d\n", child->pid);
  if (w->pid == -1)
    potential_match = 1;
  else if (w->pid == 0)
    potential_match = child->pgid == myself->pgid;
  else if (w->pid < 0)
    potential_match = child->pgid == -w->pid;
  else
    potential_match = (w->pid == child->pid);

  if (!potential_match)
    return 0;

  BOOL terminated;

  if ((terminated = child->process_state == PID_ZOMBIE) ||
      (w->options & WUNTRACED) && child->stopsig)
    {
      parent_w->next = w->next;	/* successful wait.  remove from wait queue */
      w->pid = child->pid;

      if (!terminated)
	{
	  w->status = (child->stopsig << 8) | 0x7f;
	  child->stopsig = 0;
	}
      else
	{
	  DWORD status;
	  if (!GetExitCodeProcess (child->hProcess, &status))
	    status = 0xffff;
	  if (status & EXIT_SIGNAL)
	    w->status = (status >> 8) & 0xff;	/* exited due to signal */
	  else
	    w->status = (status & 0xff) << 8;	/* exited via "exit ()" */

	  add_rusage (&myself->rusage_children, &child->rusage_children);
	  add_rusage (&myself->rusage_children, &child->rusage_self);

	  if (w->rusage)
	    {
	      add_rusage ((struct rusage *) w->rusage, &child->rusage_children);
	      add_rusage ((struct rusage *) w->rusage, &child->rusage_self);
	    }
	  zap_subproc (child);
	}

      if (!SetEvent (w->ev))	/* wake up wait4 () immediately */
	alert_printf ("Couldn't wake up wait event, error = %d\n",
		      GetLastError ());
      return 1;
    }

  return -potential_match;
}

#ifdef DEBUGGING
/* Return the symbolic name of the current thread for debugging.
 */
static char *threadname (void)
{
    DWORD tid = GetCurrentThreadId ();
    char *p;
    Static char buf[30];

    if (tid == proctid)
      p = "proc";
    else if (tid == sigtid)
      p = "signal";
    else if (tid == maintid)
      p = "main";
    else
      __small_sprintf (p = buf, "unknown (%p)", tid);
    return p;
}
#endif

/* Process signals by waiting for a semaphore to become signaled.
 * Then scan an in-memory array representing queued signals.
 * Executes in a separate thread.
 *
 * Signals sent from this process are sent a completion signal so
 * that returns from kill/raise do not occur until the signal has
 * has been handled, as per POSIX.
 */
static DWORD
wait_sig (VOID *arg)
{
  /* Initialization */
  (void) SetThreadPriority (hwait_sig, WAIT_SIG_PRIORITY);

  /* sigcatch_nosync       - semaphore incremented by sig_dispatch_pending and
   *		             by foreign processes to force an examination of
   *		             the sigtodo array.
   * sigcatch_main         - ditto for local main thread.
   * sigcatch_nonmain      - ditto for local non-main threads.
   *
   * sigcomplete_main	   - event used to signal main thread on signal
   *			     completion
   * sigcomplete_nonmain   - semaphore signaled for non-main thread on signal
   *			     completion
   *
   * sig_was_dispatched	   - local event signaled when main thread has been
   *			     dispatched to a signal handler function.
   */
  sigcatch_nosync = getsem (NULL, "sigcatch", 0, MAXLONG);
  sigcatch_nonmain = CreateSemaphore (&sa, 0, MAXLONG, NULL);
  sigcatch_main = CreateSemaphore (&sa, 0, MAXLONG, NULL);
  sigcomplete_nonmain = CreateSemaphore (&sa, 0, MAXLONG, NULL);
  sigcomplete_main = CreateEvent (&sa, FALSE, FALSE, NULL);
  sig_was_dispatched = CreateEvent (&sa, FALSE, FALSE, NULL);
  

  /* Setting dwProcessId flags that this process is now capable of receiving
   * signals.  Prior to this, dwProcessId was set to the windows pid of
   * of the original windows process which spawned us unless this was a
   * "toplevel" process.
   */
  myself->dwProcessId = GetCurrentProcessId ();
  myself->process_state |= PID_ACTIVE;
  myself->process_state &= ~PID_INITIALIZING;

  /* If we've been execed, then there is still a stub left in the previous
   * windows process waiting to see if it's started a cygwin process or not.
   * Signalling subproc_ready indicates that we are a cygwin process.
   */
  if (ISSTATE(myself, PID_EXECED))
    {
      debug_printf ("subproc_ready %p\n", myself->subproc_ready);
      if (!SetEvent (myself->subproc_ready))
	system_printf ("SetEvent (subproc_ready) failed, error = %d\n",
		       GetLastError ());
      CloseHandle (myself->subproc_ready);
      myself->process_state &= ~PID_EXECED;
      myself->subproc_ready = NULL;
    }

  SetEvent (wait_sig_inited);

  HANDLE catchem[] = {sigcatch_main, sigcatch_nonmain, sigcatch_nosync};
  for (;;)
    {
      int rc = WaitForMultipleObjects (3, catchem, FALSE, sig_loop_wait);

      /* sigproc_terminate sets sig_loop_wait to zero to indicate that
       * this thread should terminate.
       */
      if (rc == WAIT_TIMEOUT)
	  break;			// Exiting
      if (rc == WAIT_FAILED)
	{
	  if (sig_loop_wait != 0)
	    alert_printf ("WFMO failed, error = %d\n", GetLastError ());
	  break;
	}

      rc -= WAIT_OBJECT_0;
      int dispatched = FALSE;
      sip_printf ("awake\n");
      /* A sigcatch semaphore has been signaled.  Scan the sigtodo
       * array looking for any unprocessed signals.
       */
      for (int sig = -__SIGOFFSET; sig < NSIG; sig++)
	{
#ifdef NOSIGQUEUE
	  if (InterlockedExchange (sigtodo (myself, sig), 0L) > 0)
#else
	  while (InterlockedDecrement (sigtodo (myself, sig)) >= 0)
#endif
	    {
	      if (sig > 0 && sig != SIGCONT && sig != SIGKILL && sig != SIGSTOP)
		if (sigismember (&(myself->sig_mask), sig) ||
		    myself->process_state & PID_STOPPED)
		  break;
	      /* Found a signal to process */
	      sip_printf ("processing signal %d\n", sig);
	      switch (sig)
		{
		/* Internal signal to force a flush of strace data to disk. */
		case __SIGSTRACE:
		  proc_strace ();	// Dump cached strace_printf stuff.
		  break;
		/* Signalled from a child process that it has stopped */
		case __SIGCHILDSTOPPED:
		  sip_printf ("Received child stopped notification\n");
		  dispatched |= sig_handle (SIGCHLD);
		  if (proc_subproc (PROC_CHILDSTOPPED, 0))
		    dispatched = 1;
		  break;
		/* Called by sigsuspend for "nonraceable" detection of
		 * dispatched signals.
		 * Waits for sig_send to give up the sig_dispatch mutex
		 * before continuing.
		 */
		case __SIGSUSPEND:
		  WaitForSingleObject (sig_dispatch, WBSD);
		  ReleaseMutex (sig_dispatch);
		  Sleep (0); Sleep (0);
		  break;
		/* A normal UNIX signal */
		default:
		  {
		    int this_dispatched;
		    sip_printf ("Got signal %d\n", sig);
		    dispatched |= (this_dispatched = sig_handle (sig));
		    /* If this_dispatch < 0, sig_handle (temporarily)
		     * couldn't get the sig_dispatch mutex, so, try the next
		     * signal and retry this one when the sig_dispatch mutex
		     * holder releases a signal semaphore (this should be
		     * guaranteed).
		     */
		    if (this_dispatched < 0)
		      {
			Sleep (1);
			goto nextsig;
		      }
		  }
		  break;
		}
	    }
#ifndef NOSIGQUEUE
	  (void) InterlockedIncrement (sigtodo (myself, sig));
#endif
	nextsig:
	  continue;
	}

      /* Signal completion of signal handling depending on which semaphore
       * woke up the WaitForMultipleObjects above.
       */
      switch (rc)
	{
	case 0:
	  SetEvent (sigcomplete_main);
	  break;
	case 1:
	  ReleaseSemaphore (sigcomplete_nonmain, 1, NULL);
	  break;
	default:
	  break;
	  /* Signal from another process.  No need to synchronize. */
	}

      /* Signal that a signal was (or could have been) dispatched */
      if (dispatched)
	{
	  sip_printf ("releasing sig_was_dispatched\n");
	  Sleep (0); Sleep (0);
	  SetEvent (sig_was_dispatched);
	}
      sip_printf ("looping\n");
    }

  /* Exiting thread.  Cleanup.  Don't set to inactive if a child has been
   * execed with the same pid.
   */
  if (myself->dwProcessId == GetCurrentProcessId ())
    myself->process_state &= ~PID_ACTIVE;
  else
    sip_printf ("Did not clear PID_ACTIVE since %d != %d\n",
		myself->dwProcessId, GetCurrentProcessId ());

  /* Signal any waiting threads/processes for one final time. */
  SetEvent (sigcomplete_main);

  /* Saturate the sigcomplete_nomain semaphore. */
  for (int i = MAXLONG; !ReleaseSemaphore (sigcomplete_nonmain, i, NULL); i--)
    if (GetLastError () != ERROR_TOO_MANY_POSTS)
      break;

  /* In case of a sigsuspend */
  SetEvent (sig_was_dispatched);

  sip_printf ("done\n");
  return 0;
}

/* Wait for subprocesses to terminate. Executes in a separate thread. */
static DWORD
wait_subproc (VOID *arg)
{
  sip_printf ("starting\n");

  for (;;)
    {
      DWORD rc = WaitForMultipleObjects (nchildren + 1, events, FALSE,
					 proc_loop_wait);
      if (rc == WAIT_TIMEOUT)
	  break;			// Exiting

      if (rc == WAIT_FAILED)
	{
	  if (!proc_loop_wait)
	    break;

	  alert_printf ("wait failed. nchildren %d, wait %d, err %d\n",
			nchildren, proc_loop_wait, GetLastError ());
	  for (int i = 0; i < nchildren + 1; i++)
	    if ((rc = WaitForSingleObject (events[i], 0)) == WAIT_OBJECT_0 ||
	    	rc == WAIT_TIMEOUT)
	      continue;
	    else
	      alert_printf ("event[%d] %p, error %d\n", i, events[0],
			    GetLastError ());
	  break;
	}

      rc -= WAIT_OBJECT_0;
      if (rc-- != 0)
	(void)proc_subproc (PROC_CHILDTERMINATED, rc);
      sip_printf ("looping\n");
    }

  CloseHandle (events[0]);
  events[0] = NULL;
  sip_printf ("done\n");
  return 0;
}

/* Clear out a subprocess from pinfo. */
static void
zap_subproc (pinfo *child)
{
  (void) CloseHandle (child->hProcess);
  child->hProcess = NULL;
  child->process_state = PID_NOT_IN_USE;	/* a reaped child */
}
