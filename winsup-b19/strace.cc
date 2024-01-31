/* strace.cc: system/windows tracing

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include "winsup.h"

/* 'twould be nice to declare this in winsup.h but winsup.h doesn't require
   stdarg.h, so we declare it here instead.  */
extern "C" int __small_vsprintf (char *dst, const char *fmt, va_list ap);

/* Whether strace is going to stderr.  */
static int strace_stderr = 1;

/* Mutex so output from several processes doesn't get intermixed.  */
static HANDLE strace_mutex = INVALID_HANDLE_VALUE;

static DWORD strace_keep = 0;

/* Non-zero if we're to flush the output buffer after every message.
   This slows things down quite a bit, but is useful when a SIGSEGV
   causes program termination before all the output has been printed.  */
static int flush_p;

void
strace_open (char *fn)
{
  HANDLE h;
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;

  if (u->strace_file != NULL &&
      u->strace_file != GetStdHandle (STD_ERROR_HANDLE))
    CloseHandle (u->strace_file);

  /* Use OPEN_ALWAYS so forks don't clobber each other.  */
  h = CreateFileA (fn,
		   GENERIC_WRITE,
		   /* FILE_SHARE_READ: Let other tasks read the trace
		      while it's in progress.  */
		   FILE_SHARE_READ | FILE_SHARE_WRITE,
		   &sa,
		   OPEN_ALWAYS,
		   FILE_ATTRIBUTE_NORMAL,
		   0);
  if (h == INVALID_HANDLE_VALUE)
    {
      small_printf ("Unable to open trace file %s, using stderr.", fn);
      strace_stderr = TRUE;
    }
  else
    {
      u->strace_file = h;
      strace_stderr = FALSE;
    }
}

/* Environment variable `STRACE' is used to turn on tracing.
   Its format is n[:cache][,filename]
   where N is one or more flags (see sys/strace.h) expressed in decimal, or
   in 0x notation for hexadecimal, 0n notation for octal.  A value of 1
   turns on all tracing.

   CACHE is the optional number of lines of information to keep in memory.
   Writing the log messages to memory causes strace_printf to execute more
   quickly, which helps resolve timing issues.  The cache is flushed when the
   user types 'CTRL-T' (see tty.cc), or if _STRACE_EXITDUMP is set
   (see sys/strace.h).

   FILENAME is an optional file to use instead of STD_ERROR_HANDLE.

   Normally tracing output isn't flushed as it slows things immensely.
   However, it can (I think) cause tracing data to be lost of the program
   crashes at the wrong time.  To turn on flushing, use _STRACE_FLUSH.

   Stracing can be turned on after the program is running.  This currently
   requires the program to be ready for it (env var strace is set).  This is
   done so that the trace mutex and file aren't opened for *every* process.
   To enable stracing to be turned on later, but without turning it on
   immediately, set env var strace to 0.  */

void
strace_init (char *buf)
{
  /* The value of myself->strace_mask is inherited from the parent and is copied
     over before be start (the parent creates us suspended).  */

  if (buf && *buf)
    {
      if (u->strace_file != NULL &&
	  u->strace_file != GetStdHandle (STD_ERROR_HANDLE))
	(void)CloseHandle (u->strace_file);
      u->strace_file = GetStdHandle (STD_ERROR_HANDLE);
      strace_stderr = 1;

      if (strace_mutex == INVALID_HANDLE_VALUE)
	{
	  SECURITY_ATTRIBUTES sa;
	  sa.nLength = sizeof (sa);
	  sa.lpSecurityDescriptor = 0;
	  sa.bInheritHandle = TRUE;
	  /* If this fails, that's ok.  The debugging output may get mixed up
	     but that's it.  */
	  strace_mutex = CreateMutexA (&sa, FALSE, cygname ("strace", 0));
	}

      char *p;

      myself->strace_mask = strtol (buf, &p, 0);

      flush_p = !!(myself->strace_mask & _STRACE_FLUSH);
      if (*p == ':')
	{
	  strace_keep = strtol (p + 1, &p, 0);
	  myself->strace_mask |= _STRACE_CACHE;
	}

      if (*p == ',')
	strace_open (p + 1);
    }
}

struct msglist
  {
    struct msglist *next;
    char buf[0];
  };

static struct msglist NO_COPY headlist = {0};

static struct msglist NO_COPY *endlist = &headlist;
int NO_COPY inqueue = 0;

