/* winsup.h: main Cygwin32 header file.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "windows.h"

#include <sys/types.h>
#include <sys/strace.h>
#include <sys/resource.h>
#include <setjmp.h>

#include <signal.h>
#undef sigemptyset	/* need to undefine macros created in newlib */
#undef sigaddset

#include <string.h>

#include "syscalls.h"
#include "fhandler.h"
#include "path.h"
#include "version.h"
#include "tty.h"
#include "delqueue.h"

/* Forward references. */
class pinfo;
class shared_info;

/* Now that pinfo has been defined, include... */
#include "sigproc.h"

/********************** Application Interface **************************/

/* This lives in the app and is initialized before jumping into the DLL.
   It should only contain stuff which the user's process needs to see, or
   which is needed before the user pointer is initialized, or is needed to
   carry inheritance information from parent to child.  Note that it cannot
   be used to carry inheritance information across exec!

   Remember, this structure is linked into the application's executable.
   Changes to this can invalidate existing executables, so we go to extra
   lengths to avoid having to do it.

   When adding/deleting members, remember to adjust {public,internal}_reserved.
   The size of the class shouldn't change [unless you really are prepared to
   invalidate all existing executables].  The program does a check (using
   SIZEOF_PER_PROCESS) to make sure you remember to make the adjustment.
*/

class per_process
{
 public:
  char *initial_sp;

  /* The offset of these 3 values can never change. */
  /* magic_biscuit is the size of this class and should never change. */
  int magic_biscuit;
  int version_major;
  int version_minor;

  struct _reent **impure_ptr_ptr;
  char ***envptr;

  /* Used to point to the memory machine we should use.  Usually these
     point back into the dll, but they can be overridden by the user. */
  void *(*malloc)(size_t);
  void (*free)(void *);
  void *(*realloc)(void *, size_t);

  int *fmode_ptr;

  int (*main)(int, char **, char **);
  void (**ctors)(void);
  void (**dtors)(void);

  /* For fork */
  void *data_start;
  void *data_end;
  void *bss_start;
  void *bss_end;

  void *(*calloc)(size_t, size_t);
  /* For future expansion of values set by the app. */
  void *public_reserved[4];

  /* The rest are *internal* to cygwin.dll.
     Those that are here because we want the child to inherit the value from
     the parent (which happens when bss is copied) are marked as such. */

  /* non-zero of ctors have been run.  Inherited from parent. */
  int run_ctors_p;

  /* These will be non-zero if the above (malloc,free,realloc) have been
     overridden. */
  /* FIXME: not currently used */
  int __imp_malloc;
  int __imp_free;
  int __imp_realloc;

  /* Heap management.  Inherited from parent. */
  void *base;			/* bottom of the heap */
  void *ptr;			/* current index into heap */
  int  size;			/* current size of heap */

  HANDLE strace_file;		/* strace output file handle, inherited
				 * from parent on fork. */

  /* Non-zero means the task was forked.  The value is the pid.
     Inherited from parent. */
  int forkee;

  void *hmodule;

  /* For future expansion, so apps won't have to be relinked if we
     add an item. */
  void *internal_reserved[10];
};

extern per_process *u; /* Pointer into the application's static data */

/* We use the following to test that sizeof hasn't changed.  When adding
   or deleting members, insert fillers or use the reserved entries.
   Do not change this value. */
#define SIZEOF_PER_PROCESS (42 * 4)

/*********************** File Descriptor Table **********************/

class hinfo
{
 public:
  fhandler_base *h;
  char item[sizeof (fhandler_union)];
  int is_open (void) const { return h != 0; }
  void clearout (void);
};

class hinfo_vec
{
 public:
  hinfo *vec;

  int not_open (int fd);
  hinfo & operator [] (int arg);
  int find_unused_handle (int start);
  void release (int fd);
  void lookup_fhandler (int fd, const char *path, int flags);
  void clearout (void);
  void init_std_file_from_handle (int fd, HANDLE handle, int bin,
					int access, const char *name);
  fhandler_base * build_fhandler (const char *name, int n, HANDLE h);
  void dup_for_exec (void);
  void dup_for_fork (hinfo_vec *child);
  int dup2 (int oldfd, int newfd);

  int linearize_fd_array (unsigned char *, int);
  LPBYTE de_linearize_fd_array (LPBYTE);
};

/************************* Process Table ****************************/

class pinfo
{
 public:

  /* If hProcess is set, it's because it came from a
     CreateProcess call.  This means it's process relative
     to the thing which created the process.  That's ok because
     we only use this handle from the parent. */
  HANDLE hProcess;

