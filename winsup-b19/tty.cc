/* tty.cc

   Copyright 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <utmp.h>

static NO_COPY fhandler_tty_master master;

void
tty_init (void)
{
  if (NOTSTATE(myself, PID_USETTY))
    return;
  if (myself->ctty == -1)
    if (NOTSTATE(myself, PID_CYGPARENT))
      myself->ctty = attach_tty (myself->ctty);
    else
      return;
  if (myself->ctty == -1)
    termios_printf ("Can't attach to tty\n");
}

void
tty_terminate (void)
{
  if (NOTSTATE(myself, PID_USETTY))
    return;
  s->t.terminate ();
}

int
attach_tty (int num)
{
  if (num != -1)
    {
      return s->t.connect_tty (num);
    }
  if (NOTSTATE(myself, PID_USETTY))
    return -1;
  return s->t.allocate_tty (1);
}

void
detach_tty (int num)
{
  s->t.free_tty (num);
}

extern "C"
int
ttyslot (void)
{
  if (NOTSTATE(myself, PID_USETTY))
    return -1;
  return myself->ctty;
}

void
tty::init (void)
{
  OutputStopped = 0;
  sid = 0;
  pgid = 0;
  hwnd = NULL;
  input_handle = INVALID_HANDLE_VALUE;
  output_handle = INVALID_HANDLE_VALUE;
}

void
tty_list::terminate (void)
{
  int ttynum = myself->ctty;

  /* Keep master running till there are connected clients */
  if (ttynum != -1 && ttys[ttynum].master_pid == GetCurrentProcessId ())
    {
      do
        Sleep (200);
      while (count[ttynum] > 1);
      termios_printf ("tty %d master about to finish\n", ttynum);
      CloseHandle (ttys[ttynum].input_handle);
      CloseHandle (ttys[ttynum].output_handle);
      WaitForSingleObject (master.hThread, INFINITE);
      ttys[ttynum].init ();
      count[ttynum] = 0;

      char buf[20];
      sprintf (buf, "tty%d", ttynum);
      logout (buf);
    }
}

int
tty_list::connect_tty (int ttynum)
{
  if (ttynum < 0 || ttynum >= NTTYS)
    {
      termios_printf ("ttynum (%d) out of range\n", ttynum);
      return -1;
    }
  if (ttys[ttynum].getsid () == 0)
    {
      termios_printf ("tty %d was not allocated\n", ttynum);
      return -1;
    }
  int total;

  total = InterlockedIncrement ((LPLONG) &count[ttynum]);
  termios_printf ("tty %d allocated %d times\n", ttynum, count[ttynum]);
  return ttynum;
}

void
tty_list::free_tty (int ttynum)
{
  if (ttynum < 0 || ttynum >= NTTYS)
    {
      termios_printf ("ttynum (%d) out of range\n", ttynum);
      return;
    }

  int total;
  total = InterlockedDecrement ((LPLONG) &count[ttynum]);
  if (total < 0)
    small_printf ("free_tty: count < 0\n");
  if (total == 0)
    {
      if (ttys[ttynum].input_handle != INVALID_HANDLE_VALUE)
	CloseHandle (ttys[ttynum].input_handle);
      if (ttys[ttynum].output_handle != INVALID_HANDLE_VALUE)
	CloseHandle (ttys[ttynum].output_handle);
      ttys[ttynum].init ();
    }
  termios_printf ("tty %d allocated %d times\n", ttynum, count[ttynum]);
}

void
tty_list::init (void)
{
  for (int i = 0; i < NTTYS; i++)
    {
      ttys[i].init ();
      count[i] = 0;
    }
}

/* Search for tty class for our console. Allocate new tty if our process is
   the only cygwin process in the current console.
   Return tty number or -1 if error.
   If flag == 0, just find a free tty.
 */
int
tty_list::allocate_tty (int flag)
{
  HWND console;

  if (flag)
    {
      char *oldtitle = new char [TITLESIZE];

      if (!oldtitle)
        {
          termios_printf ("Can't *allocate console title buffer\n");
          return -1;
        }
      if (!GetConsoleTitle (oldtitle, TITLESIZE))
        {
          termios_printf ("Can't read console title\n");
          return -1;
        }

      if (WaitForSingleObject (title_mutex, INFINITE) == WAIT_FAILED)
        {
          termios_printf ("WFSO failed (error %d)\n", GetLastError());
        }

      char buf[40];

      sprintf (buf, "Cygwin.find.console.%d", myself->pid);
      SetConsoleTitle (buf);
      Sleep (40);
      console = FindWindow (NULL, buf);
      SetConsoleTitle (oldtitle);
      Sleep (40);
      ReleaseMutex (title_mutex);
      if (console == NULL)
        {
          termios_printf ("Can't find console window\n");
          return -1;
        }
    }
  else
    console = NULL;
  /* Is a tty allocated for console? */

  int freetty = -1;
  for (int i = 0; i < NTTYS; i++)
    {
      if (ttys[i].getsid () == 0) /* unused tty */
	{
	  if (freetty == -1)
	    freetty = i;
	  if (flag == 0)
	    break;
	}
      if (flag && ttys[i].gethwnd () == console)
	{
	  termios_printf ("console %x already associated with tty%d\n",
		console, i);
	  /* Is the master alive? */
          HANDLE hMaster;
	  hMaster = OpenProcess (PROCESS_DUP_HANDLE, FALSE, ttys[i].master_pid);
	  if (hMaster)
	    {
	      CloseHandle (hMaster);
	      return i;
	    }
	  /* Master is dead */
	  freetty = i;
	  break;
	}
    }

  /* There is no tty allocated to console, allocate the first free found */
  if (freetty == -1)
    {
      small_printf ("allocate_tty: No free tty available!\n");
      return -1;
    }
  count[freetty] = 1;
  ttys[freetty].init ();
  ttys[freetty].setsid (myself->sid);
  ttys[freetty].setpgid (myself->pgid);
  ttys[freetty].sethwnd (console);
  if (flag)
    {
      termios_printf ("console %x associated with tty%d\n", console, freetty);
      create_tty_master (freetty);
    }
  else
    termios_printf ("tty%d allocated\n", freetty);
  return freetty;
}

/**********************************************************************/
/* Tty master stuff */

DWORD process_input (void *);		// Input queue thread
DWORD process_output (void *);		// Output queue thread
DWORD process_ioctl (void *);		// Ioctl requests thread

fhandler_tty_master::fhandler_tty_master (const char *name) : fhandler_pty_master (name)
{
  termios_printf ("constructor called\n");
}

/* Create session's master tty */

