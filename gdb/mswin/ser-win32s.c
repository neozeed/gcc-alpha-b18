/* Remote serial interface for local (hardwired) serial ports for WIN32S.
   Copyright 1995 Free Software Foundation, Inc.
   Contributed by Cygnus Support.  Written by Steve Chamberlain.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#define PTR void *
#define PARAMS(x) x
#include "../defs.h"
#undef min			/* These come from stdlib.h */
#undef max
#include "gdbcmd.h"
#include "gdbwin.h"
#include "serial.h"
#include <errno.h>
#include "windefs.h"
#include "serdll32.h"

const char *doing_something (const char *s);

#define PROGRESS_HOOK(x) doing_something(x)

/* This is unused for now.  We just return a placeholder. */

struct win32s_ttystate
  {
    int bogus;
  };

static int win32s_open PARAMS ((serial_t scb, const char *name));
static void win32s_raw PARAMS ((serial_t scb));
static int win32s_readchar PARAMS ((serial_t scb, int timeout));
static int win32s_setbaudrate PARAMS ((serial_t scb, int rate));
static int win32s_write PARAMS ((serial_t scb, const char *str, int len));
static void win32s_close PARAMS ((serial_t scb));
static serial_ttystate win32s_get_tty_state PARAMS ((serial_t scb));
static int win32s_set_tty_state PARAMS ((serial_t scb, serial_ttystate state));
static char *aptr PARAMS ((short p));
static void (*serial_dll_open_ptr) (int com);
static int (*serial_dll_read_ptr) (int timeout);
static void (*serial_dll_write_ptr) (const char *ptr, int len);
static void (*serial_dll_close_ptr) ();
static int WIN32S_P;

static const char *pmap[] =
{"o", "e", "n", "m", "s"};

/* Idxed by file idx */
#define MAX_SERIAL 5

/* Visible to the options module */
char serial_port[5];
int baud_rate;
int serial_parity;
int serial_bits;
int serial_stop_bits;

/* Local and static - this serial stuff is gross */
static int opened;
static HANDLE handle;
static int commPortId;
char serdll_name[16]; /* name of dll to load for serial communication */


static void
reset_dcb (serial_t scb)
{
  win32s_close (scb);
  win32s_open (scb, serial_port);
}

static int
win32s_open (serial_t scb, const char *name)
{
  memcpy (serial_port, name, sizeof (serial_port));

  if (name[3] == '1'
      || name[3] == '2'
      || name[3] == '3'
      || name[3] == '4')
    {
      if (WIN32S_P)
	{
	  int portid;
	  char comm_string[20];

	  sprintf (comm_string, "%s:%d,%s,%d,%d",
		   name,
		   baud_rate ? baud_rate : 9600,
		   pmap[serial_parity],
		   serial_bits ? serial_bits : 8,
		   serial_stop_bits ? serial_stop_bits : 1);

	  portid = OpenComm16 (name,
			       4096, 4096,
			       comm_string);
	  if (portid < 0)
	    {
	      char *message;

	      switch (portid)
		{
		case -2:
		  message = "already open";
		  break;
		default:
		  message = "unknown error";
		  break;
		}
	      error ("Unable to open port '%s', (%s) %d.", name, message,
		     portid);
	    }
	  commPortId = portid;
	}
      else
	{
	  DCB commDCB;
	  HANDLE hdnl;

	  hdnl
	    = CreateFile (name, GENERIC_READ | GENERIC_WRITE,
			  0,
			  NULL,
			  OPEN_EXISTING, 0,
			  NULL);
	  if ((int) hdnl < 0)
	    {
	      DWORD dw;

	      dw = GetLastError ();

	      error ("Unable to open port, last error: %d", dw);
	    }
	  SetupComm (hdnl, 1024, 1024);

	  if (!GetCommState (hdnl, &commDCB))
	    {
	      CloseHandle (hdnl);
	      error ("Failure in GetCommState, %d", GetLastError ());
	      return -1;
	    }

	  commDCB.BaudRate = baud_rate ? baud_rate : 9600;
	  commDCB.fBinary = TRUE; /* Binary I/O */
	  commDCB.fParity = FALSE; /* Don't check parity */
	  commDCB.fOutxCtsFlow = FALSE;	/* Ignore CTS */
	  commDCB.fOutxDsrFlow = FALSE;	/* Ignore DSR */
	  commDCB.fDtrControl = DTR_CONTROL_ENABLE; /* Nail up DTR */
	  commDCB.fDsrSensitivity = FALSE; /* Ignore DSR for input throttle */
	  commDCB.fInX = FALSE;	/* No XON/XOFF for input */
	  commDCB.fOutX = FALSE; /* No XON/XOFF for output */
	  commDCB.fNull = FALSE; /* Don't discard NULs */
	  commDCB.fRtsControl = RTS_CONTROL_ENABLE; /* Nail up RTS */
	  commDCB.ByteSize = 8;
	  commDCB.Parity = NOPARITY;
	  commDCB.StopBits = ONESTOPBIT;
	  commDCB.ByteSize = 8;

	  if (!SetCommState (hdnl, &commDCB))
	    {
	      CloseHandle (hdnl);
	      error ("Failure in SetCommState, %d", GetLastError ());
	      return -1;
	    }

	  handle = hdnl;
	}
    }
  else
    {
      errno = ENOENT;
      return (-1);
    }

  scb->fd = 1;
  opened = 1;
  strcpy (serial_port, name);
  return 0;
}