  /* These handles are set during a fork */

  HANDLE subproc_ready;
  HANDLE forker_finished;
  HANDLE parent_alive;

  /* There are two process ids here because during a spawn it is possible
   * for two separate Win32 processes to have the same cygwin pid.
   * dwProcessId contains the processid used for sending signals.  It
   * will be reset in a child process when it is capable of receiving
   * signals.
   * dwSpawnedProcessId is set by spawn_guts from the windows process id
   * returned from CreateProcess.  If this value == the current process id
   * then this is a flag to pinfo_init to reuse an existing pid.
   */
  DWORD dwProcessId, dwSpawnedProcessId;

  /* User information.
     The information is derived from the GetUserName system call,
     with the name looked up in /etc/passwd and assigned a default value
     if not found.  This data resides in the shared data area (allowing
     tasks to store whatever they want here) so it's for informational
     purposes only. */
  uid_t uid;	/* User ID */
  gid_t gid;	/* Group ID */
  pid_t pgid;	/* Process group ID */
  pid_t sid;	/* Session ID */
  int ctty;	/* Control tty */
  mode_t umask;

  /* Non-zero if process was stopped by a signal. */
  char stopsig;

  struct sigaction sigs[NSIG];
  sigset_t sig_mask;		/* one set for everything to ignore. */
  LONG _sigtodo[NSIG + __SIGOFFSET];
  #define sigtodo(p, sig) (((p)->_sigtodo + __SIGOFFSET) + (sig))

  /* Resources used by process. */
  long start_time;
  struct rusage rusage_self;
  struct rusage rusage_children;

  /* Used to spawn a child for fork(), among other things. */
  char progname[MAX_PATH];

  #define PINFO_ZERO ((((pinfo *)NULL)->progname + 1) - ((char *)NULL))

  /* Anything below this point is not zeroed automatically by allocate_pid */

  /* The pid stays the same, while the hProcess moves due to execs. */
  pid_t pid;
  /* Parent process id.  */
  pid_t ppid;

  /* Pointer to strace mask, 0 if not set yet.  See strace.cc. */
  DWORD strace_mask;
 
  /* Used during forking to jump back into the fork support routines. */
  jmp_buf restore;

  /* Various flags indicating the state of the process.  See PID_
     constants below. */
  DWORD process_state;

  /* Open file table. */
  hinfo_vec hmap;
  struct _reent reent_save;

  /* Pointer to mmap'ed areas for this process.  Set up by fork. */
  void *mmap_ptr;

  void record_death (void);
  void record_death_nolock (void);
  void init_from_exec (void);
};

#define ISSTATE(p, f)	(!!((p)->process_state & f))
#define NOTSTATE(p, f)	(!((p)->process_state & f))

/* Flags associated with process_state */
enum
{
  PID_NOT_IN_USE       = 0x0000, // Free entry.
  PID_IN_USE 	       = 0x0001, // Entry in use.
  PID_ZOMBIE	       = 0x0002, // Child exited: no parent wait.
  PID_STOPPED	       = 0x0004, // Waiting for SIGCONT.
  PID_TTYIN	       = 0x0008, // Waiting for terminal input.
  PID_TTYOU	       = 0x0010, // Waiting for terminal output.
  PID_ORPHANED	       = 0x0020, // Member of an orphaned process group.
  PID_ACTIVE	       = 0x0040, // Pid accepts signals.
  PID_CYGPARENT	       = 0x0080, // Set if parent was a cygwin app.
  PID_SPLIT_HEAP       = 0x0100, // Set if the heap has been split,
				 //  which means we can't fork again.
  PID_EXECED	       = 0x0200, // Set if process was execed.
  PID_SOCKETS_USED     = 0x0400, // Set if process uses Winsock.
  PID_INITIALIZING     = 0x0800, // Set until ready to receive signals.
  PID_USETTY	       = 0x1000, // Setting this enables or disables cygwin's
				 //  tty support.  This is inherited by
				 //  all execed or forked processes.
};

#define PSIZE 128
#define PBASE 1000

class pinfo_list
{
 private:
  pinfo *get_empty_pinfo (void);

 public:
  int next_pid_index;
  pinfo vec[PSIZE];
  char lock_info[MAX_PATH + 1];
  pinfo *operator[] (pid_t x);
  int size (void) { return PSIZE; }
  pinfo *lookup_by_handle (HANDLE *);
  pinfo *allocate_pid (void);
  void init (void);
};

