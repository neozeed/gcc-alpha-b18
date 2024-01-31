/* exceptions.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "exceptions.h"
#include <stdio.h>
#define __INSIDE_CYGWIN32__

#include <mywinsock.h>

extern int (*i_WSACleanup) (void) PASCAL;

extern "C" void __cygwin32_stack_trace (void);

extern "C" exception_handler __cygwin32_exception_handler;

static BOOL ctrl_c_handler (DWORD);
static void really_exit (int);

/* This is set to indicate that we have already exited.  */

static NO_COPY int exit_already = 0;

static HANDLE NO_COPY hMainThread;	/* A handle to the main thread */
static NO_COPY HANDLE cs;		/* Lock critical signal processing */
HANDLE NO_COPY sig_dispatch;		/* Block dispatching to functions */


static const struct
{
  unsigned int code;
  const char *name;
}
status_info[] =
{
#define X(s) s, #s
  { X (STATUS_ABANDONED_WAIT_0) },
  { X (STATUS_ACCESS_VIOLATION) },
  { X (STATUS_ARRAY_BOUNDS_EXCEEDED) },
  { X (STATUS_BREAKPOINT) },
  { X (STATUS_CONTROL_C_EXIT) },
  { X (STATUS_DATATYPE_MISALIGNMENT) },
  { X (STATUS_FLOAT_DENORMAL_OPERAND) },
  { X (STATUS_FLOAT_DIVIDE_BY_ZERO) },
  { X (STATUS_FLOAT_INEXACT_RESULT) },
  { X (STATUS_FLOAT_INVALID_OPERATION) },
  { X (STATUS_FLOAT_OVERFLOW) },
  { X (STATUS_FLOAT_STACK_CHECK) },
  { X (STATUS_FLOAT_UNDERFLOW) },
  { X (STATUS_GUARD_PAGE_VIOLATION) },
  { X (STATUS_ILLEGAL_INSTRUCTION) },
  { X (STATUS_INTEGER_DIVIDE_BY_ZERO) },
  { X (STATUS_INTEGER_OVERFLOW) },
  { X (STATUS_INVALID_DISPOSITION) },
  { X (STATUS_IN_PAGE_ERROR) },
  { X (STATUS_NONCONTINUABLE_EXCEPTION) },
  { X (STATUS_NO_MEMORY) },
  { X (STATUS_PENDING) },
  { X (STATUS_PRIVILEGED_INSTRUCTION) },
  { X (STATUS_SINGLE_STEP) },
  { X (STATUS_STACK_OVERFLOW) },
  { X (STATUS_TIMEOUT) },
  { X (STATUS_USER_APC) },
  { X (STATUS_WAIT_0) },
  { 0, 0 }
#undef X
};


/* Initialization code.  */

#ifdef __i386__

// Set up the exception handler for the current thread.  The PowerPC & Mips
// use compiler generated tables to set up the exception handlers for each
// region of code, and the kernel walks the call list until it finds a region
// of code that handles exceptions.  The x86 on the other hand uses segment
// register fs, offset 0 to point to the current exception handler.

asm (".equ __except_list,0");

extern exception_list *_except_list asm ("%fs:__except_list");

static void
init_exception_handler (exception_list *el)
{
  el->handler = __cygwin32_exception_handler;
  el->prev = _except_list;
  _except_list = el;
}

#define INIT_EXCEPTION_HANDLER(el) init_exception_handler (el)
#endif

/* Serialize access to the signal handler.
 * This avoids multiple threads tromping on signal structures.
 * If timeout is != 0, also grab the sig_dispatch mutex.  Ownership of
 * this mutex means that signals will not be dispatched to their handler
 * functions unless the mutex is owned by sighandle().
 */
static BOOL
lock_cs (DWORD timeout)
{
  int rc, ret = TRUE;

  if (timeout)
    if ((rc = WaitForSingleObject (sig_dispatch, timeout)) == WAIT_OBJECT_0 ||
	rc == WAIT_TIMEOUT)
      sigproc_printf ("sig_dispatch %d\n", rc);
    else
      {
	system_printf ("lock_cs: WFSO(sig_dispatch), rc %d, error %d\n",
		       rc, GetLastError ());
	ret = FALSE;
      }

  if ((rc = WaitForSingleObject (cs, 37000)) != WAIT_OBJECT_0)
    {
      system_printf ("lock_cs: WFSO(cs), rc %d, error %d\n", rc,
		     GetLastError ());
      ret = FALSE;
    }

  return ret;
}

/* Release whatever mutexes have been locked.
 */
static void
unlock_cs (BOOL avoidsigs)
{
  (void) ReleaseMutex (cs);
  if (avoidsigs)
    {
      (void) ReleaseMutex (sig_dispatch);
      sigproc_printf ("released sig_dispatch\n");
    }
}

