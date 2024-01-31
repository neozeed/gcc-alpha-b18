/* fhandler.h

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#ifndef _FHANDLER_H_
#define _FHANDLER_H_

/* Classes

  fhandler_base         normal I/O

     fhandler_dev_floppy
     fhandler_disk_file
     fhandler_socket 
     fhandler_pipe

     fhandler_tty_slave
     fhandler_pty_master
       fhandler_tty_master

     fhandler_tty       adds vmin and vtime. Not a good class name! Probably
			should be renamed to fhandler_serial?

       fhandler_console (out with ansi control)

  fhandler_dev_null     not really I/O

  fhandler_proc         interesting possibility, not implemented yet
*/

class fhandler_base
{
  int access_;
  HANDLE handle_;

  /* Set if in binary write mode.  */
  char w_binary_;

  /* Set if in binary read mode.  */
  char r_binary_;
  char close_exec_p_;		/* Non-zero if close-on-exec bit set.  */

  /* Used for crlf conversion in text files */
  char readahead_valid_;
  char readahead_;

  char append_p_; /* Set if always appending */
  char async_;    /* Non-zero if async I/O */

  int rpos_; /* Used in text reading */
  int rsize_; 

  char had_eof_;
  unsigned long namehash_;	 /* hashed filename, used as inode num */

  /* Full unix path name of this file */
  char *unix_path_name_;
  /* File open flags from open(void) and fcntl(void) calls */
  int openflags_;

  void set_name (const char *);

protected:

  char symlink_p_;
  /* Non-zero if this file looked like it would run (i.e. ends in .exe or .bat
     or begins with #!.  */
  char execable_p_;		

public:

  fhandler_base (const char *name = 0);
  ~fhandler_base(void);

  /* Non-virtual simple accessor functions. */
  void set_handle (HANDLE);

  int  get_access (void) { return access_; }
  void set_access (int x) { access_ = x; }

  int  get_async (void) { return async_; }
  void set_async (int x) { async_ = x; }
  int  get_flags (void) { return openflags_; }
  void set_flags (int x) { openflags_ = x; }

  int get_w_binary (void) { return w_binary_; }
  int get_r_binary (void) { return r_binary_; }

  void set_w_binary (int b) { w_binary_ = b; }
  void set_r_binary (int b) { r_binary_ = b; }

  void set_close_on_exec (char val) { close_exec_p_ = val; }
  char get_close_on_exec (void) { return close_exec_p_; }

  const char *get_name (void) { return unix_path_name_; }
  unsigned long get_namehash(void) { return namehash_; }

  /* Potentially overridden virtual functions. */
  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int close (void);
  virtual int fstat (struct stat *buf);
  virtual int ioctl (int cmd, void *);
  virtual char const * ttyname (void) { return get_name(); }
  virtual int read (void *ptr, size_t len);
  virtual int write (const void *ptr, size_t len);
  virtual off_t lseek (off_t offset, int whence);
  virtual int lock(int, struct flock *);
  virtual void dump (void);
  virtual int dup (fhandler_base *child);

  void *operator new (size_t, void *);

  virtual void init (HANDLE, int, int, const char *);

  virtual int tcflush (int);
  virtual int tcsendbreak (int);
  virtual int tcdrain (void);
  virtual int tcflow (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcsetpgrp (const pid_t pid);
  virtual int tcgetpgrp (void);
  virtual int is_tty (void) { return 0; }
  virtual char *ptsname (void) { return NULL;}
  virtual class fhandler_socket *is_socket (void) { return 0; }
  virtual class fhandler_console *is_console (void) { return 0; }

  virtual int raw_read (void *ptr, size_t ulen);
  virtual int raw_write (const void *ptr, size_t ulen);

  /* 1 if it's pointless (and broken) to select for read on the handle */
  virtual const int always_read_ready (void) { return 1; } ;
  /* 1 if it's pointless (and broken) to select for write on the handle */
  virtual const int always_write_ready (void) { return 1; } ;
  /* 1 if it's pointless (and broken) to select for except on the handle */
  virtual const int always_except_ready (void) { return 1; } ;

  /* Function to save state of a fhandler_base into memory. */
  virtual int linearize(unsigned char *);
  /* Function to de-linearize into a fd */
  virtual int de_linearize(const unsigned char *);

  /* Virtual accessor functions to hide the fact
     that some fd's have two handles. */
  virtual HANDLE get_handle (void) const { return handle_; }
  virtual HANDLE get_input_handle (void) const { return handle_; }
  virtual HANDLE get_output_handle (void) const { return handle_; }
  virtual void dup_for_fork (void) { return; }
};

class fhandler_socket: public fhandler_base
{
public:
  fhandler_socket (unsigned int, const char *name = 0);
  ~fhandler_socket (void);
  int get_socket (void) const { return (int) get_handle(); }
  fhandler_socket * is_socket (void) { return this; }
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int ioctl (int cmd, void *);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int fstat (struct stat *buf);
  virtual int close (void);