static int
win32s_noop (serial_t scb)
{
  return 0;
}

static void
win32s_raw (serial_t scb)
{
  /* Always effectively in raw mode. */
}

/* Read a character with user-specified timeout.  TIMEOUT is number of seconds
   to wait, or -1 to wait forever.  Use timeout of 0 to effect a poll.  Returns
   char if successful.  Returns -2 if timeout expired, EOF if line dropped
   dead, or -3 for any other error (see errno in that case). */

int
poll (char *p)
{
  static int rl = 0;

  if (WIN32S_P)
    {
      return GetCommReady16 (commPortId, p);
    }
  else
    {
      DWORD w;
      COMSTAT stat;

      ClearCommError (handle, &w, &stat);
      if (stat.cbInQue)
	{
	  DWORD res;
	  int len = stat.cbInQue;

	  if (len > 100)
	    len = 100;
	  ReadFile (handle, p, len, &res, NULL);
	  return res;
	}
    }
  return 0;
}

static int
win32s_readchar (serial_t scb, int timeout)
{
  int c;
  DWORD otickcount = 0;

#if 0
  if (timeout == -1)
    timeout = 4;
#endif
  if (scb->bufcnt)
    {
      c = *(scb->bufp);
      scb->bufp++;
      scb->bufcnt--;
      return c;
    }

  while (1)
    {
      int len = poll (scb->buf);

      if (len > 0)
	{
	  scb->bufcnt = len - 1;
	  scb->bufp = scb->buf + 1;
	  {
	    int j;
	    static char mybuf[100];

	    for (j = 0; j < len; j++)
	      mybuf[j] = scb->buf[j];
	    mybuf[j] = 0;
	    PROGRESS_HOOK (mybuf);
	  }
	  return scb->buf[0];
	}
      else
	{
	  if (timeout == 0)
	    return SERIAL_TIMEOUT;
	  if (timeout == -1)
	    continue;
	  if (otickcount == 0)
	    otickcount = GetTickCount ();
	  if (GetTickCount () > otickcount + timeout * 1000)
	    {
	      return SERIAL_TIMEOUT;
	    }
	}
    }
}

/* win32s_{get set}_tty_state() are both dummys to fill out the function
   vector.  Someday, they may do something real... */

static serial_ttystate
win32s_get_tty_state (serial_t scb)
{
  static struct win32s_ttystate state;

  return (serial_ttystate) & state;

}

static int
win32s_set_tty_state (serial_t scb, serial_ttystate ttystate)
{
  return 0;
}

static int
win32s_noflush_set_tty_state (serial_t scb,
			      serial_ttystate new_ttystate,
			      serial_ttystate old_ttystate)
{
  return 0;
}

static void
win32s_print_tty_state (serial_t scb, serial_ttystate ttystate)
{
  /* Nothing to print.  */
  return;
}

static int
win32s_set_baud_rate (serial_t scb, int rate)
{
  baud_rate = rate;
  reset_dcb (scb);
  return 0;
}

static int
win32s_set_stop_bits (serial_t scb, int num)
{
  serial_stop_bits = num;
  reset_dcb (scb);
  return 0;
}

/* Sometimes we can write too fast for the receiver,
   adjusting this changes all that */

int write_dos_tick_delay = 0;