extern "C"
void
init_exceptions (exception_list *el)
{
#ifdef INIT_EXCEPTION_HANDLER
  INIT_EXCEPTION_HANDLER (el);
#endif

  if (!SetConsoleCtrlHandler (ctrl_c_handler, TRUE))
    system_printf ("SetConsoleCtrlHandler failed.  error = %d\n",
		   GetLastError ());
  DuplicateHandle (GetCurrentProcess (),
	     GetCurrentThread (),
	     GetCurrentProcess (),
	     &hMainThread,
	     0,
	     FALSE, /* Want kids to see thread id */
	     DUPLICATE_SAME_ACCESS);

  if ((cs = CreateMutex (NULL, FALSE, NULL)) == NULL)
    api_fatal ("Can't create signal mutex (cs)\n");

  if ((sig_dispatch = CreateMutex (NULL, FALSE, NULL)) == NULL)
    api_fatal ("Can't create signal mutex (sig_dispatch)\n");
}

/* Utilities for dumping the stack, etc.  */

#ifdef __PPC__
static char *
hexify (DWORD value, int which)
{
  static NO_COPY char buffer[8][16];
  char *ret = &buffer[which][0];
  char *p = ret;
  int i;

  *p = '0';
  *++p = 'x';
  for (i = 28; i >= 0; i -= 4)
    *++p = "0123456789abcdef"[ (value >> i) & 0xf ];

  *++p = '\0';
  return ret;
}
#endif

static void
dump_status (EXCEPTION_RECORD *e,  CONTEXT *in)
{
#ifdef __PPC__
#define HAVE_STATUS
  system_printf ("Exception trapped!\n");
  if (e)
    system_printf ("exception 0x%x at %s\n", e->ExceptionCode, hexify (in->Iar, 0));
  else
    system_printf ("Null exception record at %s\n", hexify (in->Iar, 0));

  system_printf (" r0: %s  sp: %s toc: %s  r3: %s\n",
		 hexify (in->Gpr0, 0), hexify (in->Gpr1, 1),
		 hexify (in->Gpr2, 2), hexify (in->Gpr3, 3));

  system_printf (" r4: %s  r5: %s  r6: %s  r7: %s\n",
		 hexify (in->Gpr4, 0), hexify (in->Gpr5, 1),
		 hexify (in->Gpr6, 2), hexify (in->Gpr7, 3));

  system_printf (" r8: %s  r9: %s r10: %s r11: %s\n",
		 hexify (in->Gpr8,  0), hexify (in->Gpr9,  1),
		 hexify (in->Gpr10, 2), hexify (in->Gpr11, 3));

  system_printf ("r12: %s r13: %s r14: %s r15: %s\n",
		 hexify (in->Gpr12, 0), hexify (in->Gpr13, 1),
		 hexify (in->Gpr14, 2), hexify (in->Gpr15, 3));

  system_printf ("r16: %s r17: %s r18: %s r19: %s\n",
		 hexify (in->Gpr16, 0), hexify (in->Gpr17, 1),
		 hexify (in->Gpr18, 2), hexify (in->Gpr19, 3));

  system_printf ("r20: %s r21: %s r22: %s r23: %s\n",
		 hexify (in->Gpr20, 0), hexify (in->Gpr21, 1),
		 hexify (in->Gpr22, 2), hexify (in->Gpr23, 3));

  system_printf ("r24: %s r25: %s r26: %s r27: %s\n",
		 hexify (in->Gpr24, 0), hexify (in->Gpr25, 1),
		 hexify (in->Gpr26, 2), hexify (in->Gpr27, 3));

  system_printf ("r28: %s r29: %s r30: %s r31: %s\n",
		 hexify (in->Gpr28, 0), hexify (in->Gpr29, 1),
		 hexify (in->Gpr30, 2), hexify (in->Gpr31, 3));

  system_printf (" cr: %s xer: %s  lr: %s ctr: %s\n",
		 hexify (in->Cr, 0), hexify (in->Xer, 1),
		 hexify (in->Lr, 2), hexify (in->Ctr, 3));
#endif

#ifdef __i386__
#define HAVE_STATUS
  system_printf ("Exception trapped!\n");
  system_printf ("exception %x at %x\n", e->ExceptionCode, in->Eip);
  system_printf ("exception: ax %x bx %x cx %x dx %x\n",
		 in->Eax, in->Ebx, in->Ecx, in->Edx);
  system_printf ("exception: si %x di %x bp %x sp %x\n",
		 in->Esi, in->Edi, in->Ebp, in->Esp);
#endif

#ifdef __alpha
#define HAVE_STATUS
  system_printf ("Exception trapped!\n");
  system_printf ("exception %x at %x\n", e->ExceptionCode, in->Fir);
  system_printf ("exception: SP %x FP %x A0 %x A1 %x\n",
		in->IntSp, in->IntFp, in->IntA0, in->IntA1);
  system_printf ("exception: a2 %x a3 %x a4 %x a5 %x\n",
		 in->IntA2, in->IntA3, in->IntA4, in->IntA5);
  system_printf ("exception: gp %x ra %x\n",
		 in->IntGp,in->IntRa);
#endif
#ifndef HAVE_STATUS
  system_printf ("Had an exception\n");
#endif

  if (e)
    {
      for (int i = 0; status_info[i].name; i++)
	{
	  if (status_info[i].code == e->ExceptionCode)
	    {
	      system_printf ("exception is: %s\n", status_info[i].name);
	      break;
	    }
	}
    }
}