  virtual const int always_read_ready (void) { return 0; }
  virtual const int always_write_ready (void) { return 0; }
  virtual const int always_except_ready (void) { return 0; }
};

class fhandler_pipe: public fhandler_base
{
public:
  fhandler_pipe (const char *name = 0);
  virtual off_t lseek (off_t offset, int whence);

  virtual const int always_read_ready (void) { return 0; }
};

class fhandler_dev_floppy: public fhandler_base
{
public:
  fhandler_dev_floppy (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
};

class fhandler_dev_tape: public fhandler_base
{
public:
  fhandler_dev_tape (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
};

/* Standard disk file */

class fhandler_disk_file: public fhandler_base
{
private:
  int check_execable_p (const char *path);

public:
  fhandler_disk_file (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
  virtual int lock (int, struct flock *);
};

class fhandler_tty: public fhandler_base
{
private:
  unsigned int vmin_;			/* from termios */
  unsigned int vtime_;			/* from termios */
  pid_t pgrp_;

public:
  /* Constructor */
  fhandler_tty (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode);
  virtual int raw_read (void *ptr, size_t ulen);
  virtual int tcsendbreak (int);
  virtual int tcdrain (void);
  virtual int tcflow (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int tcflush (int);
  virtual void dump (void);
  virtual int is_tty (void) { return 1; }

  /* We maintain a pgrp so that tcsetpgrp and tcgetpgrp work, but we
     don't use it for permissions checking.  fhandler_tty_slave does
     permission checking on pgrps.  */
  virtual int tcgetpgrp (void) { return pgrp_; }
  virtual int tcsetpgrp (const pid_t pid) { pgrp_ = pid; return 0; }

  /* Function to save state of a fhandler_tty into memory. */
  virtual int linearize (unsigned char *);
  /* Function to de-linearize into a fd */
  virtual int de_linearize (const unsigned char *);
};

/* This is a input and output console handle */
class fhandler_console: public fhandler_tty
{
private:

/* Output state */

  // enum {normal, gotesc, gotsquare, gotarg1, gotcommand} state;
#define normal 1
#define gotesc 2
#define gotsquare 3
#define gotarg1 4
#define gotrsquare 5
#define gotcommand 6
#define gettitle 7
#define eattitle 8
#define MAXARGS 10
  int state_;
  int args_[MAXARGS];
  int nargs_;

/* Extra output handle */
  HANDLE output_handle_;
  DWORD default_color;

/* Output calls */

  BOOL fillin_info (void);
  void clear_screen (int, int, int, int);
  void scroll_screen (int, int, int, int, int, int);
  void cursor_set (BOOL, int, int);
  void cursor_get (int *, int *);
  void cursor_rel (int, int);
  void get_info (void);
  const unsigned char * write_normal (unsigned const char*, unsigned const char *);
  void char_command (char);
  int output_tcsetattr (int a, const struct termios *t);

/* Input state */
  /* Bits are..
     IGNCR  ignore carriage return on input - whether we nuke '\r's
     the default for this is set by wheter the file is opened
     in text or binary mode.

     INLCR  translate NL to CR on input

     IUCLC  map uppercase characters to lowercase on input
  */
  int iflag_;
  int lflag_;

/* Input calls */
  int igncr_enabled (void);
  int input_tcsetattr (int a, const struct termios *t);

public:
  fhandler_console (const char *name = 0);

