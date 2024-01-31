/* sigproc.h

   Copyright 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#define EXIT_SIGNAL    	 0x010000
#define EXIT_REPARENTING 0x020000
#define EXIT_NOCLOSEALL  0x040000

enum procstuff
{
  PROC_ADDCHILD		= 1,	// add a new subprocess to list
  PROC_CHILDSTOPPED	= 2,	// a child stopped
  PROC_CHILDTERMINATED	= 3,	// a child died
  PROC_CLEARWAIT	= 4,	// clear all waits - signal arrived
  PROC_WAIT		= 5	// setup for wait() for subproc
};

typedef struct struct_waitq
{
  int pid;
  int options;
  int status;
  HANDLE ev;
  void *rusage;			/* pointer to potential rusage */
  struct struct_waitq *next;
  HANDLE thread_ev;
} waitq;

enum
{
  __SIGSTRACE	    = -2,
  __SIGSUSPEND	    = -1,
  __SIGCHILDSTOPPED =  0,
  __SIGOFFSET	    =  2
};

extern HANDLE sig_dispatch;
extern DWORD waitq_storage;

extern void block_sig_dispatch (void);
extern void allow_sig_dispatch (void);

BOOL alive_parent (pinfo *);
void sig_dispatch_pending (void);
extern "C" void set_process_mask (sigset_t);
int sig_handle (int);
void sig_clear (int);
void sig_set_pending (int);
int handle_sigsuspend (sigset_t);

void proc_terminate (void);
void sigproc_init (void);
void subproc_init (void);
void sigproc_terminate (void);
BOOL proc_exists (pinfo *);
int proc_subproc (DWORD, DWORD);
int sig_send (pinfo *, int);
#define proc_register(child) \
	proc_subproc (PROC_ADDCHILD, (DWORD) (child))