static int
win32s_write (serial_t scb, const char *str, int len)
{
  int olen = len;
  int j;

  len = 1;
  for (j = 0; j < olen; str++, j++)
    {
      /* Cope with polling I/O done on some boards */
      if (write_dos_tick_delay)
	{
	  unsigned long endtickcount = GetTickCount () + write_dos_tick_delay;

	  while (GetTickCount () < endtickcount)
	    ;
	}
      if (WIN32S_P)
	{
	  int i;

	  do
	    {
	      i = WriteComm16 (commPortId, str, len);
	    }
	  while (i == 0);

	  if (i != len)
	    {
	      char b[100];

	      sprintf (b, "i out of range:  i = %d, len = %d", i, len);
	      MessageBox (NULL, "Warning", b, MB_OK);
	    }

	  if (i <= 0)
	    {
	      int e = GetCommError16 (commPortId, NULL);
	      char b[200];

	      if (e == 0xe0)
		{
		  MessageBox (NULL, "Warning",
			      "Write timed out with various\nRTS and CTS things.\n  I suspect open problems.", MB_OK);
		}
	      else
		{
		  sprintf (b, "Write Error %x", e);
		  MessageBox (NULL, b, "OOPS", MB_OK);
		}
	    }
	}
      else
	{
	  DWORD count;

	  WriteFile (handle, (LPVOID) str, len, &count, NULL);

	  if (count != (DWORD)len)
	    {
	      MessageBox (NULL, "Error in write", "Error in write", MB_OK);
	    }
	}
    }
  return 0;
}

static void
win32s_close (serial_t scb)
{
  if (opened)
    {
      opened = 0;
      if (WIN32S_P)
	{
	  CloseComm16 (commPortId);
	}

      else
	{
	  CloseHandle (handle);
	}
    }
}

int
win32s_flush_output (serial_t x)
{
  if (WIN32S_P)
    {
      /*FlushComm16(commPortId,0); */
    }
  return 0;
}

int
win32s_flush_input (serial_t x)
{
  x->bufcnt = 0;
  if (WIN32S_P)
    {
      /*FlushComm16(commPortId,1); */
    }
  return 0;
}

int
win32s_send_break (serial_t x)
{
  return 0;
}

static struct serial_ops win32s_ops =
{
  "hardwire",
  0,
  win32s_open,
  win32s_close,
  win32s_readchar,
  win32s_write,
  win32s_flush_output,		/* flush output */
  win32s_flush_input,		/* flush input */
  win32s_send_break,		/* send break -- currently only for nindy */
  win32s_raw,
  win32s_get_tty_state,
  win32s_set_tty_state,
  win32s_print_tty_state,
  win32s_noflush_set_tty_state,
  win32s_set_baud_rate,
  win32s_set_stop_bits,
};


#ifdef DYNAMIC_LOAD

/* dll entry points for serdll32.dll; call kernel32 to thunk for us */
typedef BOOL (APIENTRY * PUTREGISTER) (
	HANDLE hModule,
        LPCSTR lpsz16BitDLL,
	LPCSTR lpszInitName,
	LPCSTR lpszProcName,
	UT32PROC * ppfn32Thunk,
	FARPROC pfnUT32Callback,
	LPVOID lpBuff
	);

HANDLE hSerdll = 0;

/****** Comm support via serdll32.dll *************************************
int APIENTRY BuildCommDCB16(LPCSTR lpszDef, DCB16 *lpdcb);
int APIENTRY OpenComm16(LPCSTR lpszDevControl, USHORT cbInQueue, 
		USHORT cbOutQueue, LPCSTR dcb);
int APIENTRY CloseComm16(INT idComDev);
int APIENTRY ReadComm16(INT idComDev, LPVOID lpBuf, INT cbRead);
int APIENTRY WriteComm16(INT idComDev, LPCSTR lpBuf, INT cbWrite);
int APIENTRY FlushComm16(INT idComDev, INT fnQueue);
int APIENTRY TransmitCommChar16(INT idComDev, char chTransmit);
int APIENTRY SetCommState16(DCB16 *lpdcb); 
int APIENTRY GetCommState16(INT idComDev,DCB16 *lpdcb); 
int APIENTRY GetCommError16(INT idComDev,COMSTAT16 *lpcommstat);
int APIENTRY GetCommReady16(INT idComDev, char *);
int APIENTRY SetCommBreak16(INT idComDev);
int APIENTRY ClearCommBreak16(INT idComDev);
**************************************************************************/