/* Print a stack backtrace.
   This is defined as a C function so it's callable from C.
   Please keep the output the same across all platforms.  */

extern "C" {
#ifdef __i386__
#define HAVE_STACK_TRACE
void
__cygwin32_stack_trace (void)
{
  register int i;
  register char **ebp;

  asm ("mov %%ebp,%0": "=r" (ebp):);

  system_printf ("Stack trace:\n");
  for (i = 0; i < 16; ++i)
    {
      system_printf ("frame %d: sp = %p, pc = %p\n",
		     i, ebp, ebp[1]);
      /* Top of stack?  */
      if (ebp[1] == 0)
	break;
      ebp = ((char ***) ebp)[0];
    }
  system_printf ("End of stack trace%s\n",
		 i == 16 ? " (more stack frames may be present)" : "");
}
#endif /* __i386__ */

#ifdef __PPC__
#define HAVE_STACK_TRACE
void
__cygwin32_stack_trace (void)
{
  void **fp = (void **) __builtin_frame_address (1);
  int i;

  system_printf ("Stack trace:\n");
  for (i = 0; i < 16; ++i)
    {
      system_printf ("frame %d: sp = %s, pc = %s\n",
		    i, hexify ((DWORD) fp, 0), hexify ((DWORD) fp[-1], 1));
      fp = (void **) *fp;
      if (! fp)
	break;
    }
  system_printf ("End of stack trace%s\n",
		 i == 16 ? " (more stack frames may be present)" : "");
}
#endif /* __PPC__ */

#ifndef HAVE_STACK_TRACE
void
__cygwin32_stack_trace (void)
{
  system_printf ("Stack trace not yet supported on this machine.\n");
}
#endif
}

/* Utilities to call a user supplied exception handler.  */

#ifdef __i386__
#define HAVE_CALL_HANDLER

extern "C"
void
set_process_mask (sigset_t newmask)
{
  BOOL unlockit = lock_cs (1);	// Get signal mutex, optionally avoid dispatch
  sigproc_printf ("old mask = %x, new mask = %x\n", myself->sig_mask, newmask);
  myself->sig_mask = newmask;	// Set a new mask
  unlock_cs (unlockit);		// Give up mutexes
  sig_dispatch_pending ();	// Tell signal thread to rescan sigtodo array
  return;
}

/* Non-raceable(?) sigsuspend
 */
int
handle_sigsuspend (sigset_t tempmask)
{
  sigset_t oldmask;
  int newerrno;

  lock_cs (60000);
  oldmask = myself->sig_mask;
  myself->sig_mask = tempmask;
  sigproc_printf ("old mask %x, new mask %x\n", oldmask, tempmask);
  unlock_cs (FALSE);
  /* Tell signal handler to wake me up when a signal arrives.
   * sig_send will release the sig_dispatch mutex as _SIGSUSPEND is
   * handled as a special case.
   */
  if (!sig_send (NULL, __SIGSUSPEND))
    newerrno = EINTR;
  else
    newerrno = ENOSYS;
  set_process_mask (oldmask);
  set_errno (newerrno);
  return -1;
}

static NO_COPY DWORD rethere;