void
create_tty_master (int ttynum)
{
  /* Global constuctors are not called within a dll. So, make a trick... */
  fhandler_tty_master dummy ("master");
  master = dummy;

  if (master.init (ttynum))
    api_fatal ("Can't create master tty");
  else
    {
      /* Log utmp entry */
      struct utmp utmp;

      bzero((char *)&utmp, sizeof(utmp));
      (void)time(&utmp.ut_time);
      strncpy(utmp.ut_name, getlogin (), sizeof(utmp.ut_name));
      strncpy(utmp.ut_host, "local", sizeof(utmp.ut_host));
      sprintf(utmp.ut_line, "tty%d", ttynum);
      utmp.ut_type = USER_PROCESS;
      myself->ctty = ttynum;
      login(&utmp);
    }
}

/* Initialise master tty */

fhandler_tty_master::init (int ttynum)
{
  tty *ttyp = s->t.gettty (ttynum);

  termios_printf ("Creating master for tty%d\n", ttynum);
  this->ttynum = ttynum;

  /* Redirection of stderr almost never occured in Win32 world. So stderr is
   * connected to our physical device
   */ 
  HANDLE err = GetStdHandle (STD_ERROR_HANDLE);

  if (err == INVALID_HANDLE_VALUE)
    {
      termios_printf ("can't get stderr handle\n");
      return -1;
    }
  f = myself->hmap.build_fhandler ("master", 0, err);
  if (f == NULL)
    {
      termios_printf ("can't create fhandler\n");
      return -1;
    }
  /* copy fd[0] item to local area and point f to it. Tricky... */

  f = (fhandler_base *)&item;
  memcpy (&item, myself->hmap.vec[0].h,  sizeof (item));

  f->init (err, 1, GENERIC_READ | GENERIC_WRITE, "master");

  /* Create communication pipes */

  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.bInheritHandle = 0;
  sa.lpSecurityDescriptor = get_null_sd();

  HANDLE handle;
  if (CreatePipe (&ttyp->input_handle, &handle, &sa, 0) == FALSE)
    {
      termios_printf ("can't create input pipe\n");
      return -1;
    }
  output_handle_ = handle;
  if (CreatePipe (&handle, &ttyp->output_handle, &sa, 0) == FALSE)
    {
      termios_printf ("can't create output pipe\n");
      return -1;
    }
  set_handle (handle);

  neednl_ = 0;

  /* Save our pid  */

  ttyp->master_pid = GetCurrentProcessId ();
  ttyp->slave_opened = 0;

  /* Allow the others to open us (for handle duplication) */

  handle = GetCurrentProcess();
  if (get_os_type () == winNT && 
      SetKernelObjectSecurity(handle, DACL_SECURITY_INFORMATION, get_null_sd ()) == FALSE)
    small_printf ("Can't set process security %u\n", GetLastError ());

  /* Create synchronisation events */
  char buf[40];

  sprintf (buf, OUTPUT_DONE_EVENT, ttynum);
  output_done_event = CreateEvent (&sa, FALSE, FALSE, buf);
  sprintf (buf, IOCTL_REQUEST_EVENT, ttynum);
  ioctl_request_event = CreateEvent (&sa, FALSE, FALSE, buf);
  sprintf (buf, IOCTL_DONE_EVENT, ttynum);
  ioctl_done_event = CreateEvent (&sa, FALSE, FALSE, buf);
  sprintf (buf, RESTART_OUTPUT_EVENT, ttynum);
  restart_output_event = CreateEvent (NULL, FALSE, FALSE, buf);
  sprintf (buf, OUTPUT_MUTEX, ttynum);
  output_mutex = CreateMutex (&sa, FALSE, buf);
  if (output_done_event == NULL || ioctl_done_event == NULL ||
      restart_output_event == NULL || output_mutex == NULL ||
      ioctl_request_event == NULL)
    {
      termios_printf ("can't create events\n");
      return -1;
    }

  /* Initial termios values */

  ttyp->termios.c_iflag = BRKINT | ICRNL | IXON;
  ttyp->termios.c_oflag = OPOST | ONLCR;
  ttyp->termios.c_cflag = B9600 | CS8 | CREAD;
  ttyp->termios.c_lflag = ISIG | ICANON | ECHO | IEXTEN;
  ttyp->termios.c_cc[VDISCARD]	= CFLUSH;
  ttyp->termios.c_cc[VEOL]	= CEOL;
  ttyp->termios.c_cc[VEOL2]	= CEOL2;
  ttyp->termios.c_cc[VEOF]	= CEOF;
  ttyp->termios.c_cc[VERASE]	= CERASE;
  ttyp->termios.c_cc[VINTR]	= CINTR;
  ttyp->termios.c_cc[VKILL]	= CKILL;
  ttyp->termios.c_cc[VLNEXT]	= CLNEXT;
  ttyp->termios.c_cc[VMIN]	= 1;
  ttyp->termios.c_cc[VQUIT]	= CQUIT;
  ttyp->termios.c_cc[VREPRINT]	= CRPRNT;
  ttyp->termios.c_cc[VSTART]	= CSTART;
  ttyp->termios.c_cc[VSTOP]	= CSTOP;
  ttyp->termios.c_cc[VSUSP]	= CSUSP;
  ttyp->termios.c_cc[VSWTC]	= CSWTCH;
  ttyp->termios.c_cc[VTIME]	= 0;
  ttyp->termios.c_cc[VWERASE]	= CWERASE;

  cfsetispeed (&ttyp->termios, B38400);
  cfsetospeed (&ttyp->termios, B38400);

  ttyp->winsize.ws_col = 80;
  ttyp->winsize.ws_row = 25;

  /* Create input and output threads */
  DWORD tid;

  hThread = CreateThread (NULL, 0, process_input, (void *) 0, 0, &tid);
  if (hThread == NULL)
    {
      termios_printf ("can't create input thread\n");
      return -1;
    }
  else
    {
      SetThreadPriority (hThread, THREAD_PRIORITY_HIGHEST);
      CloseHandle (hThread);
    }

  hThread = CreateThread (NULL, 0, process_ioctl, (void *) 0, 0, &tid);
  if (hThread == NULL)
    {
      termios_printf ("can't create ioctl thread\n");
      return -1;
    }
  else
    {
      SetThreadPriority (hThread, THREAD_PRIORITY_HIGHEST);
      CloseHandle (hThread);
    }

  hThread = CreateThread (NULL, 0, process_output, (void *) 0, 0, &tid);
  if (hThread == NULL)
    {
      termios_printf ("can't create output thread\n");
      return -1;
    }
  else
    {
      SetThreadPriority (hThread, THREAD_PRIORITY_HIGHEST);
    }

  return 0;
}

/* Process tty input. */

void doecho (fhandler_pty_master *m, const void *str, unsigned len)
{
  tty *ttyp = s->t.gettty (m->ttynum);

  WaitForSingleObject (m->output_mutex, INFINITE);
  WriteFile (ttyp->output_handle, str, len, &len, NULL);
//  WaitForSingleObject (m->output_done_event, INFINITE);
  ReleaseMutex (m->output_mutex);
}