void pinfo_init (void);
pinfo *procinfo (int n);

/******************* Host-dependent constants **********************/
/* Portions of the cygwin DLL require special constants whose values
   are dependent on the host system.  Rather than dynamically
   determine those values whenever they are required, initialize these
   values once at process start-up. */

class host_dependent_constants
{
 public:
  void init (void);
  
  /* Used by fhandler_disk_file::lock which needs a platform-specific
     upper word value for locking entire files. */
  DWORD win32_upper;

  /* fhandler_base::open requires host dependent file sharing
     attributes. */
  int shared;
};

extern host_dependent_constants host_dependent;

/************************** Shared data **************************/
/* This data is accessable to all tasks.
   FIXME: Security implications? */

class shared_info
{
  int inited;

public:
  pinfo_list p;

  /* FIXME: Doesn't work if more than one user on system. */
  mount_info mount;

  int heap_chunk_in_mb;
  int heap_chunk_size (void);

  tty_list t;
  delqueue_list delqueue;
  void initialize (void);
};

extern shared_info *s;

void shared_init (void);
void shared_terminate (void);

/* This is for programs that want to access the shared data. */
extern "C" class shared_info *cygwin32_getshared (void);

/*************************** Unsorted ******************************/

/* The size of the console title */
#define TITLESIZE 1024

#define WM_ASYNCIO	0x8000		// WM_APP

#ifndef __alpha
#define NO_COPY __attribute__((section(".data$nocopy")))
#else 
#define NO_COPY __attribute__((section(".ldata")))
#endif

/* Note that MAX_PATH is defined in the windows headers */
/* There is also PATH_MAX and MAXPATHLEN.
   PATH_MAX is from Posix and does *not* include the trailing NUL.
   MAXPATHLEN is from Unix.

   Thou shalt use MAX_PATH throughout.  It avoids the NUL vs no-NUL
   issue and is neither of the Unixy ones [so we can punt on which
   one is the right one to use].  */

/* Used when treating / and \ as equivalent. */
#define SLASH_P(C) ((C) == '/' || (C) == '\\')

/* Initial and increment values for cygwin's fd table */
#define NOFILE_INIT    32
#define NOFILE_INCR    32

/* Fork support and exec. */
void fork_init (void);
void fork_terminate (void);
void dump_jmp_buf (jmp_buf buf);

int spawn_guts (HANDLE hToken, const char *prog_arg,
                   const char *const *argv, const char *const envp[],
                   int pid, int mode);
const char * find_exec (const char *name, char *buf);

/* Strace facility.  See strace.cc and sys/strace.h. */
void strace_init (char *);

/* Heap management. */
#define HEAP_CHUNK_SIZE  (8 * 1024 * 1024)
void heap_init (void);
void malloc_init (void);

void hmap_init (void);
void uinfo_init (void);

/* For mmaps across fork(). */
extern "C" int recreate_mmaps_after_fork (void *);
extern "C" void set_child_mmap_ptr (pinfo *);

extern "C" void close_all_files (void);

#ifdef __cplusplus
extern "C" {
#endif
#define MIN(a,b) ((a)<(b) ? (a): (b))

/* FIXME: errno handling needs cleaning up.  */
extern "C" void seterrno (const char *, int line);
#define __seterrno() seterrno (__FILE__, __LINE__)
#undef errno
#define errno dont_use_this_since_were_in_a_shared library
#define set_errno(val) (_impure_ptr->_errno = (val))
#define get_errno()  (_impure_ptr->_errno)

#define NOT_OPEN_FD(fd) myself->hmap.not_open (fd)

#define alloca(x) __builtin_alloca (x)

#define STD_RBITS S_IRUSR | S_IRGRP | S_IROTH
#define STD_WBITS S_IWUSR
#define STD_XBITS S_IXUSR | S_IXGRP | S_IXOTH

#define O_NOSYMLINK 0x080000
#define O_DIROPEN   0x100000

#ifdef __cplusplus
}
#endif

void mark (const char *s, int i);
#define MARK() mark (__FILE__,__LINE__)

extern "C" int __small_sprintf (char *dst, const char *fmt, ...);
#if 0 /* Commented out because of va_list reference? */
extern "C" int __small_vsprintf (char *dst, const char *fmt, va_list ap);
#endif

void system_printf (const char *fmt, ...);
void small_printf (const char *fmt, ...);

void dll_crt0 (per_process *);
extern "C" int dll_dllcrt0 (HMODULE,per_process*);

extern "C" unsigned long hash_path_name (unsigned long hash, const char *name);