  fhandler_console* is_console (void) { return this; }

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);

  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);

  virtual int tcflush (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);

  /* Special dup as we must dup two handles */
  virtual int dup (fhandler_base *child);

  virtual int ioctl (int cmd, void *);
  virtual void init (HANDLE, int, int, const char *);

  virtual const int always_read_ready (void) { return 0;}

  /* Function to save state of a fhandler_console_out into memory. */
  virtual int linearize (unsigned char *);
  /* Function to de-linearize into a fd */
  virtual int de_linearize (const unsigned char *);

  virtual HANDLE get_output_handle(void) const { return output_handle_; }
};

class fhandler_tty_slave: public fhandler_base
{
private:
  HANDLE output_done_event;	// Raised by master when tty's output buffer
				// written. Write status in tty::write_retval.
  HANDLE ioctl_request_event;	// Raised by slave to perform ioctl(void) request.
				// Ioctl(void) request in tty::cmd/arg.
  HANDLE ioctl_done_event;	// Raised by master when ioctl(void) request is done.
				// Ioctl(void) status in tty::ioctl_retval.
  HANDLE output_mutex;
  int ttynum;			// Master tty num.
/* Extra output handle */
  HANDLE output_handle_;
  void send_ioctl_request (void);
public:
  /* Constructor */
  fhandler_tty_slave (int, const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);
  virtual void init (HANDLE, int, int, const char *);

  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcsetpgrp (const pid_t pid);
  virtual int tcgetpgrp (void);
  virtual int tcflush (int);
  virtual int ioctl (int cmd, void *);

  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int is_tty (void) { return 1; }
  virtual const int always_read_ready (void) { return 0;}

  /* Function to save state of a fhandler_base into memory. */
  virtual int linearize(unsigned char *);
  /* Function to de-linearize into a fd */
  virtual int de_linearize (const unsigned char *);

  /* Special dup */
  virtual int dup (fhandler_base *child);
  virtual HANDLE get_output_handle(void) const { return output_handle_; }
  virtual void dup_for_fork (void);
};

class fhandler_pty_master: public fhandler_base
{
  int pktmode;			// non-zero if pty in a packet mode.
public:
  HANDLE output_done_event;	// Raised by master when tty's output buffer
				// written. Write status in tty::write_retval.
  HANDLE ioctl_request_event;	// Raised by slave to perform ioctl(void) request.
				// Ioctl(void) request in tty::cmd/arg.
  HANDLE ioctl_done_event;	// Raised by master when ioctl(void) request is done.
				// Ioctl(void) status in tty::ioctl_retval.
  HANDLE restart_output_event;
  HANDLE output_mutex;
  int ttynum;			// Master tty num.
  HANDLE output_handle_;	// Extra output handle.
  int neednl_;			// Next read should start with \n

  /* Constructor */
  fhandler_pty_master (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);

  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcflush (int);
  virtual int ioctl (int cmd, void *);

  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int is_tty (void) { return 1; }
  virtual char *ptsname (void);
  virtual const int always_read_ready (void) { return 0;}

  virtual HANDLE get_output_handle(void) const { return output_handle_; }
  /* Function to save state of a fhandler_base into memory. */
  virtual int linearize(unsigned char *);
  /* Function to de-linearize into a fd */
  virtual int de_linearize (const unsigned char *);
  virtual void dup_for_fork (void);
};


class fhandler_dev_null: public fhandler_base
{
public:
  fhandler_dev_null (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual void dump (void);
};

#if 0
/* You can't do this */
typedef union 
{
  fhandler_normal normal;
  fhandler_dev_null dev_null;
  fhandler bare;
  fhandler_tty tty;
} fhandler_union;
#else
#define fhandler_union fhandler_console
#endif

class fhandler_tty_master: public fhandler_pty_master
{
public:
  /* Constructor */
  fhandler_tty_master (const char *name = 0);
  fhandler_base *f;		// device handler to perform real i/o.
  char item[sizeof(fhandler_union)];	
  HANDLE hThread;		// process_output thread handle.

  virtual int init (int);
};


uid_t get_file_owner (char *);
gid_t get_file_group (char *);

#endif /* _FHANDLER_H_ */