static int
call_handler (int sig, _sig_func_ptr pfunc, int n, sigset_t oldmask)
{
  CONTEXT orig;
  int res;
  extern HANDLE hExeced;		// Process handle of new window
					//  process created by spawn_guts()
  extern DWORD exec_exit;		// Possible exit value for exec

  /* Only dispatch to handler if we can get sig_dispatch mutex.
   * Otherwise put the signal back into sigtodo and let someone else
   * worry about it.
   */
  if (WaitForSingleObject (sig_dispatch, 0) != WAIT_OBJECT_0)
    {
      sigproc_printf ("couldn't get sig_dispatch lock\n");
      sig_set_pending (sig);
      myself->sig_mask = oldmask;
      return -1;		// would have dispatched
    }
  sigproc_printf ("got sig_dispatch lock\n");

  if (hExeced != NULL)
    {
      SetEvent (signal_arrived);	// Just signal spawn_guts stub
      exec_exit = n;			// Maybe we'll exit with this value
      return 1;
    }

  /* Suspend the running thread, grab its context somewhere safe
     and run the exception handler in the context of the thread -
     we have to do that since sometimes they don't return - and if
     this thread doesn't return, you won't ever get another exception. */

  sigproc_printf ("Suspending %p\n", hMainThread);
  res = SuspendThread (hMainThread);
  sigproc_printf ("suspend said %d error %d\n", res, GetLastError ());

  /* Clear any waiting threads prior to dispatching to handler function */
  proc_subproc(PROC_CLEARWAIT, 0);

  orig.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
  if (!GetThreadContext (hMainThread, &orig))
    {
      system_printf ("call_handler: ouldn't get context of main thread.  err %d\n", GetLastError ());
      sig_set_pending (sig);
      return -1;		// would have dispatched
    }

  unsigned int *sp = (unsigned int *) orig.Esp;
  *(--sp) = orig.Eip;	/*  original IP where program was suspended */
  orig.Eip = (unsigned) &&wrap;

  *(--sp) = oldmask;
  *(--sp) = n;
  *(--sp) = (DWORD) pfunc;
  orig.Esp = (DWORD) sp;
  SetThreadContext (hMainThread, &orig); /* Restart the thread */
  ResumeThread (hMainThread);
  /* It looks like a bug in Windows NT, but several waiting threads are not
     always released on SetEvent () without this sleep...
  */
  Sleep (1);
  PulseEvent (signal_arrived);
  sigproc_printf ("returning\n");
  return 1;
  /* This code is run in the standard thread space */
  /* Commented out instructions are emulated already */
 wrap:
  asm (
//      "pushl	%eip\n"
//      "pushl 	_oldmask\n"
//      "pushl 	_sigarg\n"
//      "pushl 	_sigfunc\n");
      "pusha\n"
      "pushf\n"
      "orl	$0x0,(%esp)\n"  /* probe out enough room to play */
      "orl	$0x0,-0x800(%esp)\n"
      "orl	$0x0,-0x1000(%esp)\n"
      "pushl 	%ebp\n"
      "movl 	%esp,%ebp\n"
      "pushl	0xb*4(%ebp)\n"		// sigarg
      "movl	0xa*4(%ebp),%eax\n"	// sigfunc
      "call 	*%eax\n"
      "pushl	0xc*4(%ebp)\n"		// oldmask
      "call	_set_process_mask\n"
      "leave\n"
      "popf\n"
      "popa\n"
      "popl	_rethere\n"
      "popl	_rethere\n"
      "popl	_rethere\n"
      "ret");
  
}
#endif /* i386 */

#ifdef __PPC__
#define HAVE_CALL_HANDLER
// Given a function pointer (descriptor), return the real function address
static inline DWORD
descriptor_to_function (void (*pfunc)())
{
  DWORD *ptr = (DWORD *) (void *) pfunc;
#if 0
  debug_printf ("pfunc = %s, ptr = %s, ptr[0] = %s\n",
                hexify ((DWORD) pfunc, 0), hexify ((DWORD) ptr, 1),
                hexify ((DWORD) ptr[0], 2));

#endif
  return ptr[0];
}

// Given a function pointer (descriptor), return the GOT used by that function
static inline DWORD
descriptor_to_gotaddr (void (*pfunc)())
{
  DWORD *ptr = (DWORD *) (void *) pfunc;
#if 0
  debug_printf ("pfunc = %s, ptr = %s, ptr[1] = %s\n",
                hexify ((DWORD) pfunc, 0), hexify ((DWORD) ptr, 1),
                hexify ((DWORD) ptr[1], 2));

#endif
  return ptr[1];
}

// Stub started from call_handler to actually call the user function.
static void
call_stub (void (*pfunc)(), int n, CONTEXT *orig_context)
{
  DWORD function_address = descriptor_to_function (pfunc);
  debug_printf ("Call_stub before calling user function 0x%x\n",
		(int) function_address);

  (* (void (*) (int)) pfunc) (n);			// call the user function

  // If the main thread returns, we have to restore our original context.
  debug_printf ("got return from calling user function 0x%x\n",
		(int) function_address);
#if 0
  dump_status ((EXCEPTION_RECORD *) 0,  orig_context);
  really_exit (255);
#else
  orig_context->ContextFlags = CONTEXT_FULL;
  SetThreadContext (myself->hThread, orig_context);
  ResumeThread (myself->hThread);
  debug_printf ("Should never get here!!\n");
#endif
}