long totime_t (FILETIME * ptr);

/* Internal declarations */
void totimeval (struct timeval *dst, FILETIME * src, int sub, int flag);
long to_time_t (FILETIME * ptr);
int fhandler_make_pipe (int fildes[2]);

#if DEBUG_NEST_ON!=0
#define in(x) { debug_printf ("mark in %s:%d %s\n",__FILE__,__LINE__, x); d++;}
#define out(x) { d--; debug_printf ("mark out %s:%d %s\n",__FILE__,__LINE__,x);}
#else
#define in(x)
#define out(x)
#endif

void api_fatal (const char *);

void events_init (void);
void events_terminate (void);
int lock_pinfo_for_update (DWORD timeout);
void unlock_pinfo (void);
extern "C" void	do_exit (int) __attribute__ ((noreturn));

/* Process info for this process */
extern pinfo *myself;

/* Events/mutexes */
extern HANDLE pinfo_mutex;
extern HANDLE signal_arrived;
extern HANDLE title_mutex;

/* Retrieve a security descriptor that allows all access */
/* in shared.cc. */
SECURITY_DESCRIPTOR *get_null_sd (void);

int get_id_from_sid (PSID);

BOOL get_file_attribute (const char *, int *);
BOOL set_file_attribute (const char *, int);

int NTReadEA (const char *file, const char *attrname, char *buf, int len);
BOOL NTWriteEA (const char *file, const char *attrname, char *buf, int len);

HANDLE gethwnd (void);
void window_terminate (void);

char *cygname (char *, int);
void set_console_title (char *);

void fill_rusage (struct rusage *, HANDLE);
void add_rusage (struct rusage *, struct rusage *);

void environ_init (void);
char *winenv (const char * const *);
extern char **__cygwin_environ;

/* The title on program start */

extern char *old_title;
extern BOOL display_title;

enum os_type {winNT, win95, win32s, unknown};

extern "C" os_type get_os_type (void);

/* Globals that handle initialization of winsock in a child process. */
extern int number_of_sockets;
void winsock_init (void);
extern "C" int cygwin32_select (int , fd_set *, fd_set *, fd_set *,
		     struct timeval *to);

/* Should only be called internally from
   hinfo::de_linearize_fd_array() and hinfo_vec::find_unused_handle. */
extern "C" void setdtablesize (int);

/* these should be moved to global include files, but where? */
extern "C" void login (struct utmp *);
extern "C" int logout (char *);

#ifdef DEBUGGING
#define lock_pinfo_for_update(n) lpfu(__FUNCTION__, __LINE__, n)
int lpfu (char *, int, DWORD timeout);
#endif

/**************************** Exports ******************************/

extern "C" {
pid_t _execve (const char *path, const char *const argv[],
                                          const char *const envp[]);
void __main (void);
void __do_global_ctors (void);
void __do_global_dtors (void);
int _rename (const char *oldpath, const char *newpath);
int lstat (const char *name, struct stat *buf);
int access (const char *fn, int flags);
int _stat (const char *name, struct stat *buf);
int  chmod (const char *a, mode_t x);
int _unlink (const char *name);
pid_t _getpid (void);
pid_t  setsid (void);
time_t time (time_t * ptr);
int _fcntl (int fd, int cmd, ...);
int dup2 (int fd, int fd2);
int dup (int fd);
int pipe (int fildes[2]);
int setpgid (int f, int p);
int tcsetpgrp (int f, int p);
int tcgetpgrp (int f);
int tcgetattr (int fd, struct termios *t);
int sigaddset (sigset_t *, const int);
int sigemptyset (sigset_t *);
int gethostname (char *name, size_t len);
int tcsetattr (int fd, int actions, const struct termios *t);
int tcdrain (int fd);
int tcdrain (int fd);
int tcsendbreak (int fd, int duration);
int tcflow (int fd, int action);

int _link (const char *, const char *);
int vfork (void);
int _kill (int, int);
int kill_pgrp (pid_t, int);
int _raise (int sig);
pid_t cwait (int *status, pid_t intpid, int flags);
pid_t waitpid (pid_t intpid, int *status, int options);
pid_t _wait (int *status);
int tcflush (int fd, int queue);
int system (const char *);

unsigned int sleep (unsigned int seconds);
unsigned int usleep (unsigned int useconds);
unsigned int alarm (unsigned int seconds);

int _gettimeofday ();

int getdtablesize (void);

extern unsigned long int htonl (unsigned long int);
extern unsigned short int htons (unsigned short int);
};

