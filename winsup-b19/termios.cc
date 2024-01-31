/* termios.cc: termios for WIN32.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Written by Doug Evans and Steve Chamberlain of Cygnus Support
   dje@cygnus.com, sac@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/termios.h>
#include "winsup.h"

int
tcsendbreak (int fd, int duration)
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcsendbreak (duration);

  syscall_printf ("%d = tcsendbreak (%d, %d );\n", res, fd, duration);
  return res;
}

int
tcdrain (int fd)
{
  int res = -1;

  termios_printf ("tcdrain\n");
  
  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcdrain ();

  syscall_printf ("%d = tcdrain (%d);\n", res, fd);
  return res;
}

int
tcflush (int fd, int queue)
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcflush (queue);

  termios_printf ("%d = tcflush (%d, %d);\n", res, fd, queue);
  return res;
}

int
tcflow (int fd, int action)
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcflow (action);

  syscall_printf ("%d = tcflow (%d, %d);\n", res, fd, action);
  return res;
}

#if 0
static void
tdump (int)
{
  termios_printf ("fd %d rb %d wb %d len %d time %d\n",
		  fd,
		  myself->hmap[fd].r_binary,
		  myself->hmap[fd].w_binary,
		  myself->hmap[fd].vmin,
		  myself->hmap[fd].vtime);
}
#endif

#if 0
static void
ds (char *when, DCB *s)
{
  termios_printf ("DCB state %s\n", when);
  termios_printf ("DCBlength %x\n", s->DCBlength);
  termios_printf ("BaudRate;    %d\n", s->BaudRate);   
  termios_printf ("fBinary;  %d\n", s->fBinary);
  termios_printf ("fParity;   %d\n", s->fParity);
  termios_printf ("fOutxCtsFlow	%d\n", s->fOutxCtsFlow);
  termios_printf ("fOutxDsrFlow	%d\n", s->fOutxDsrFlow);
  termios_printf ("fDtrControl	 %d\n", s->fDtrControl);
  termios_printf ("fDsrSensitivity	%d\n", s->fDsrSensitivity);
  termios_printf ("fTXContinueOnXoff	%d\n", s->fTXContinueOnXoff);
  termios_printf ("1;      %d\n", s->fOutX);
  termios_printf ("1;       %d\n", s->fInX);
  termios_printf ("1; %d\n", s->fErrorChar);
  termios_printf ("1;      %d\n", s->fNull);
  termios_printf ("fRtsControl %d\n", s->fRtsControl);
  termios_printf ("fAbortOnError	 %d\n", s->fAbortOnError);
  termios_printf ("%d\n", s->fDummy2);
  termios_printf ("res1	%d\n", s->res1);
  termios_printf ("XonLim;          %d\n", s->XonLim);         
  termios_printf ("XoffLim;         %d\n", s->XoffLim);        
  termios_printf ("ByteSize;        %d\n", s->ByteSize);       
  termios_printf ("Parity;          %d\n", s->Parity);         
  termios_printf ("StopBits;        %d\n", s->StopBits);       
  termios_printf ("XonChar;         %d\n", s->XonChar);        
  termios_printf ("XoffChar;        %d\n", s->XoffChar);       
  termios_printf ("ErrorChar;       %d\n", s->ErrorChar);      
  termios_printf ("EofChar;         %d\n", s->EofChar);        
  termios_printf ("EvtChar;         %d\n", s->EvtChar);        
  termios_printf ("res2		%d\n", s->res2);
}
#endif

int
tcsetattr (int fd, int a, const struct termios *t)
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcsetattr (a, t);

  termios_printf ("iflag %x oflag %x cflag %x lflag %x\n",
	t->c_iflag, t->c_oflag, t->c_cflag, t->c_lflag);
  termios_printf ("%d = tcsetattr (%d, %d, %x);\n", res, fd, a, t);
  return res;
}

int
tcgetattr (int fd, struct termios *t)
{
  int res = -1;
  
  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcgetattr (t);

  termios_printf ("%d = tcgetattr (%d, %x);\n", res, fd, t);
  return res;
}

int
tcgetpgrp (int fd)
{
  int res = -1;
  
  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcgetpgrp ();

  termios_printf ("%d = tcgetpgrp (%d);\n", res, fd);
  return res;
}

int
tcsetpgrp (int fd, pid_t pgid)
{
  int res = -1;
  
  if (NOT_OPEN_FD (fd))
    set_errno (EBADF);
  else if (!myself->hmap[fd].h->is_tty ())
    set_errno (ENOTTY);
  else
    res = myself->hmap[fd].h->tcsetpgrp (pgid);

  termios_printf ("%d = tcsetpgrp (%d, %x);\n", res, fd, pgid);
  return res;
}

/* NIST PCTS requires not macro-only implementation */
#undef cfgetospeed
#undef cfgetispeed
#undef cfsetospeed
#undef cfsetispeed

extern "C"
speed_t
cfgetospeed (struct termios *tp)
{
  return tp->c_ospeed;
}

extern "C"
speed_t
cfgetispeed (struct termios *tp)
{
  return tp->c_ispeed;
}

extern "C"
int
cfsetospeed(struct termios *tp, speed_t s)
{
  tp->c_ospeed = s;
  return 0;
}

extern "C"
int
cfsetispeed(struct termios *tp, speed_t s)
{
  tp->c_ispeed = s;
  return 0;
}