// Call the user function (in the user's thread) with argument n.
static void
call_handler (_sig_func_ptr pfunc, int n, EXCEPTION_RECORD *e, CONTEXT *in)
{
  CONTEXT *orig_context, context;
  int res;
  void (*stub_ptr) () = (void (*) ()) call_stub;
  void **old_sp;
  const size_t context_size = ((sizeof (context) + 15) / 16) * 16;
  const DWORD redzone_size = 224;			// max size compiler could write beyond end of SP aligned to 16 bytes
  const DWORD regsave_size = 8 * sizeof (void *);	// size to save 8 GPRS
  const DWORD tos_size = 6 * sizeof (void *);		// size of area callee must allocate

  /* Suspend the running thread, grab its context somewhere safe
     and run the exception handler in the context of the thread -
     we have to do that since sometimes they don't return - and if
     this thread doesn't return, you won't ever get another exception. */

  res = SuspendThread (myself->hThread);
  debug_printf ("suspend said %d (hThread = %d)\n", res,
                                           (int) myself->hThread);

  /* Clear any waiting threads prior to dispatching to handler function */
  proc_subproc(PROC_CLEARWAIT, 0);

  context.ContextFlags = CONTEXT_FULL;
  res = GetThreadContext (myself->hThread, &context);
  debug_printf ("get context said %d\n", res);

  if (strace () & (_STRACE_DEBUG | 1))
    dump_status (e, &context);

  /* now here comes the nasty stuff.  We push some stuff onto the stack of the
     main thread to pretend that it had a signal in a unixy way.  Under PowerPC
     NT, we have to advance the stack pointer, because we may have been
     interrupted while the function is in the prologue, and hasn't advanced the
     stack pointer yet.  In order that we don't have a race condition with
     another signal while we are processing the current one, copy the context
     structure to space on the main thread's stack, rather than use static
     storage.  */

  orig_context = (CONTEXT *) (context.Gpr1 - redzone_size - context_size);
  *orig_context = context;
  old_sp = (void **) context.Gpr1;
  context.Gpr1 -= redzone_size + regsave_size + tos_size + context_size;
  (* (void **) context.Gpr1) = *old_sp;			// update back chain in case there is a traceback
  context.Iar = descriptor_to_function (stub_ptr);
  context.Lr = orig_context->Iar;
  context.Gpr2 = descriptor_to_gotaddr (stub_ptr);
  context.Gpr3 = (DWORD) pfunc;				// arg 1
  context.Gpr4 = n;					// arg 2
  context.Gpr5 = (DWORD) orig_context;			// arg 3

  debug_printf ("about to restart thread at %s, new sp = %s\n",
	       hexify (context.Iar, 0), hexify (context.Gpr1, 1));
  debug_printf ("args = (%s, %s, %s)\n", hexify (context.Gpr3, 0),
	       hexify (context.Gpr4, 1), hexify (context.Gpr5, 2));

  res = SetThreadContext (myself->hThread, &context);	// Restart thread
  debug_printf ("SetThreadContext said %d\n", res);

  res = ResumeThread (myself->hThread);
  debug_printf ("ResumeThread said %d\n", res);
  return;
}
#endif /* ppc */

#ifdef __alpha

#define HAVE_CALL_HANDLER
extern "C"
void
set_process_mask (sigset_t newmask)
{
  BOOL unlockit = lock_cs (1);	// Get signal mutex, optionally avoid dispatch
  sigproc_printf ("old mask = %x, new mask = %x\n", myself->sig_mask, newmask);
  myself->sig_mask = newmask;	// Set a new mask
  unlock_cs (unlockit);		// Give up mutexes
  sig_dispatch_pending ();	// Tell signal thread to rescan sigtodo array
  return;
}

/* Non-raceable(?) sigsuspend
 */
int
handle_sigsuspend (sigset_t tempmask)
{
  sigset_t oldmask;
  int newerrno;
  lock_cs (60000);
  oldmask = myself->sig_mask;
  myself->sig_mask = tempmask;
  sigproc_printf ("old mask %x, new mask %x\n", oldmask, tempmask);
  unlock_cs (FALSE);
  /* Tell signal handler to wake me up when a signal arrives.
   * sig_send will release the sig_dispatch mutex as _SIGSUSPEND is
   * handled as a special case.
   */
  if (!sig_send (NULL, __SIGSUSPEND))
    newerrno = EINTR;
  else
    newerrno = ENOSYS;
  set_process_mask (oldmask);
  set_errno (newerrno);
  return -1;
}

static  NO_COPY void (*signalhandler)(int);
static  NO_COPY int Signal;
static  NO_COPY int omask;
 