int
do_input (fhandler_pty_master *m, const char *rptr, int nraw)
{
  static NO_COPY char buf[INP_BUFFER_SIZE];
  static NO_COPY char *bptr = buf;
  unsigned int n, written;
  tty *ttyp = s->t.gettty (m->ttynum);
  char c;
  int eol = 0;
  int towrite = nraw;

  while (nraw > 0)
    {
      c = *rptr++;
      nraw--;

      termios_printf ("char %c\n", c);

      /* Check for special chars */

      if (c == '\024' && strace() & _STRACE_CACHE)
	{
	  sig_send(NULL, __SIGSTRACE);
	  continue;
	}
      if (c == '\r')
        {
	  if (ttyp->termios.c_iflag & IGNCR)
	    continue;
	  if (ttyp->termios.c_iflag & ICRNL)
	    c = '\n';
	  ++eol;
	}
      else if (c == '\n' && (ttyp->termios.c_iflag & INLCR))
	{
	  c = '\r';
	  ++eol;
	}

      if (ttyp->termios.c_iflag & ISTRIP)
	c &= 0x7f;
      if (ttyp->termios.c_lflag & ISIG)
	{
	  if (c == ttyp->termios.c_cc[VINTR] ||	// interrupt chars
	      c == ttyp->termios.c_cc[VQUIT] ||
	      c == ttyp->termios.c_cc[VSUSP])
	    {
	      _kill (-ttyp->getpgid (), c == CINTR? SIGINT:
				       (c == CQUIT? SIGQUIT: SIGTSTP));
	      ttyp->termios.c_lflag &= ~FLUSHO;
	      goto restart_output;
	    }
	}
      if (ttyp->termios.c_iflag & IXON)
	{
	  if (c == ttyp->termios.c_cc[VSTOP])
	    {
	      ttyp->OutputStopped++;
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VSTART])
	    {
restart_output:
	      ttyp->OutputStopped = 0;
	      SetEvent (m->restart_output_event);
	      continue;
	    }
	  else if ((ttyp->termios.c_iflag & IXANY) && ttyp->OutputStopped)
	    goto restart_output;
	}
      if (ttyp->termios.c_lflag & IEXTEN)
	{
	  if (c == ttyp->termios.c_cc[VDISCARD])
	    {
	      ttyp->termios.c_lflag ^= FLUSHO;
	      continue;
	    }
	}
      if (ttyp->termios.c_lflag & ICANON)
	{
	  if (c == ttyp->termios.c_cc[VERASE])
	    {
	      if (bptr > buf)
	        {
	          bptr--;
		  doecho (m, "\b \b", 3);
		}
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VWERASE])
	    {
	      while (bptr > buf)
		if (isspace (bptr[-1]))
		  break;
		else
		  {
		    bptr--;
		    doecho (m, "\b \b", 3);
		  }
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VKILL])
	    {
	      while (bptr > buf)
		{
		  bptr--;
		  doecho (m, "\b \b", 3);
		}
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VREPRINT])
	    {
	      doecho (m, "\n\r", 2);
	      doecho (m, buf, bptr-buf);
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VEOF])
	    {
	      termios_printf ("EOF\n");
              n = ttyp->read_retval = bptr - buf;
              termios_printf ("about to write %d chars to inbuf\n", n);
              WriteFile (m->get_output_handle (), (unsigned *) buf, n? n: 1, &written, NULL);
	      if (n)
		{
		  Sleep (10);
                  ttyp->read_retval = 0;
                  WriteFile (m->get_output_handle (), (unsigned *) buf, 1, &written, NULL);
		}
	      continue;
	    }
	  else if (c == ttyp->termios.c_cc[VEOL] ||
		   c == ttyp->termios.c_cc[VEOL2] ||
		   c == '\n')
	    {
	      eol++;
	      termios_printf ("EOL\n");
	    }
	}
      if (ttyp->termios.c_lflag & ECHO)
	{
	  doecho (m, &c, 1);
	}
      *bptr++ = c;
      if ((ttyp->termios.c_lflag & ICANON) && !eol)
	continue;

      n = ttyp->read_retval = bptr - buf;
      termios_printf ("about to write %d chars to inbuf\n", n);
      if (WriteFile (m->get_output_handle (), (unsigned *) buf, n, &written,
		     NULL) == FALSE)
	return -1;
      bptr = buf;
    }

  /* FIXME: This does not handle incomplete lines correctly.  The data
     is lost without ever being written anywhere.  */

  if (nraw == -1)
    {
      ttyp->read_retval = -get_errno ();
      WriteFile (m->get_output_handle (), (unsigned *) buf, 1, &written, NULL);
    }
  return towrite;
}

DWORD
process_input (void *arg)
{
  char rawbuf[INP_BUFFER_SIZE];
  int nraw;

  while (1)
    {
      nraw = master.f->read ((void *) rawbuf, (size_t) INP_BUFFER_SIZE);
      do_input ((fhandler_pty_master *) &master, rawbuf, nraw);
    }
}

/* Process tty output requests */

