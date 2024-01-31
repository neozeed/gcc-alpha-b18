/* tty.h

   Copyright 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#ifndef _TTY_H
#define _TTY_H

#include <sys/termios.h>

#define INP_BUFFER_SIZE 256
#define OUT_BUFFER_SIZE 256
#define NTTYS		16

/* Input/Output/ioctl events */

#define OUTPUT_DONE_EVENT	"Cygwin.tty%d.output.done"
#define IOCTL_REQUEST_EVENT	"Cygwin.tty%d.ioctl.request"
#define IOCTL_DONE_EVENT	"Cygwin.tty%d.ioctl.done"
#define RESTART_OUTPUT_EVENT	"Cygwin.tty%d.output.restart"
#define OUTPUT_MUTEX		"Cygwin.tty%d.output.mutex"

class tty {
public:
  struct termios termios;
  struct winsize winsize;

  /* ioctl requests buffer */
  int cmd;
  union {
    struct termios termios;
    struct winsize winsize;
    int value;
    pid_t pid;
  } arg;
  /* XXX_retval variables holds master's completion codes. Error are stored as
   * -ERRNO
   */
  int ioctl_retval;

  int read_retval;

  BOOL OutputStopped;
  int write_retval;

  pid_t pgid;	/* Process group ID of tty */
  pid_t sid;	/* Session ID of tty */
  HWND  hwnd;	/* Console window handle tty belongs to */

  DWORD master_pid;	/* Win32 PID of tty master process */
  int slave_opened;
  HANDLE input_handle;	/* Real I/O handles of master tty */
  HANDLE output_handle;

  void init ();
  int getsid () {return sid;}
  void setsid (pid_t tsid) {sid = tsid;}
  pid_t getpgid () {return pgid;}
  void setpgid (pid_t gid) {pgid = gid;}
  HWND gethwnd () {return hwnd;}
  void sethwnd (HWND wnd) {hwnd = wnd;}
};

class tty_list {
  tty ttys[NTTYS];
  int volatile count[NTTYS]; /* How many times this tty opened */

public:
  int allocate_tty (int n); /* n non zero if allocate a tty, pty otherwice */
  int connect_tty (int);
  void free_tty (int);
  tty *gettty(int n) {return &ttys[n];}
  int getcount (int n) { return count[n]; }
  void terminate ();
  void init ();
};

void tty_init ();
void tty_terminate ();
int attach_tty (int);
void detach_tty (int);
void create_tty_master (int);
extern "C" ttyslot (void);

#endif /* _TTY_H */