/* Printf function used when tracing system calls.
   DO NOT SET ERRNO HERE.  */

void
strace_printf (const char *str,...)
{
  char buf[6000];
  va_list ap;
  DWORD done;
  int count;
  static time_t last_time = 0;
  time_t t, delta_time;

  t = time (NULL);
  delta_time = last_time ? t - last_time : 0;
  last_time = t;
  
  if (u->strace_file != INVALID_HANDLE_VALUE)
    {
      /* The process table might not be set up yet.  */
      if (u && myself)
	{
	  count = __small_sprintf (buf, "(%s %d) <%d> ",
				   myself->progname ?
				     myself->progname : "unknown",
				   myself->pid,
				   delta_time);
	}
      else
	{
	  count = __small_sprintf (buf, "(unknown) <%d> ", delta_time);
	}

      va_start (ap, str);
      count += __small_vsprintf (buf + count, str, ap);
      va_end (ap);

      /* The reason for the mutex is to keep the debugging output from several
	 processes from intermixing.  However, it's not critical and we
	 certainly don't want to wait too long if the system breaks down.  */
      WaitForSingleObject (strace_mutex, 1000 /* milliseconds */);
      if (!strace_keep)
	{
	  if (GetFileType (u->strace_file) == FILE_TYPE_DISK)
	    SetFilePointer (u->strace_file, 0, 0, FILE_END);
	  WriteFile (u->strace_file, buf, count, &done, 0);
	  /* We don't use (myself->strace_mask & _STRACE_FLUSH) here because that
	     assumes `u' is valid.  */
	  if (flush_p)
	    FlushFileBuffers (u->strace_file);
	}
      else
	{
	  struct msglist *m = NULL;
	  if (++inqueue >= strace_keep)
	    {
	      inqueue = strace_keep - 1;
	      m = headlist.next;
	      headlist.next = m->next;
	      HeapFree (GetProcessHeap (), 0, (LPVOID) m);
	    }
	  m = (struct msglist *)HeapAlloc (GetProcessHeap (), 0,
					   sizeof (*m) + strlen (buf) + 1);
	  strcpy (m->buf, buf);
	  endlist->next = m;
	  (endlist = m)->next = NULL;
	}
      ReleaseMutex (strace_mutex);
    }
}

void
strace_dump (void)
{
  struct msglist *m, *n;
  DWORD done;

  WaitForSingleObject (strace_mutex, 1000 /* milliseconds */);
  if (GetFileType (u->strace_file) == FILE_TYPE_DISK)
    SetFilePointer (u->strace_file, 0, 0, FILE_END);
  for (m = headlist.next; m != NULL; m = n)
    {
      WriteFile (u->strace_file, m->buf, strlen (m->buf), &done, 0);
      n = m->next;
      HeapFree (GetProcessHeap (), 0, (LPVOID) m);
    }

  headlist.next = NULL;
  endlist = &headlist;
  inqueue = 0;
  if (flush_p)
    FlushFileBuffers (u->strace_file);
  ReleaseMutex (strace_mutex);
}

/* Print a message on stderr (bypassing anything that could prevent the
   message from being printed, for example a buggy or corrupted stdio).
   This is used, for example, to print diagnostics of fatal errors.  */

void
system_printf (const char *str,...)
{
  char buf[2000];
  va_list ap;
  DWORD done;
  int count;

  /* The process table might not be set up yet.  */
  if (u && myself)
    {
      count = __small_sprintf (buf, "(%s %d) ", myself->progname, myself->pid);
    }
  else
    {
      count = __small_sprintf (buf, "(unknown) ");
    }

  va_start (ap, str);
  count += __small_vsprintf (buf + count, str, ap);
  va_end (ap);

  if (! strace_stderr)
    debug_printf ("%s", buf);

  WriteFile (GetStdHandle (STD_ERROR_HANDLE), buf, count, &done, 0);
  FlushFileBuffers (GetStdHandle (STD_ERROR_HANDLE));
}

void
small_printf (const char *str,...)
{
  char buf[2000];
  va_list ap;
  DWORD done;
  int count;

  va_start (ap, str);
  count = __small_vsprintf (buf, str, ap);
  va_end (ap);

  WriteFile (GetStdHandle (STD_ERROR_HANDLE), buf, count, &done, 0);
  FlushFileBuffers (GetStdHandle (STD_ERROR_HANDLE));
}