int
do_output (fhandler_pty_master *m, char *buf, size_t len)
{
  size_t rlen;
  char outbuf[OUT_BUFFER_SIZE];
  unsigned int n;
  int column = 0;
  tty *ttyp = s->t.gettty (m->ttynum);

again:

  if (len == 0)
    return 0;

  if (m->neednl_)
    {
      /* We need to return a left over \n character, resulting from
         \r\n conversion.  Note that we already checked for FLUSHO and
         OutputStopped at the time that we read the character, so we
         don't check again here.  */
      buf[0] = '\n';
      m->neednl_ = 0;
      return 1;
    }

  /* Set RLEN to the number of bytes to read from the pipe.  */
  rlen = len;
  if ((ttyp->termios.c_oflag & OPOST) != 0
      && (ttyp->termios.c_oflag & ONLCR) != 0)
    {
      /* We are going to expand \n to \r\n, so don't read more than
         half of the number of bytes requested.  */
      rlen /= 2;
      if (rlen == 0)
	rlen = 1;
    }
  if (rlen > sizeof outbuf)
    rlen = sizeof outbuf;

  HANDLE handle = m->get_input_handle ();

  /* Doing a busy wait like this is quite inefficient, but nothing
     else seems to work completely.  Windows should provide some sort
     of overlapped I/O for pipes, or something, but it doesn't.  */
  DWORD avail;
  while (1)
    {
      if (! PeekNamedPipe (handle, NULL, 0, NULL, &avail, NULL))
	{
	  if (GetLastError () == ERROR_BROKEN_PIPE)
	    return 0;
	  __seterrno ();
	  return -1;
	}
      termios_printf ("%u available; %d handles; slave %sopened\n",
		      (int) avail, s->t.getcount (m->ttynum),
		      ttyp->slave_opened ? "" : "not ");
      if (avail > 0)
	break;
      if (s->t.getcount (m->ttynum) == 1 && ttyp->slave_opened)
	{
	  /* We have the only remaining open handle to this pty, and
             the slave pty has been opened at least once.  We treat
             this as EOF.  */
	  termios_printf ("all other handles closed\n");
	  return 0;
	}
      termios_printf ("sleeping waiting for data\n");
      Sleep (10);
    }

  if (ReadFile (handle, outbuf, rlen, &n, NULL) == FALSE)
    {
      if (GetLastError () == ERROR_BROKEN_PIPE)
	return 0;
      __seterrno ();
      return -1;
    }

  termios_printf ("len=%u\n", n);

  if (ttyp->termios.c_lflag & FLUSHO)
    {
      ttyp->write_retval = n;
      if (m->output_done_event != NULL)
	SetEvent (m->output_done_event);
      goto again;
    }
  if (ttyp->OutputStopped)
    {
      WaitForSingleObject (m->restart_output_event, INFINITE);
    }
  if (ttyp->termios.c_oflag & OPOST)	// post-process output
    {
      char *iptr = outbuf, *optr = buf;

      while (n--)
	{
	  switch (*iptr)
	    {
	    case '\r':
	      if ((ttyp->termios.c_oflag & ONOCR) && column == 0)
	        {
		  iptr++;
		  continue;
		}
	      if (ttyp->termios.c_oflag & OCRNL)
		*iptr = '\n';
	      else
		column = 0;
	      break;
	    case '\n':
	      if (ttyp->termios.c_oflag & ONLCR)
		{
		  *optr++ = '\r';
		  column = 0;
		}
	      if (ttyp->termios.c_oflag & ONLRET)
		column = 0;
	      break;
	    default:
	      column++;
	      break;
	    }

	  /* Don't store data past the end of the user's buffer.  This
             can happen if the user requests a read of 1 byte when
             doing \r\n expansion.  */
	  if (optr - buf >= len)
	    {
	      m->neednl_ = 1;
	      if (*iptr != '\n' || n != 0)
		system_printf ("tty: do_output: internal error: %d unexpected characters\n",
			       n);
	      break;
	    }

	  *optr++ = *iptr++;
	}
      return optr - buf;
    }
  else					// raw output mode
    {
      memcpy (buf, outbuf, n);
      return n;
    }
}

DWORD
process_output (void *arg)
{
  char buf[OUT_BUFFER_SIZE*2];
  int n;
  tty *ttyp = s->t.gettty (master.ttynum);

  while (1)
    {
      n = do_output ((fhandler_pty_master *) &master, buf, OUT_BUFFER_SIZE);
      if (n < 0)
	{
          termios_printf ("ReadFile error %d\n", GetLastError ());
          ExitThread (0);
	}
      if (n == 0)
	{
	  /* End of file.  */
	  ExitThread (0);
	}
      n = master.f->write ((void *) buf, (size_t) n);
      ttyp->write_retval = n == -1? -get_errno (): n;
      SetEvent (master.output_done_event);
    }
}


/* Process tty ioctl requests */

DWORD
process_ioctl (void *arg)
{
  tty *ttyp = s->t.gettty (master.ttynum);

  while (1)
    {
      WaitForSingleObject (master.ioctl_request_event, INFINITE);
      termios_printf ("ioctl() request\n");
      ttyp->ioctl_retval = master.f->ioctl (ttyp->cmd, (void *) &ttyp->arg);
      SetEvent (master.ioctl_done_event);
    }
}

/**********************************************************************/
/* Tty slave stuff */

fhandler_tty_slave::fhandler_tty_slave(int num, const char *name)
 : fhandler_base (name)
{
  ttynum = num;
}

fhandler_base *
fhandler_tty_slave::open (const char *name, int flags, mode_t)
{
  tty *ttyp = s->t.gettty (ttynum);

  if (myself->ctty == -1 && !(flags & O_NOCTTY))
    {
      myself->ctty = ttynum;
      if (myself->sid == myself->pid)
	{
	  /* We are the session leader */
	  ttyp->setsid (myself->sid);
	  ttyp->setpgid (myself->pgid);
	}
      else
        myself->sid = ttyp->getsid ();
      if (ttyp->getpgid () == 0)
        ttyp->setpgid (myself->pgid);
    }
  attach_tty (ttynum);

  set_flags (flags);
  /* Create synchronisation events */
  char buf[40];
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.bInheritHandle = 1;
  sa.lpSecurityDescriptor = get_null_sd();

  /* output_done_event may or may not exist.  It will exist if the tty
     was opened by fhandler_tty_master::init, normally called at
     startup if use_tty is non-zero.  It will not exist if this is a
     pty opened by fhandler_pty_master::open.  In the former case, tty
     output is handled by a separate thread which controls output.  */
  sprintf (buf, OUTPUT_DONE_EVENT, ttynum);
  output_done_event = OpenEvent (EVENT_ALL_ACCESS, TRUE, buf);

  sprintf (buf, OUTPUT_MUTEX, ttynum);
  output_mutex = CreateMutex (&sa, FALSE, buf);
  if (output_mutex == NULL)
    {
      termios_printf ("open output mutex failed: %d\n", GetLastError ());
      __seterrno ();
      detach_tty (ttynum);
      return 0;
    }

  /* The ioctl events may or may not exist.  See output_done_event,
     above.  */
  sprintf (buf, IOCTL_REQUEST_EVENT, ttynum);
  ioctl_request_event = OpenEvent (EVENT_ALL_ACCESS, TRUE, buf);
  sprintf (buf, IOCTL_DONE_EVENT, ttynum);
  ioctl_done_event = OpenEvent (EVENT_ALL_ACCESS, TRUE, buf);

  /* Duplicate tty handles.  */

  if (ttyp->input_handle == INVALID_HANDLE_VALUE
      || ttyp->output_handle == INVALID_HANDLE_VALUE)
    {
      termios_printf ("tty handles have been closed\n");
      set_errno (EACCES);
      detach_tty (ttynum);
      return 0;
    }

  HANDLE handle_owner = OpenProcess (PROCESS_DUP_HANDLE, FALSE,
				     ttyp->master_pid);
  if (handle_owner == NULL)
    {
      termios_printf ("can't open tty handle process\n");
      __seterrno ();
      detach_tty (ttynum);
      return 0;
    }

  HANDLE nh;
  if (!DuplicateHandle (handle_owner, ttyp->input_handle,
			GetCurrentProcess (), &nh, 0, TRUE,
			DUPLICATE_SAME_ACCESS))
    {
      termios_printf ("can't duplicate input (%d)\n", GetLastError ());
      __seterrno ();
      detach_tty (ttynum);
      return 0;
    }
  set_handle (nh);
  if (!DuplicateHandle (handle_owner, ttyp->output_handle,
			GetCurrentProcess (), &output_handle_, 0, TRUE,
			DUPLICATE_SAME_ACCESS))
    {
      termios_printf ("can't duplicate output (%d)\n", GetLastError ());
      __seterrno ();
      detach_tty (ttynum);
      return 0;
    }
  CloseHandle (handle_owner);

  ttyp->slave_opened = 1;

  termios_printf("tty%d opened\n", ttynum);

  return this;
}