/* dll entry points for serdll32.dll */
#define STR(x) #x
#define DEFINE_ENTRY(PROC, RET, ARGDEFS, ARGS) \
    typedef RET (APIENTRY * t_##PROC) ARGDEFS; /* define proc's type */ \
    t_##PROC p_##PROC=NULL; /* initialize proc to NULL */ \
    static RET PROC ARGDEFS /* local wrapper for call to proc */ \
    { \
	if (!p_##PROC) /* do we have proc's address yet? */\
	{ \
	  p_##PROC = (t_##PROC) GetProcAddress (hSerdll, STR(PROC)); \
	    if (!p_##PROC) \
	    { \
		printf_filtered( "Error: unable to resolve %s.\n", STR(PROC)); \
		return 0; \
	    } \
	} \
	if (p_##PROC) \
	  return p_##PROC ARGS; /* call proc */ \
	return 0; \
    }

  DEFINE_ENTRY( BuildCommDCB16, int,
		(LPCSTR lpszDef, DCB16 *lpdcb),
		 (lpszDef, lpdcb))
  DEFINE_ENTRY( OpenComm16, int,
		(LPCSTR lpszDevControl, USHORT cbInQueue,
		 USHORT cbOutQueue, LPCSTR dcb),
		 (lpszDevControl, cbInQueue, cbOutQueue, dcb))
  DEFINE_ENTRY( CloseComm16, int,
		(INT idComDev),
		 (idComDev))
  DEFINE_ENTRY( ReadComm16, int,
		(INT idComDev, LPVOID lpBuf, INT cbRead),
		 (idComDev, lpBuf, cbRead))
  DEFINE_ENTRY( WriteComm16, int,
		(INT idComDev, LPCSTR lpBuf, INT cbWrite),
		 (idComDev, lpBuf, cbWrite))
  DEFINE_ENTRY( FlushComm16, int,
		(INT idComDev, INT fnQueue),
		 (idComDev, fnQueue))
  DEFINE_ENTRY( TransmitCommChar16, int,
		(INT idComDev, char chTransmit),
		 (idComDev, chTransmit))
  DEFINE_ENTRY( SetCommState16, int,
		(DCB16 *lpdcb),
		 (lpdcb))
  DEFINE_ENTRY( GetCommState16, int,
		(INT idComDev, DCB16 *lpdcb),
		 (idComDev, lpdcb))
  DEFINE_ENTRY( GetCommError16, int,
		(INT idComDev, COMSTAT16 *lpcommstat),
		 (idComDev, lpcommstat))
  DEFINE_ENTRY( GetCommReady16, int,
		(INT idComDev, char *),
		 (idComDev, c))
  DEFINE_ENTRY( SetCommBreak16, int,
		(INT idComDev),
		 (idComDev))
  DEFINE_ENTRY( ClearCommBreak16, int,
		(INT idComDev),
		 (idComDev))

static int 
load_serdll(void)
{
  char dll[64];

  if (win_host()!=win32s)
    {
        return 0;
    }

  /* load dll for windows serial support */
  strcpy(dll,"serdll32.dll");
  hSerdll = LoadLibrary (dll);
  if (!hSerdll)
    {
        printf_filtered( "Error: unable to load %s.\n",dll);
        return 0;
    }
  return 1;
}
#endif /* DYNAMIC_LOAD */

extern struct cmd_list_element *setlist;
extern struct cmd_list_element *showlist;
void
_initialize_ser_win32s ()
{

  switch(win_host())
  {
      case winnt:
        WIN32S_P = 0; /* windows NT */
    	break;
      case win95:
        WIN32S_P = 0; /* windows 95 */
    	break;
      case win32s:
        WIN32S_P = 1; /* windows 3.1 or windows for workgroups with win32s */
    	break;
   }
   
#ifdef DYNAMIC_LOAD
  switch(win_host())
  {
      case winnt:
	strcpy(serdll_name,"serdllnt.dll");
    	break;
      case win95:
	strcpy(serdll_name,"serdll95.dll");
    	break;
      case win32s:
	strcpy(serdll_name,"serdll32.dll");
    	break;
   }

  if (win_host()==win32s)
      load_serdll();

  make_final_cleanup(unload_serdll,0);	/* make sure dll gets unloaded */
#endif

#ifndef BUILD_DLL 
  if (win_host()==win32s)
      load_serdll16();

  make_final_cleanup(unload_serdll16,0);	/* make sure dll gets unloaded */
#endif /* !BUILD_DLL */

  serial_add_interface (&win32s_ops);

  add_show_from_set (add_set_cmd
		     ("remotedelay", -1,
		      var_zinteger, (char *) &write_dos_tick_delay,
		      "Set delay in ticks between transmitted characters for remote serial I/O.\n\
This value is used to slow down GDB to cope with slow targets.\n", &setlist),
		     &showlist);
}