static int
call_handler (int sig, _sig_func_ptr pfunc, int n, sigset_t oldmask)
{
  int res;
  extern HANDLE hExeced;		// Process handle of new window
					//  process created by spawn_guts()
  extern DWORD exec_exit;		// Possible exit value for exec
  CONTEXT context;
  

  /* Only dispatch to handler if we can get sig_dispatch mutex.
   * Otherwise put the signal back into sigtodo and let someone else
   * worry about it.
   */
  if (WaitForSingleObject (sig_dispatch, 0) != WAIT_OBJECT_0)
    {
      sigproc_printf ("couldn't get sig_dispatch lock\n");
      sig_set_pending (sig);
      myself->sig_mask = oldmask;
      return -1;		// would have dispatched
    }
  sigproc_printf ("got sig_dispatch lock\n");
  if (hExeced != NULL)
    {
      SetEvent (signal_arrived);	// Just signal spawn_guts stub
      exec_exit = n;			// Maybe we'll exit with this value
      return 1;
    }

  /* Suspend the running thread, grab its context somewhere safe
     and run the exception handler in the context of the thread -
     we have to do that since sometimes they don't return - and if
     this thread doesn't return, you won't ever get another exception. */

  sigproc_printf ("Suspending %p\n", hMainThread);
  res = SuspendThread (hMainThread);
  sigproc_printf ("suspend said %d error %d\n", res, GetLastError ());


  /* Clear any waiting threads prior to dispatching to handler function */
  proc_subproc(PROC_CLEARWAIT, 0);

  context.ContextFlags = CONTEXT_FULL ;

  if (!GetThreadContext (hMainThread, &context))
    {
      system_printf ("call_handler: ouldn't get context of main thread.  err %d\n", GetLastError ());
      sig_set_pending (sig);
      return -1;		// would have dispatched
    }

  context.IntRa=(DWORD)context.Fir; // where we want to return to
  context.Fir= (DWORD)&&wrap;    // function we wish to call
  signalhandler=pfunc;
  Signal=sig;
  omask = oldmask;  
  res = SetThreadContext (hMainThread, &context);	// Restart thread
  debug_printf ("SetThreadContext said %d\n", res);
  res = ResumeThread (hMainThread);
  debug_printf ("ResumeThread said %d\n", res);

  /* It looks like a bug in Windows NT, but several waiting threads are not
     always released on SetEvent () without this sleep...
  */
  Sleep (1);
  PulseEvent (signal_arrived);
  sigproc_printf ("returning\n");
  return 1;

wrap:

	asm (   
	"lda $30,-16($30)\n"
	"stq $26,0($30)\n"
	"stq $9,8($30)\n"
	"lda $1,Signal\n"
	"lda $2,signalhandler\n"
	"ldl $16,0($1)\n"
	"ldl $1,0($2)\n"
	"jsr $26,($1)\n"
	"lda $9,omask\n"
	"ldl $16,0($9)\n"
	"bsr $26,set_process_mask\n"
	"ldq $26,0($30)\n"
	"ldq $9,8($30)\n"
	"addq $30,16,$30\n"
	"ret $31,($26),1\n");
}
#endif

#ifndef HAVE_CALL_HANDLER
#error "Need to supply machine dependent call_handler"
#endif

/* Main exception handler.

   This function apparently needs to be exported for the ppc port.
   FIXME: Need to say why here!  */



int
__cygwin32_exception_handler (EXCEPTION_RECORD *e, void *arg, CONTEXT *in, void *x)
{
  int sig;

  /* If we've already exited, don't do anything here.  Returning 1
     tells Windows to keep looking for an exception handler.  */
  if (exit_already)
    return 1;

  /* Coerce win32 value to posix value.  */
  switch (e->ExceptionCode)
    {
    case STATUS_FLOAT_DENORMAL_OPERAND:
    case STATUS_FLOAT_DIVIDE_BY_ZERO:
    case STATUS_FLOAT_INEXACT_RESULT:
    case STATUS_FLOAT_INVALID_OPERATION:
    case STATUS_FLOAT_OVERFLOW:
    case STATUS_FLOAT_STACK_CHECK:
    case STATUS_FLOAT_UNDERFLOW:
    case STATUS_INTEGER_DIVIDE_BY_ZERO:
    case STATUS_INTEGER_OVERFLOW:
      sig = SIGFPE;
      break;

    case STATUS_ILLEGAL_INSTRUCTION:
    case STATUS_PRIVILEGED_INSTRUCTION:
    case STATUS_NONCONTINUABLE_EXCEPTION:
      sig = SIGILL;
      break;

    case STATUS_TIMEOUT:
      sig = SIGALRM;
      break;

    case STATUS_ACCESS_VIOLATION:
    case STATUS_DATATYPE_MISALIGNMENT:
    case STATUS_ARRAY_BOUNDS_EXCEEDED:
    case STATUS_GUARD_PAGE_VIOLATION:
    case STATUS_IN_PAGE_ERROR:
    case STATUS_NO_MEMORY:
    case STATUS_INVALID_DISPOSITION:
    case STATUS_STACK_OVERFLOW:
      sig = SIGSEGV;
      break;

    case STATUS_CONTROL_C_EXIT:
      sig = SIGINT;
      break;

    case STATUS_INVALID_HANDLE:
      /* CloseHandle will throw this exception if it is given an
         invalid handle.  We don't care about the exception; we just
         want CloseHandle to return an error.  This can be revisited
         if gcc ever supports Windows style structured exception
         handling.  */
      return 0;

    default:
      /* If we don't recognize the exception, we have to assume that
         we are doing structured exception handling, and we let
         something else handle it.  */
      return 1;
    }

#ifndef __alpha
  debug_printf ("In cygwin32_except_handler exc %x at %x sp %x\n", e->ExceptionCode, in->Eip, in->Esp);
  debug_printf ("In cygwin32_except_handler sig = %d at %x\n", sig, in->Eip);
#else
  debug_printf ("In cygwin32_except_handler exc %x at %x sp %x\n", e->ExceptionCode, in->Fir, in->IntSp);
  debug_printf ("In cygwin32_except_handler sig = %d at %x\n", sig, in->Fir);
#endif

  /* Print the exception to the console */
  if (e)
    {
      for (int i = 0; status_info[i].name; i++)
	{
	  if (status_info[i].code == e->ExceptionCode)
	    {
	      system_printf ("Exception: %s\n", status_info[i].name);
	      break;
	    }
	}
    }

  if (myself && myself->sigs[sig].sa_mask & (1<<sig))
    {
      syscall_printf ("signal %d masked 0x%x\n",
		      sig, myself->sigs[sig].sa_mask);
    }

  if (! myself
      || (void *) myself->sigs[sig].sa_handler == (void *) SIG_DFL
      || (void *) myself->sigs[sig].sa_handler == (void *) SIG_IGN
      || (void *) myself->sigs[sig].sa_handler == (void *) SIG_ERR)
    {

      static NO_COPY int traced = 0;

      /* Another exception could happen while tracing or while exiting.
	 Only do this once.  */
      if (traced++)
        {
          system_printf ("Error while dumping state (probably corrupted stack)\n");
        }
      else
	{
          /* write to progname.core if possible */
          char corefile[MAX_PATH], *p;
          p = strrchr (myself->progname, '\\');
          p = p ? p + 1 : myself->progname;
          sprintf (corefile, "%.*s.core", MAX_PATH - sizeof ".core", p);
          HANDLE h = CreateFile (corefile, GENERIC_WRITE, 0, 0,
                                 CREATE_ALWAYS, 0, 0);
          if (h != INVALID_HANDLE_VALUE)
            {
              system_printf ("Dumping stack trace to %s\n", corefile);
              SetStdHandle (STD_ERROR_HANDLE, h);
            }
	  dump_status (e, in);
	  __cygwin32_stack_trace ();
	}
      really_exit (EXIT_SIGNAL | 0x8000);
    }

  debug_printf ("In cygwin32_except_handler calling %x\n", 
                 myself->sigs[sig].sa_handler);

  sig_send (NULL, sig);		// Signal myself
  return 0;
}