void                                                             
fhandler_tty_slave::init (HANDLE f, int bin, int a, const char *n) 
{                 
  int mode;
                                               
  a &= GENERIC_READ | GENERIC_WRITE;
  if (a == GENERIC_READ)
    mode = O_RDONLY;
  if (a == GENERIC_WRITE)
    mode = O_WRONLY;
  if (a == (GENERIC_READ | GENERIC_WRITE))
    mode = O_RDWR;
  open (0, mode);                                                    
}                                                                

int
fhandler_tty_slave::close (void)
{
  if (output_done_event)
    {
      if (! CloseHandle (output_done_event))
	termios_printf ("CloseHandle 1 failed (%d)\n", GetLastError ());
    }
  if (ioctl_done_event)
    {
      if (! CloseHandle (ioctl_done_event))
	termios_printf ("CloseHandle 2 failed (%d)\n", GetLastError ());
    }
  if (ioctl_request_event)
    {
      if (! CloseHandle (ioctl_request_event))
	termios_printf ("CloseHandle 3 failed (%d)\n", GetLastError ());
    }
  if (! CloseHandle (output_mutex))
    termios_printf ("CloseHandle 4 failed (%d)\n", GetLastError ());
  if (! CloseHandle (get_handle ()))
    termios_printf ("CloseHandle 5 failed (%d)\n", GetLastError ());
  if (! CloseHandle (output_handle_))
    termios_printf ("CloseHandle 6 failed (%d)\n", GetLastError ());

  tty *ttyp = s->t.gettty (ttynum);
  detach_tty (ttynum);

  termios_printf ("tty%d closed\n", ttynum);

  return 0;
}

int
fhandler_tty_slave::write (const void *ptr, size_t len)
{
  unsigned int towrite=len, n;
  char buf[OUT_BUFFER_SIZE];
  tty *ttyp = s->t.gettty (ttynum);
  sigset_t mask = ~0, oldmask;

  termios_printf("tty%d, write(%x, %d)\n", ttynum, ptr, len);

  if (myself->pgid && ttyp->getpgid () != myself->pgid &&
	myself->ctty == ttynum && (ttyp->termios.c_lflag & TOSTOP))
    {
      /* background process */
      termios_printf("bg write pgid=%d tpgid=%d ctty=%d\n", 
			myself->pgid, ttyp->getpgid (), myself->ctty);
      if (ttyp->termios.c_lflag & TOSTOP)
        _raise (SIGTTOU);
    }
  WaitForSingleObject (output_mutex, INFINITE);
  while (len)
    {
      n = min (OUT_BUFFER_SIZE, len);
      memcpy (buf, ptr, n);
      ptr = (char *) ptr + n;
      len -= n;

      if (output_done_event != NULL)
	{
	  termios_printf("write - waiting for output_done\n", ttynum);
	  sigprocmask (SIG_SETMASK, &mask, &oldmask);
	}

      if (WriteFile (output_handle_, buf, n, &n, NULL) == FALSE)
        {
	  termios_printf ("WriteFile failed (%d)\n", GetLastError ());
          ReleaseMutex (output_mutex);
          sigprocmask (SIG_SETMASK, &oldmask, NULL);
	  _raise (SIGHUP);
          return 0;
        }

      if (output_done_event != NULL)
	{
	  WaitForSingleObject (output_done_event, INFINITE);
	  sigprocmask (SIG_SETMASK, &oldmask, NULL);
	}

      if (ttyp->write_retval < 0)
	{
	  set_errno (-ttyp->write_retval);
	  ReleaseMutex (output_mutex);
	  return -1;
	}
    }
  ReleaseMutex (output_mutex);
  return towrite;
}

int
fhandler_tty_slave::read (void *ptr, size_t len)
{
  unsigned int n;
  int totalread = 0;
  int vmin = INT_MAX, vtime;
  char buf[INP_BUFFER_SIZE];
  tty *ttyp = s->t.gettty (ttynum);

  termios_printf("read(%x, %d) handle %d\n", ptr, len, get_handle ());

  if (myself->pgid && ttyp->getpgid () != myself->pgid &&
	myself->ctty == ttynum) // background process
    {
      termios_printf("bg read pgid=%d tpgid=%d ctty=%d\n",
			myself->pgid, ttyp->getpgid (), myself->ctty);

      if (ttyp->getsid () == 0)
	{
	  /* The pty has been closed by the master.  Return an EOF
             indication.  FIXME: There is nothing to stop somebody
             from reallocating this pty.  I think this is the case
             which is handled by unlockpt on a Unix system.  */
	  return 0;
	}

      /* if process is ignoring or blocks SIGTTIN, return with error */
      if ((void *)myself->sigs[SIGTTIN].sa_handler == (void *)SIG_IGN ||
	  (myself->sig_mask & (1<<SIGTTIN)))
	{
	  set_errno (EIO);
	  return -1;
	}
      _raise (SIGTTIN);
    }

  if (!(ttyp->termios.c_lflag & ICANON))
    {
      vmin = ttyp->termios.c_cc[VMIN];
      vtime = ttyp->termios.c_cc[VTIME];
    }
  while (len)
    {
      if (PeekNamedPipe (get_handle (), NULL, 0, NULL, &n, NULL) == FALSE)
	{
	  termios_printf("PeekNamedPipe failed %d\n", GetLastError ());
	  return 0;
	  continue;
	}
      if (n == 0)
        {
	  if (get_flags () & (O_NONBLOCK | O_NDELAY))
	    {
	      if (totalread)
		goto done;
	      set_errno (EAGAIN);
	      return -1;
	    }
	  /* We can't enter to blocking Readfile - signals will be lost!
	   * So, poll the pipe for data.
	   * FIXME: try to avoid polling...
	   */
	  if (ttyp->termios.c_lflag & ICANON)
wait:	    while (PeekNamedPipe (get_handle (), NULL, 0, NULL, &n, NULL) && !n)
	      Sleep(10);
	  else		// non-canonical mode
	    {
	      termios_printf("vmin %d vtime %d\n", vmin, vtime);
	      if (vmin == 0 && vtime == 0)
		return 0;   	// min = 0, time = 0
	      if (vtime == 0)
	        goto wait;		// min > 0, time = 0
	      if (vmin == 0)
		{			// min = 0, time > 0
		  while (vtime--)
		    {
		      PeekNamedPipe (get_handle (), NULL, 0, NULL, &n, NULL);
		      if (n)
		        break;
		      Sleep(100);
		    }
		  if (vtime == 0)
		    return 0;
		}
	      else			// min > 0, time > 0
		{
		  if (totalread == 0)
		    goto wait;
		  while (vtime--)
		    {
		      PeekNamedPipe (get_handle (), NULL, 0, NULL, &n, NULL);
		      if (n)
		        break;
		      Sleep(10);
		    }
		  if (vtime == 0)
		    return totalread;
		}
	    }
	}
      termios_printf("reading %d bytes\n", min (vmin, min (len, sizeof (buf))));
      if (ReadFile (get_handle (), (unsigned *) buf,
		 min (vmin, min (len, sizeof (buf))), &n, NULL) == FALSE)
	{
	  termios_printf("read failed (%d)\n", GetLastError ());
	  _raise (SIGHUP);
	}
      if (ttyp->read_retval < 0)	// read error
	{
	  set_errno (-ttyp->read_retval);
	  totalread = -1;
	  break;
	}
      if (ttyp->read_retval == 0)	//EOF
	break;
      len -= n;
      totalread += n;
      memcpy (ptr, buf, n);
      ptr = (char *) ptr + n;
      if (ttyp->termios.c_lflag & ICANON)
	break;
      else if (totalread >= vmin)
	break;
      continue;
    }
done:
  termios_printf("%d=read(%x, %d)\n", totalread, ptr, len);
  return totalread;
}