void mark (const char *s, int i)
{
#if 0
register int x  asm ("r2");
register int y  asm ("r31");
int ox = x;
int oy = y;
alloca (100000);
#endif

  if (0 ) 
    {
      char b[2000];
      DWORD c;
      c =  __small_sprintf (b,"%s:%d %x %x %x\n", s,i, &i);

      WriteFile (GetStdHandle (STD_ERROR_HANDLE),
		 b, c, &c, 0);
#if 0
      c =  __small_sprintf (b,"AGAIN %s:%d %x %x %x\n", s,i, &i, x,y);

      WriteFile (GetStdHandle (STD_ERROR_HANDLE),
		 b, c, &c, 0);
#endif

    }
}

static const struct tab
{
  int v;
  const char *n;
}
ta[] =
{
  {  WM_NULL, "WM_NULL"  },
  {  WM_CREATE, "WM_CREATE"  },
  {  WM_DESTROY, "WM_DESTROY"  },
  {  WM_MOVE, "WM_MOVE"  },
  {  WM_SIZE, "WM_SIZE"  },
  {  WM_ACTIVATE, "WM_ACTIVATE"  },
  {  WM_SETFOCUS, "WM_SETFOCUS"  },
  {  WM_KILLFOCUS, "WM_KILLFOCUS"  },
  {  WM_ENABLE, "WM_ENABLE"  },
  {  WM_SETREDRAW, "WM_SETREDRAW"  },
  {  WM_SETTEXT, "WM_SETTEXT"  },
  {  WM_GETTEXT, "WM_GETTEXT"  },
  {  WM_GETTEXTLENGTH, "WM_GETTEXTLENGTH"  },
  {  WM_PAINT, "WM_PAINT"  },
  {  WM_CLOSE, "WM_CLOSE"  },
  {  WM_QUERYENDSESSION, "WM_QUERYENDSESSION"  },
  {  WM_QUIT, "WM_QUIT"  },
  {  WM_QUERYOPEN, "WM_QUERYOPEN"  },
  {  WM_ERASEBKGND, "WM_ERASEBKGND"  },
  {  WM_SYSCOLORCHANGE, "WM_SYSCOLORCHANGE"  },
  {  WM_ENDSESSION, "WM_ENDSESSION"  },
  {  WM_SHOWWINDOW, "WM_SHOWWINDOW"  },
  {  WM_WININICHANGE, "WM_WININICHANGE"  },
  {  WM_DEVMODECHANGE, "WM_DEVMODECHANGE"  },
  {  WM_ACTIVATEAPP, "WM_ACTIVATEAPP"  },
  {  WM_FONTCHANGE, "WM_FONTCHANGE"  },
  {  WM_TIMECHANGE, "WM_TIMECHANGE"  },
  {  WM_CANCELMODE, "WM_CANCELMODE"  },
  {  WM_SETCURSOR, "WM_SETCURSOR"  },
  {  WM_MOUSEACTIVATE, "WM_MOUSEACTIVATE"  },
  {  WM_CHILDACTIVATE, "WM_CHILDACTIVATE"  },
  {  WM_QUEUESYNC, "WM_QUEUESYNC"  },
  {  WM_GETMINMAXINFO, "WM_GETMINMAXINFO"  },
  {  WM_PAINTICON, "WM_PAINTICON"  },
  {  WM_ICONERASEBKGND, "WM_ICONERASEBKGND"  },
  {  WM_NEXTDLGCTL, "WM_NEXTDLGCTL"  },
  {  WM_SPOOLERSTATUS, "WM_SPOOLERSTATUS"  },
  {  WM_DRAWITEM, "WM_DRAWITEM"  },
  {  WM_MEASUREITEM, "WM_MEASUREITEM"  },
  {  WM_DELETEITEM, "WM_DELETEITEM"  },
  {  WM_VKEYTOITEM, "WM_VKEYTOITEM"  },
  {  WM_CHARTOITEM, "WM_CHARTOITEM"  },
  {  WM_SETFONT, "WM_SETFONT"  },
  {  WM_GETFONT, "WM_GETFONT"  },
  {  WM_SETHOTKEY, "WM_SETHOTKEY"  },
  {  WM_GETHOTKEY, "WM_GETHOTKEY"  },
  {  WM_QUERYDRAGICON, "WM_QUERYDRAGICON"  },
  {  WM_COMPAREITEM, "WM_COMPAREITEM"  },
  {  WM_COMPACTING, "WM_COMPACTING"  },
  {  WM_WINDOWPOSCHANGING, "WM_WINDOWPOSCHANGING"  },
  {  WM_WINDOWPOSCHANGED, "WM_WINDOWPOSCHANGED"  },
  {  WM_POWER, "WM_POWER"  },
  {  WM_COPYDATA, "WM_COPYDATA"  },
  {  WM_CANCELJOURNAL, "WM_CANCELJOURNAL"  },
  {  WM_NCCREATE, "WM_NCCREATE"  },
  {  WM_NCDESTROY, "WM_NCDESTROY"  },
  {  WM_NCCALCSIZE, "WM_NCCALCSIZE"  },
  {  WM_NCHITTEST, "WM_NCHITTEST"  },
  {  WM_NCPAINT, "WM_NCPAINT"  },
  {  WM_NCACTIVATE, "WM_NCACTIVATE"  },
  {  WM_GETDLGCODE, "WM_GETDLGCODE"  },
  {  WM_NCMOUSEMOVE, "WM_NCMOUSEMOVE"  },
  {  WM_NCLBUTTONDOWN, "WM_NCLBUTTONDOWN"  },
  {  WM_NCLBUTTONUP, "WM_NCLBUTTONUP"  },
  {  WM_NCLBUTTONDBLCLK, "WM_NCLBUTTONDBLCLK"  },
  {  WM_NCRBUTTONDOWN, "WM_NCRBUTTONDOWN"  },
  {  WM_NCRBUTTONUP, "WM_NCRBUTTONUP"  },
  {  WM_NCRBUTTONDBLCLK, "WM_NCRBUTTONDBLCLK"  },
  {  WM_NCMBUTTONDOWN, "WM_NCMBUTTONDOWN"  },
  {  WM_NCMBUTTONUP, "WM_NCMBUTTONUP"  },
  {  WM_NCMBUTTONDBLCLK, "WM_NCMBUTTONDBLCLK"  },
  {  WM_KEYFIRST, "WM_KEYFIRST"  },
  {  WM_KEYDOWN, "WM_KEYDOWN"  },
  {  WM_KEYUP, "WM_KEYUP"  },
  {  WM_CHAR, "WM_CHAR"  },
  {  WM_DEADCHAR, "WM_DEADCHAR"  },
  {  WM_SYSKEYDOWN, "WM_SYSKEYDOWN"  },
  {  WM_SYSKEYUP, "WM_SYSKEYUP"  },
  {  WM_SYSCHAR, "WM_SYSCHAR"  },
  {  WM_SYSDEADCHAR, "WM_SYSDEADCHAR"  },
  {  WM_KEYLAST, "WM_KEYLAST"  },
  {  WM_INITDIALOG, "WM_INITDIALOG"  },
  {  WM_COMMAND, "WM_COMMAND"  },
  {  WM_SYSCOMMAND, "WM_SYSCOMMAND"  },
  {  WM_TIMER, "WM_TIMER"  },
  {  WM_HSCROLL, "WM_HSCROLL"  },
  {  WM_VSCROLL, "WM_VSCROLL"  },
  {  WM_INITMENU, "WM_INITMENU"  },
  {  WM_INITMENUPOPUP, "WM_INITMENUPOPUP"  },
  {  WM_MENUSELECT, "WM_MENUSELECT"  },
  {  WM_MENUCHAR, "WM_MENUCHAR"  },
  {  WM_ENTERIDLE, "WM_ENTERIDLE"  },
  {  WM_CTLCOLORMSGBOX, "WM_CTLCOLORMSGBOX"  },
  {  WM_CTLCOLOREDIT, "WM_CTLCOLOREDIT"  },
  {  WM_CTLCOLORLISTBOX, "WM_CTLCOLORLISTBOX"  },
  {  WM_CTLCOLORBTN, "WM_CTLCOLORBTN"  },
  {  WM_CTLCOLORDLG, "WM_CTLCOLORDLG"  },
  {  WM_CTLCOLORSCROLLBAR, "WM_CTLCOLORSCROLLBAR"  },
  {  WM_CTLCOLORSTATIC, "WM_CTLCOLORSTATIC"  },
  {  WM_MOUSEFIRST, "WM_MOUSEFIRST"  },
  {  WM_MOUSEMOVE, "WM_MOUSEMOVE"  },
  {  WM_LBUTTONDOWN, "WM_LBUTTONDOWN"  },
  {  WM_LBUTTONUP, "WM_LBUTTONUP"  },
  {  WM_LBUTTONDBLCLK, "WM_LBUTTONDBLCLK"  },
  {  WM_RBUTTONDOWN, "WM_RBUTTONDOWN"  },
  {  WM_RBUTTONUP, "WM_RBUTTONUP"  },
  {  WM_RBUTTONDBLCLK, "WM_RBUTTONDBLCLK"  },
  {  WM_MBUTTONDOWN, "WM_MBUTTONDOWN"  },
  {  WM_MBUTTONUP, "WM_MBUTTONUP"  },
  {  WM_MBUTTONDBLCLK, "WM_MBUTTONDBLCLK"  },
  {  WM_MOUSELAST, "WM_MOUSELAST"  },
  {  WM_PARENTNOTIFY, "WM_PARENTNOTIFY"  },
  {  WM_ENTERMENULOOP, "WM_ENTERMENULOOP"  },
  {  WM_EXITMENULOOP, "WM_EXITMENULOOP"  },
  {  WM_MDICREATE, "WM_MDICREATE"  },
  {  WM_MDIDESTROY, "WM_MDIDESTROY"  },
  {  WM_MDIACTIVATE, "WM_MDIACTIVATE"  },
  {  WM_MDIRESTORE, "WM_MDIRESTORE"  },
  {  WM_MDINEXT, "WM_MDINEXT"  },
  {  WM_MDIMAXIMIZE, "WM_MDIMAXIMIZE"  },
  {  WM_MDITILE, "WM_MDITILE"  },
  {  WM_MDICASCADE, "WM_MDICASCADE"  },
  {  WM_MDIICONARRANGE, "WM_MDIICONARRANGE"  },
  {  WM_MDIGETACTIVE, "WM_MDIGETACTIVE"  },
  {  WM_MDISETMENU, "WM_MDISETMENU"  },
  {  WM_DROPFILES, "WM_DROPFILES"  },
  {  WM_MDIREFRESHMENU, "WM_MDIREFRESHMENU"  },
  {  WM_CUT, "WM_CUT"  },
  {  WM_COPY, "WM_COPY"  },
  {  WM_PASTE, "WM_PASTE"  },
  {  WM_CLEAR, "WM_CLEAR"  },
  {  WM_UNDO, "WM_UNDO"  },
  {  WM_RENDERFORMAT, "WM_RENDERFORMAT"  },
  {  WM_RENDERALLFORMATS, "WM_RENDERALLFORMATS"  },
  {  WM_DESTROYCLIPBOARD, "WM_DESTROYCLIPBOARD"  },
  {  WM_DRAWCLIPBOARD, "WM_DRAWCLIPBOARD"  },
  {  WM_PAINTCLIPBOARD, "WM_PAINTCLIPBOARD"  },
  {  WM_VSCROLLCLIPBOARD, "WM_VSCROLLCLIPBOARD"  },
  {  WM_SIZECLIPBOARD, "WM_SIZECLIPBOARD"  },
  {  WM_ASKCBFORMATNAME, "WM_ASKCBFORMATNAME"  },
  {  WM_CHANGECBCHAIN, "WM_CHANGECBCHAIN"  },
  {  WM_HSCROLLCLIPBOARD, "WM_HSCROLLCLIPBOARD"  },
  {  WM_QUERYNEWPALETTE, "WM_QUERYNEWPALETTE"  },
  {  WM_PALETTEISCHANGING, "WM_PALETTEISCHANGING"  },
  {  WM_PALETTECHANGED, "WM_PALETTECHANGED"  },
  {  WM_HOTKEY, "WM_HOTKEY"  },
  {  WM_PENWINFIRST, "WM_PENWINFIRST"  },
  {  WM_PENWINLAST, "WM_PENWINLAST"  },
  {  WM_ASYNCIO, "ASYNCIO"  },
  {  0, 0  }};

void _strace_wm (int message, int word, int lon)
{ 
  if (strace () & _STRACE_WM) 
    {
      int i;

      for (i = 0; ta[i].n; i++)	
	{	
	  if (ta[i].v == message)	    
	    {
	      strace_printf ("wndproc %d %s %d %d\n", message, ta[i].n, word, lon);
	      return;
	    }	
	}
      strace_printf ("wndproc %d unknown  %d %d\n", message, word, lon);    
    }
}

#undef strace
/* FIXME: Not sure why this exists, except perhaps to export the strace
   facility to apps.  */
extern "C" {
int strace ()
  {
    return myself ? myself->strace_mask : 0;
  }
};