/* Keyboard interrupt handler.  */
static BOOL
ctrl_c_handler (DWORD type)
{
  int sig;

  /* FIXME: The original version had code here to reinitialize the exception
     handler under the guise of initializing thread exceptions.  It's not
     clear what this code was ever intended to do.  */

  switch (type)
    {
    case CTRL_C_EVENT:
      sig = SIGINT;
      break;
    case CTRL_BREAK_EVENT:
      sig = SIGINT;
      break;
    case CTRL_CLOSE_EVENT:
      sig = SIGHUP;
      break;
    case CTRL_LOGOFF_EVENT:
      return 1;
      break;
    case CTRL_SHUTDOWN_EVENT:
      sig = SIGHUP;
      break;
    }

  sigproc_printf ("type %d, signal %d\n", type, sig);
  sig_send (NULL, sig);
  return 1;
}

int
sig_handle (int sig)
{
  int rc = 0;
  sigset_t oldmask;

  sigproc_printf ("signal %d\n", sig);

  lock_cs (FALSE);
  myself->rusage_self.ru_nsignals++;

  /* Clear pending SIGCONT on stop signals */
  if (sig == SIGSTOP || sig == SIGTSTP || sig == SIGTTIN || sig == SIGTTOU)
    sig_clear (SIGCONT);

  if (sig == SIGKILL)
    goto cont_exit_sig;
  if (sig == SIGSTOP)
    goto stop;
  if (sig == SIGCONT)
    {
      myself->stopsig = 0;
      myself->process_state &= ~PID_STOPPED;
      /* Clear pending stop signals */
      sig_clear (SIGSTOP);
      sig_clear (SIGTSTP);
      sig_clear (SIGTTIN);
      sig_clear (SIGTTOU);
      /* Windows 95 hangs on resuming non-suspended thread */
      SuspendThread (hMainThread);
      while (ResumeThread (hMainThread) > 1)
	;
      /* process pending signals */
      sig_dispatch_pending ();
    }

  if ((void *) myself->sigs[sig].sa_handler == (void *) SIG_DFL)
    {
      if (sig == SIGCHLD || sig == SIGIO || sig == SIGCONT || sig == SIGWINCH)
        {
          sigproc_printf ("default signal %d ignored\n", sig);
          goto done;
        }
      if (sig != SIGSTOP && sig != SIGTSTP && sig != SIGTTIN && sig != SIGTTOU)
	if (myself->pgid == 0 || NOTSTATE(myself, PID_STOPPED))
	  goto cont_exit_sig;
	else
	  goto exit_sig;

stop:
      /* Do not stop processes with pgid == 0.  These are top-level
	 processes that were not invoked by parent cygwin processes. */
      if (myself->pgid)
	{
	  HANDLE waitbuf[2];

	  /* Be sure that process's main thread isn't an owner of vital
	     mutex to prevent cygwin subsystem lockups */

	  waitbuf[0] = pinfo_mutex;
	  waitbuf[1] = title_mutex;
	  WaitForMultipleObjects (2, waitbuf, TRUE, INFINITE);
	  SuspendThread (hMainThread);
	  myself->stopsig = sig;
	  myself->process_state |= PID_STOPPED;
	  ReleaseMutex (pinfo_mutex);
	  ReleaseMutex (title_mutex);
	  /* See if we have a living parent.  If so, send it a special signal.
	   * It will figure out exactly which pid has stopped by scanning
	   * its list of subprocesses.
	   */
	  if (alive_parent(myself))
	    {
	      pinfo *parent = procinfo(myself->ppid);
	      sig_send (parent, __SIGCHILDSTOPPED);
	    } 
	}
      sigproc_printf ("process %d stopped by signal %d, parent_alive %p\n",
		      myself->pid, sig, myself->parent_alive);
      goto done;
    }

  if ((void *) myself->sigs[sig].sa_handler == (void *) SIG_IGN)
    {
      sigproc_printf ("signal %d ignored\n", sig);
      goto done;
    }

  if ((void *) myself->sigs[sig].sa_handler == (void *) SIG_ERR)
    {
    cont_exit_sig:
      SuspendThread (hMainThread);
      while (ResumeThread (hMainThread) > 1)
	continue;

    exit_sig:
      if (i_WSACleanup)
	(*i_WSACleanup) ();
      sigproc_printf ("signal %d, about to call do_exit\n", sig);
      /* We encode the signal stuff in the high 8 bits.
	 (sorta like the reverse of a standard wait)
	 This is so that ordinary dos progs can look at our
	 exit value. */
      rc = call_handler (sig, do_exit, (sig<<8) | EXIT_SIGNAL, (sigset_t) 0);
      goto done;
    }

  if ((sig == SIGCHLD) && (myself->sigs[sig].sa_flags & SA_NOCLDSTOP))
    goto done;

  /* Dispatch to the appropriate function. */

  oldmask = myself->sig_mask;
  myself->sig_mask |= myself->sigs[sig].sa_mask | (1<<sig);
  sigproc_printf ("signal %d, about to call %p\n", sig,
		myself->sigs[sig].sa_handler);
  rc = call_handler (sig, myself->sigs[sig].sa_handler, sig, oldmask);

  /* FIXME: The original version had code here to reinitialize the
     exception handler under the guise of initializing thread exceptions.
     It's not clear what this code was ever intended to do. */

done:
  unlock_cs (TRUE);
  sigproc_printf ("returning %d\n", rc);
  return rc;
}