fhandler_tty_slave::linearize (unsigned char *buf)
{
  int len = sizeof (output_done_event) + sizeof (ioctl_done_event) +
	    sizeof (ttynum) + sizeof (output_handle_)+ sizeof (output_mutex) +
	    sizeof (ioctl_request_event);

  if (buf == 0)
    {
      len += this->fhandler_base::linearize (buf);
      return len;
    }

  memcpy (buf, (char *) &output_done_event, sizeof (output_done_event));
  buf += sizeof (output_done_event);
  memcpy (buf, (char *) &ioctl_request_event, sizeof (ioctl_request_event));
  buf += sizeof (ioctl_request_event);
  memcpy (buf, (char *) &ioctl_done_event, sizeof (ioctl_done_event));
  buf += sizeof (ioctl_done_event);
  memcpy (buf, (char *) &ttynum, sizeof (ttynum));
  buf += sizeof (ttynum);
  memcpy (buf, (char *) &output_handle_, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy (buf, (char *) &output_mutex, sizeof (output_mutex));
  buf += sizeof (output_mutex);
 
  /* We call attach_tty here to increment the count of references to
     this tty.  This will have to be changed if attach_tty ever
     worries about just which process has the tty attached.  */
  attach_tty (ttynum);

  len += this->fhandler_base::linearize (buf);
  return len;
}

fhandler_tty_slave::de_linearize (const unsigned char *buf)
{
  const unsigned char *orig_buf = buf;

  memcpy ((char *) &output_done_event, buf, sizeof (output_done_event));
  buf += sizeof (output_done_event);
  memcpy ((char *) &ioctl_request_event, buf, sizeof (ioctl_request_event));
  buf += sizeof (ioctl_request_event);
  memcpy ((char *) &ioctl_done_event, buf, sizeof (ioctl_done_event));
  buf += sizeof (ioctl_done_event);
  memcpy ((char *) &ttynum, buf, sizeof (ttynum));
  buf += sizeof (ttynum);
  memcpy ((char *) &output_handle_, buf, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy ((char *) &output_mutex, buf, sizeof (output_mutex));
  buf += sizeof (output_mutex);

  int len = buf - orig_buf;
  return (len + this->fhandler_base::de_linearize (buf));
}

int
fhandler_tty_slave::dup (fhandler_base *child)
{
  fhandler_tty_slave *fts = (fhandler_tty_slave *) child;
  tty *ttyp = s->t.gettty (ttynum);
  int errind;

  termios_printf ("in fhandler_tty_slave dup\n");

  attach_tty (ttynum);
  fts->ttynum = ttynum;
  fts->set_close_on_exec (0);
  fts->set_flags (0);
#ifndef __alpha
  const HANDLE proc = GetCurrentProcess ();
#else
  HANDLE proc = GetCurrentProcess ();
#endif
  HANDLE nh;

  if (output_done_event == NULL)
    fts->output_done_event = NULL;
  else if (!DuplicateHandle (proc, output_done_event, proc,
			     &fts->output_done_event, 0, 1,
			     DUPLICATE_SAME_ACCESS))
    {
      errind = 1;
      goto err;
    }
  if (ioctl_request_event == NULL)
    fts->ioctl_request_event = NULL;
  else if (!DuplicateHandle (proc, ioctl_request_event, proc,
			     &fts->ioctl_request_event, 0, 1,
			     DUPLICATE_SAME_ACCESS))
    {
      errind = 2;
      goto err;
    }
  if (ioctl_done_event == NULL)
    fts->ioctl_done_event = NULL;
  else if (!DuplicateHandle (proc, ioctl_done_event, proc,
			     &fts->ioctl_done_event, 0, 1,
			     DUPLICATE_SAME_ACCESS))
    {
      errind = 3;
      goto err;
    }
  if (!DuplicateHandle (proc, output_mutex, proc,
			&fts->output_mutex, 0, 1,
			DUPLICATE_SAME_ACCESS))
    {
      errind = 4;
      goto err;
    }
  if (!DuplicateHandle (proc, get_handle (), proc,
			&nh, 0, 1,
			DUPLICATE_SAME_ACCESS))
    {
      errind = 5;
      goto err;
    }
  if (!DuplicateHandle (proc, output_handle_, proc,
			&fts->output_handle_, 0, 1,
			DUPLICATE_SAME_ACCESS))
    {
      errind = 6;
      goto err;
    }

  fts->set_handle (nh);

  return 0;

 err:
  termios_printf ("dup %d failed in DuplicateHandle: %d", errind,
		  GetLastError ());
  __seterrno ();
  detach_tty (ttynum);
  return -1;
}

void
fhandler_tty_slave::dup_for_fork (void)
{
  attach_tty (ttynum);
}

int
fhandler_tty_slave::fstat (struct stat *buf)
{
  memset (buf, 0, sizeof (*buf));
  buf->st_mode |= S_IFCHR;
  buf->st_blksize = S_BLKSIZE;
  buf->st_uid     = getuid ();
  buf->st_gid     = getgid ();
  buf->st_mode |= STD_RBITS | STD_WBITS | S_IWGRP | S_IWOTH;
  buf->st_ino = get_namehash ();
  termios_printf ("0 = fhandler_tty_slave:fstat (%x) (mode %x)\n",
		  buf, buf->st_mode);
  return 0;
}

int
fhandler_tty_slave::tcgetattr (struct termios *t)
{
  *t = s->t.gettty (ttynum)->termios;
  return 0;
}

int
fhandler_tty_slave::tcsetattr (int a, const struct termios *t)
{
  WaitForSingleObject (output_mutex, INFINITE);
  s->t.gettty (ttynum)->termios = *t;
  ReleaseMutex (output_mutex);
  return 0;
}

int
fhandler_tty_slave::tcflush (int a)
{
  return 0;
}

int
fhandler_tty_slave::tcsetpgrp (const pid_t pgid)
{
  termios_printf ("tcsetpgrp (%d) (sid = %d tsid=%d)\n",
		 pgid, myself->sid, s->t.gettty (ttynum)->getsid ());
  if (myself->sid != s->t.gettty (ttynum)->getsid ())
    {
      set_errno (EPERM);
      return -1;
    }
  s->t.gettty (ttynum)->setpgid (pgid);
  return 0;
}

int
fhandler_tty_slave::tcgetpgrp (void)
{
  return s->t.gettty (ttynum)->getpgid ();
}

void
fhandler_tty_slave::send_ioctl_request (void)
{
  sigset_t mask = ~0, oldmask;
  tty *ttyp = s->t.gettty (ttynum);

  if (ioctl_request_event == NULL || ioctl_done_event == NULL) // slave of pty
    {
      return;
    }

  sigprocmask (SIG_SETMASK, &mask, &oldmask);
  WaitForSingleObject (output_mutex, INFINITE);
  SetEvent (ioctl_request_event);
  WaitForSingleObject (ioctl_done_event, INFINITE);
  ReleaseMutex (output_mutex);
  sigprocmask (SIG_SETMASK, &oldmask, NULL);
}

int
fhandler_tty_slave::ioctl (int cmd, void *arg)
{
  tty *ttyp = s->t.gettty (ttynum);

  termios_printf ("ioctl (%x)\n", cmd);

  if (myself->pgid && ttyp->getpgid () != myself->pgid &&
	 myself->ctty == ttynum && (ttyp->termios.c_lflag & TOSTOP))
    {
      /* background process */
      termios_printf("bg ioctl pgid=%d tpgid=%d ctty=%d", 
			myself->pgid, ttyp->getpgid (), myself->ctty);
      _raise (SIGTTOU);
    }
  ttyp->cmd = cmd;
  ttyp->ioctl_retval = 0;
  switch (cmd)
    {
    case TIOCGWINSZ:
      ttyp->arg.winsize = ttyp->winsize;
      send_ioctl_request ();
      * (struct winsize *) arg = ttyp->arg.winsize;
      ttyp->winsize = ttyp->arg.winsize;
      break;
    case TIOCSWINSZ:
      ttyp->ioctl_retval = -1;
      ttyp->arg.winsize = * (struct winsize *) arg;
      send_ioctl_request ();
      break;
    case TCGETA:
      return tcgetattr ((struct termios *) arg);
    case TCSETA:
      return tcsetattr (TCSANOW, (struct termios *) arg);
    case FIONBIO:
      if (* (int *) arg)
        set_flags (get_flags () | O_NONBLOCK);
      else
        set_flags (get_flags () & ~O_NONBLOCK);
      break;
    default:
      set_errno (EINVAL);
      return -1;
    }
  termios_printf ("%d = ioctl (%x)\n", ttyp->ioctl_retval, cmd);
  return ttyp->ioctl_retval;
}

/*******************************************************
 fhandler_pty_master
*/
fhandler_pty_master::fhandler_pty_master (const char *name) : fhandler_base (name)
{
  ioctl_request_event = NULL;
  ioctl_done_event = NULL;
}

int
fhandler_pty_master::fstat (struct stat *buf)
{
  memset (buf, 0, sizeof (*buf));
  buf->st_mode = S_IFCHR | STD_RBITS | STD_WBITS;
  buf->st_blksize = S_BLKSIZE;
  buf->st_uid     = getuid ();
  buf->st_gid     = getgid ();
  buf->st_ino = get_namehash ();
  termios_printf ("0 = fhandler_tty_slave:fstat (%x) (mode %x)\n",
		  buf, buf->st_mode);
  return 0;
}

fhandler_base *
fhandler_pty_master::open (const char *name, int flags, mode_t)
{
  ttynum = s->t.allocate_tty (0);
  if (ttynum < 0)
    return NULL;

  tty *ttyp = s->t.gettty (ttynum);

  set_flags (flags);

  /* Create communication pipes */

  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.bInheritHandle = 1;
  sa.lpSecurityDescriptor = get_null_sd();

  HANDLE handle, nh;
  if (CreatePipe (&ttyp->input_handle, &handle, &sa, 0) == FALSE)
    {
      termios_printf ("can't create input pipe\n");
      set_errno (ENOENT);
      return NULL;
    }
  output_handle_ = handle;
  if (CreatePipe (&handle, &ttyp->output_handle, &sa, 0) == FALSE)
    {
      termios_printf ("can't create output pipe\n");
      set_errno (ENOENT);
      return NULL;
    }
  set_handle (handle);

  neednl_ = 0;

  /* Save our pid  */

  ttyp->master_pid = GetCurrentProcessId ();
  ttyp->slave_opened = 0;

  /* Allow the others to open us (for handle duplication) */

  handle = GetCurrentProcess();
  if (get_os_type () == winNT && 
      SetKernelObjectSecurity(handle, DACL_SECURITY_INFORMATION, get_null_sd ()) == FALSE)
    small_printf ("Can't set process security %u\n", GetLastError ());

  /* Create synchronisation events */
  char buf[40];

  /* We don't create output_done_event, ioctl_request_event, or
     ioctl_done_event here.  They are used by
     fhandler_tty_master::init, which is used to set up the master tty
     when use_tty is non-zero, and which sets up separate threads to
     handle output and ioctls.  */

  sprintf (buf, RESTART_OUTPUT_EVENT, ttynum);
  restart_output_event = CreateEvent (&sa, FALSE, FALSE, buf);
  sprintf (buf, OUTPUT_MUTEX, ttynum);
  output_mutex = CreateMutex (&sa, FALSE, buf);
  if (restart_output_event == NULL || output_mutex == NULL)
    {
      termios_printf ("can't create events\n");
      set_errno (ENOENT);
      return NULL;
    }

  /* Initial termios values */

  ttyp->termios.c_iflag = BRKINT | ICRNL | IXON;
  ttyp->termios.c_oflag = OPOST | ONLCR;
  ttyp->termios.c_cflag = B9600 | CS8 | CREAD;
  ttyp->termios.c_lflag = ISIG | ICANON | ECHO | IEXTEN;
  ttyp->termios.c_cc[VDISCARD]	= CFLUSH;
  ttyp->termios.c_cc[VEOL]	= CEOL;
  ttyp->termios.c_cc[VEOL2]	= CEOL2;
  ttyp->termios.c_cc[VEOF]	= CEOF;
  ttyp->termios.c_cc[VERASE]	= CERASE;
  ttyp->termios.c_cc[VINTR]	= CINTR;
  ttyp->termios.c_cc[VKILL]	= CKILL;
  ttyp->termios.c_cc[VLNEXT]	= CLNEXT;
  ttyp->termios.c_cc[VMIN]	= 1;
  ttyp->termios.c_cc[VQUIT]	= CQUIT;
  ttyp->termios.c_cc[VREPRINT]	= CRPRNT;
  ttyp->termios.c_cc[VSTART]	= CSTART;
  ttyp->termios.c_cc[VSTOP]	= CSTOP;
  ttyp->termios.c_cc[VSUSP]	= CSUSP;
  ttyp->termios.c_cc[VSWTC]	= CSWTCH;
  ttyp->termios.c_cc[VTIME]	= 0;
  ttyp->termios.c_cc[VWERASE]	= CWERASE;

  cfsetispeed (&ttyp->termios, B38400);
  cfsetospeed (&ttyp->termios, B38400);

  ttyp->winsize.ws_col = 80;
  ttyp->winsize.ws_row = 25;

  termios_printf("tty%d opened\n", ttynum);

  return this;
}

int
fhandler_pty_master::close (void)
{
  if (output_done_event != NULL)
    {
      if (! CloseHandle (output_done_event))
	termios_printf ("CloseHandle 1 failed (%d)\n", GetLastError ());
    }
  if (! CloseHandle (output_mutex))
    termios_printf ("CloseHandle 2 failed (%d)\n", GetLastError ());
  if (! CloseHandle (restart_output_event))
    termios_printf ("CloseHandle 3 failed (%d)\n", GetLastError ());
  if (! CloseHandle (get_handle ()))
    termios_printf ("CloseHandle 4 failed (%d)\n", GetLastError ());
  if (! CloseHandle (output_handle_))
    termios_printf ("CloseHandle 5 failed (%d)\n", GetLastError ());

  detach_tty (ttynum);

  termios_printf("tty%d closed\n", ttynum);

  return 0;
}

int
fhandler_pty_master::write (const void *ptr, size_t len)
{
  do_input (this, (char *) ptr, len);
  return len;
}

int
fhandler_pty_master::read (void *ptr, size_t len)
{
  DWORD n;
  char *cptr = (char *) ptr;

  if (! PeekNamedPipe (get_handle (), NULL, 0, NULL, &n, NULL))
    {
      if (GetLastError () == ERROR_BROKEN_PIPE)
	{
	  /* On Unix, a read from a broken pipe returns EOF.  */
	  return 0;
	}
      __seterrno ();
      return -1;
    }
  if (n == 0
      && (get_flags () & (O_NONBLOCK | O_NDELAY)) != 0)
    {
      set_errno (EAGAIN);
      return -1;
    }
  if (pktmode)
    {
      *cptr++ = TIOCPKT_DATA;
      len--;
    }
  n = do_output (this, cptr, len);
  if (n < 0)
    return -1;
  if (output_done_event != NULL)
    SetEvent (output_done_event);
  if (pktmode && n > 0)
    n++;
  return n;
}

int
fhandler_pty_master::tcgetattr (struct termios *t)
{
  *t = s->t.gettty (ttynum)->termios;
  return 0;
}

int
fhandler_pty_master::tcsetattr (int a, const struct termios *t)
{
  s->t.gettty (ttynum)->termios = *t;
  return 0;
}

int
fhandler_pty_master::tcflush (int a)
{
  return 0;
}

int
fhandler_pty_master::ioctl (int cmd, void *arg)
{
  tty *ttyp = s->t.gettty (ttynum);

  switch (cmd)
    {
    case TIOCPKT:
      pktmode = * (int *) arg;
      break;
    case TIOCGWINSZ:
      * (struct winsize *) arg = ttyp->winsize;
      break;
    case TIOCSWINSZ:
      ttyp->winsize = * (struct winsize *) arg;
      _kill (-ttyp->getpgid (), SIGWINCH);
      break;
    case FIONBIO:
      if (* (int *) arg)
        set_flags (get_flags () | O_NONBLOCK);
      else
        set_flags (get_flags () & ~O_NONBLOCK);
      break;
    default:
  set_errno (EINVAL);
  return -1;
}
  return 0;
}

/* FIXME: it's not possible to make the buf static - dll's data/bss
   areas not copied on fork().
 */
char *
fhandler_pty_master::ptsname (void)
{
  char *buf = (char *) malloc(20);

  sprintf (buf, "/dev/tty%d", ttynum);
  return buf;
}

fhandler_pty_master::linearize (unsigned char *buf)
{
  int len = sizeof (restart_output_event) + sizeof (output_done_event) +
	    sizeof (ttynum) + sizeof (output_handle_)+ sizeof (output_mutex) +
	    sizeof (pktmode);

  if (buf == 0)
    {
      len += this->fhandler_base::linearize (buf);
      return len;
    }

  memcpy (buf, (char *) &output_done_event, sizeof (output_done_event));
  buf += sizeof (output_done_event);
  memcpy (buf, (char *) &restart_output_event, sizeof (restart_output_event));
  buf += sizeof (restart_output_event);
  memcpy (buf, (char *) &ttynum, sizeof (ttynum));
  buf += sizeof (ttynum);
  memcpy (buf, (char *) &output_handle_, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy (buf, (char *) &output_mutex, sizeof (output_mutex));
  buf += sizeof (output_mutex);
  memcpy (buf, (char *) &pktmode, sizeof (pktmode));
  buf += sizeof (pktmode);

  /* We call attach_tty here to increment the count of references to
     this tty.  This will have to be changed if attach_tty ever
     worries about just which process has the tty attached.  */
  attach_tty (ttynum);

  len += this->fhandler_base::linearize (buf);
  return len;
}

fhandler_pty_master::de_linearize (const unsigned char *buf)
{
  const unsigned char *orig_buf = buf;

  memcpy ((char *) &output_done_event, buf, sizeof (output_done_event));
  buf += sizeof (output_done_event);
  memcpy ((char *) &restart_output_event, buf, sizeof (restart_output_event));
  buf += sizeof (restart_output_event);
  memcpy ((char *) &ttynum, buf, sizeof (ttynum));
  buf += sizeof (ttynum);
  memcpy ((char *) &output_handle_, buf, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy ((char *) &output_mutex, buf, sizeof (output_mutex));
  buf += sizeof (output_mutex);
  memcpy ((char *) &pktmode, buf, sizeof (pktmode));
  buf += sizeof (pktmode);

  int len = buf - orig_buf;
  return (len + this->fhandler_base::de_linearize (buf));
}

void
fhandler_pty_master::dup_for_fork (void)
{
  attach_tty (ttynum);
}

extern "C"
int
grantpt(void)
{
  return 0;
}

extern "C"
int
unlockpt(void)
{
  return 0;
}