/* Cover function to `do_exit' to handle exiting even in presence of more
   exceptions.  We use to call exit, but a SIGSEGV shouldn't cause atexit
   routines to run.  */

static void
really_exit (int rc)
{
  /* If the exception handler gets a trap, we could recurse awhile.
     If this is non-zero, skip the cleaning up and exit NOW.  */

  if (exit_already++)
    {
    /* We are going down - reset our process_state without locking. */
    myself->record_death_nolock ();
    ExitProcess (rc);
    }

  do_exit (rc);
}

HANDLE NO_COPY pinfo_mutex;
HANDLE NO_COPY signal_arrived;
HANDLE NO_COPY title_mutex;

void
events_init (void)
{
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.bInheritHandle = 0;
  sa.lpSecurityDescriptor = get_null_sd ();

  /* pinfo_mutex protects access to process table */

  if (!(pinfo_mutex = CreateMutex (&sa, FALSE, cygname ("pinfo_mutex", 0))))
    api_fatal ("Cygwin32: Catastrophic fail - unable to Create pinfo_mutex\n");

  /* title_mutex protects modification of console title. It's neccessary
     while finding console window handle */

  if (!(title_mutex = CreateMutex (&sa, FALSE, cygname ("title_mutex", 0))))
    {
      small_printf ("error %d:", GetLastError ());
      api_fatal ("Cygwin32: Can't create title mutex");
    }

  /* signal_arrived event raised by exception code to unblock blocking win32
     syscalls to switch main thread to handler routine */

  if (!(signal_arrived = CreateEvent (NULL, TRUE, FALSE, NULL)))
    api_fatal ("Cygwin32: Can't create signal event\n");
}

void
events_terminate (void)
{
//CloseHandle (pinfo_mutex);	// Use implicit close on exit to avoid race
  CloseHandle (signal_arrived);
  CloseHandle (title_mutex);
  CloseHandle (sig_dispatch);
  exit_already = 1;
}
