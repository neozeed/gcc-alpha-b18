/* console.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/termios.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "winsup.h"

#define srTop (info.winTop + scroll_region.Top)
#define srBottom (info.winTop + scroll_region.Bottom)

#define use_tty ISSTATE(myself, PID_USETTY)

/**********************************************************************/
/* fhandler_console */

static void
undo_input (HANDLE h, char *ptr)
{
  INPUT_RECORD input_rec;
  DWORD n;

  memset (&input_rec, 0, sizeof (input_rec));
  input_rec.EventType = KEY_EVENT;
  while (*ptr)
    {
      input_rec.Event.KeyEvent.AsciiChar = *ptr++;
      input_rec.Event.KeyEvent.bKeyDown = 1;
      WriteConsoleInput (h, &input_rec, 1, &n);
      input_rec.Event.KeyEvent.bKeyDown = 0;
      WriteConsoleInput (h, &input_rec, 1, &n);
    }
}

static struct
  {
    SHORT winTop;
    SHORT winBottom;
    COORD dwWinSize;
    COORD dwCursorPosition;
    WORD wAttributes;
  } info;

BOOL
fhandler_console::fillin_info (void)
{
  BOOL ret;
  CONSOLE_SCREEN_BUFFER_INFO linfo;

  if (ret = GetConsoleScreenBufferInfo (get_output_handle(), &linfo))
    {
      info.winTop = linfo.srWindow.Top;
      info.winBottom = linfo.srWindow.Bottom;
      info.dwWinSize.Y = 1 + linfo.srWindow.Bottom - linfo.srWindow.Top;
      info.dwWinSize.X = 1 + linfo.srWindow.Right - linfo.srWindow.Left;
      info.dwCursorPosition = linfo.dwCursorPosition;
      info.wAttributes = linfo.wAttributes;
    }
  else
    {
      memset (&info, 0, sizeof info);
      info.dwWinSize.Y = 25;
      info.dwWinSize.X = 80;
      info.winBottom = 24;
    }
  return ret;
}

/*
 * Scroll the screen context.
 * x1, y1 - ul corner
 * x2, y2 - dr corner
 * xn, yn - new ul corner
 * Negative values represents current screen dimensions
 */
static struct
    {
      short Top, Bottom;
    } scroll_region = {0, -1};

void
fhandler_console::scroll_screen (int x1, int y1, int x2, int y2, int xn, int yn)
{
  SMALL_RECT sr1, sr2;
  CHAR_INFO fill;
  COORD dest;

  (void)fillin_info ();
  if (scroll_region.Bottom < 0)
    scroll_region.Bottom = info.dwWinSize.Y - 1;
  sr1.Left = x1 >= 0 ? x1 : info.dwWinSize.X - 1;
  if (y1 == 0)
    sr1.Top = info.winTop;
  else
    sr1.Top = y1 > 0 ? y1 : info.winBottom;
  sr1.Right = x2 >= 0 ? x2 : info.dwWinSize.X - 1;
  if (y2 == 0)
    sr1.Bottom = info.winTop;
  else
    sr1.Bottom = y2 > 0 ? y2 : info.winBottom;
  sr2.Top = srTop;
  sr2.Left = 0;
  sr2.Bottom = srBottom;
  sr2.Right = info.dwWinSize.X - 1;
  if (sr1.Bottom > sr2.Bottom && sr1.Top <= sr2.Bottom)
    sr1.Bottom = sr2.Bottom;
  dest.X = xn >= 0 ? xn : info.dwWinSize.X - 1;
  if (yn == 0)
    dest.Y = info.winTop;
  else
    dest.Y = yn > 0 ? yn : info.winBottom;
  fill.Char.AsciiChar = ' ';
  fill.Attributes = default_color;
  ScrollConsoleScreenBuffer (get_output_handle (), &sr1, &sr2, dest, &fill);
  if (sr1.Top != sr1.Bottom)
    clear_screen (0, 1 + dest.Y + sr1.Bottom - sr1.Top, sr2.Right, sr2.Bottom);
}

fhandler_base *
fhandler_console::open (const char *name, int flags, mode_t)
{
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = 0;
  sa.bInheritHandle = TRUE;
  HANDLE h;

  set_handle (INVALID_HANDLE_VALUE);
  output_handle_ = INVALID_HANDLE_VALUE;

  set_flags (flags);

  /* Open the input handle as handle_ */
  h = CreateFileA ("CONIN$", GENERIC_READ|GENERIC_WRITE, 
                         FILE_SHARE_READ|FILE_SHARE_WRITE, &sa, 
                         OPEN_EXISTING, 0, 0);

  if (h == INVALID_HANDLE_VALUE)
    {
      __seterrno ();
      return 0;
    }
  set_handle (h);

  output_handle_ = CreateFileA ("CONOUT$", GENERIC_READ|GENERIC_WRITE, 
                         FILE_SHARE_READ|FILE_SHARE_WRITE, &sa, 
                         OPEN_EXISTING, 0, 0);

  if (output_handle_ == INVALID_HANDLE_VALUE)
    {
      __seterrno ();
      return 0;
    }

  if (fillin_info ())
    default_color = info.wAttributes;

  debug_printf("opened conin$ = %d, conout$ = %d\n",
                get_input_handle (), get_output_handle ());

  return this;
}

int fhandler_console::close (void)
{
  CloseHandle (get_input_handle ());
  CloseHandle (get_output_handle ());
  output_handle_ = INVALID_HANDLE_VALUE;
  set_handle (INVALID_HANDLE_VALUE);
  return 0;
}

/*
 * Special console dup to duplicate input and output
 * handles.
 */

int
fhandler_console::dup (fhandler_base *child)
{
  fhandler_console *fhc = (fhandler_console *) child;
#ifndef __alpha
  const HANDLE proc = GetCurrentProcess ();
#else
  HANDLE proc = GetCurrentProcess ();
#endif
  HANDLE nh;

  if (! DuplicateHandle (proc, get_output_handle (), proc, &nh,
					0, 1, DUPLICATE_SAME_ACCESS))
    {
      small_printf ("fhandler_console::dup COPY FOR DUP FAILED, handle in %x %x!!\n", 
                      get_output_handle (), GetLastError ());
      __seterrno ();
      return -1;
    }

  fhc->output_handle_ = nh;
  fhc->state_ = state_;

  return fhandler_base::dup (child);
}

int
fhandler_console::ioctl (int cmd, void *buf)
{
  if (cmd == TIOCGWINSZ)
    {
	int st;

        st = fillin_info ();
	if (st)
	  {
	    /* *not* the buffer size, the actual screen size... */
	    /* based on Left Top Right Bottom of srWindow */
	    ((struct winsize *) buf)->ws_row = info.dwWinSize.Y;
	    ((struct winsize *) buf)->ws_col = info.dwWinSize.X;
	    syscall_printf ("WINSZ: (row=%d,col=%d)\n",
			   ((struct winsize *) buf)->ws_row,
			   ((struct winsize *) buf)->ws_col);
	    return 0;
	  }
	else
	  {
	    syscall_printf ("WINSZ failed\n");
	    __seterrno ();
	    return -1;
	  }
	return 0;
      }
    else if (cmd == TIOCSWINSZ)
      return 0;

  return fhandler_base::ioctl (cmd, buf);
}
  
int fhandler_console::linearize (unsigned char *buf)
{
  int len = sizeof (iflag_) + sizeof (lflag_) + 
            sizeof (output_handle_) + sizeof (state_) + 
            sizeof (args_) + sizeof (nargs_) + sizeof (default_color);

  if (buf == 0)
    {
      len += this->fhandler_tty::linearize (buf);
      return len;
    }

  /* Do input state */
  memcpy (buf, (char *) &iflag_, sizeof (iflag_));
  buf += sizeof (iflag_);
  memcpy (buf, (char *) &lflag_, sizeof (lflag_));
  buf += sizeof (lflag_);

  /* Do output state */
  memcpy (buf, (char *) &output_handle_, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy (buf, (char *) &state_, sizeof (state_));
  buf += sizeof (state_);
  memcpy (buf, (char *) &args_, sizeof (args_));
  buf += sizeof (args_);
  memcpy (buf, (char *) &nargs_, sizeof (nargs_));
  buf += sizeof (nargs_);
  memcpy (buf, (char *) &default_color, sizeof (default_color));
  buf += sizeof (default_color);

  len += this->fhandler_tty::linearize (buf);
  return len;
}

fhandler_console::de_linearize (const unsigned char *buf)
{
  const unsigned char *orig_buf = buf;

  /* Do input state */
  memcpy ((char *) &iflag_, buf, sizeof (iflag_));
  buf += sizeof (iflag_);
  memcpy ((char *) &lflag_, buf, sizeof (lflag_));
  buf += sizeof (lflag_);

  /* Do output state */
  memcpy ((char *) &output_handle_, buf, sizeof (output_handle_));
  buf += sizeof (output_handle_);
  memcpy ((char *) &state_, buf, sizeof (state_));
  buf += sizeof (state_);
  memcpy ((char *) &args_, buf, sizeof (args_));
  buf += sizeof (args_);
  memcpy ((char *) &nargs_, buf, sizeof (nargs_));
  buf += sizeof (nargs_);
  memcpy ((char *) &default_color, buf, sizeof (default_color));
  buf += sizeof (default_color);

  int len = buf - orig_buf;
  return (len + this->fhandler_tty::de_linearize (buf));
}

int
fhandler_console::tcflush (int queue)
{
  int res = 0;
  if (queue == TCIFLUSH
      || queue == TCIOFLUSH)
    {
      if (!FlushConsoleInputBuffer (get_input_handle ()))
	{
	  __seterrno ();
	  res = -1;
	}
    }
  return res;
}

int
fhandler_console::output_tcsetattr (int, termios const *t)
{
  /* Ignore the optional_actions stuff, since all output is emitted
     instantly */

  int flags = 0;

  /* Enable/disable LF -> CRLF conversions */
  set_w_binary ((t->c_oflag & ONLCR) ? 0 : 1);   

  /* All the output bits we can ignore */

  flags |= ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT;

  int res = SetConsoleMode (get_output_handle (), flags) ? 0 : -1;
  syscall_printf ("%d = tcsetattr (console) (,%x) (ENABLE FLAGS %x) (lflag %x oflag %x)\n", res, t, flags, t->c_lflag, t->c_oflag);
  return res;  
}

int
fhandler_console::input_tcsetattr (int, termios const *t)
{
  /* Ignore the optional_actions stuff, since all output is emitted
     instantly */

  int flags = 0;

  /* Enable/disable LF -> CRLF conversions */
  set_r_binary ((t->c_iflag & IGNCR) ? 0 : 1);

  /* There's some disparity between what we need and what's
     available.  We've got ECHO and ICANON, they've
     got ENABLE_ECHO_INPUT and ENABLE_LINE_INPUT. */
     
  iflag_ = t->c_iflag;
  lflag_ = t->c_lflag;

  if (t->c_lflag & ECHO)
    {
      flags |= ENABLE_ECHO_INPUT;
    }
  if (t->c_lflag & ICANON)
    {
      flags |= ENABLE_LINE_INPUT;
    }

  if (flags & ENABLE_ECHO_INPUT
      && !(flags & ENABLE_LINE_INPUT))
    {
      /* This is illegal, so turn off the echo here, and fake it
	 when we read the characters */

      flags &= ~ENABLE_ECHO_INPUT;
    }

  if (t->c_lflag & ISIG)
    {
      flags |= ENABLE_PROCESSED_INPUT;
    }
  /* What about ENABLE_WINDOW_INPUT
     and ENABLE_MOUSE_INPUT   ? */

  if (use_tty)
    {
      flags = 0;
      iflag_ = 0;
      lflag_ = 0;
    }
  int res = SetConsoleMode (get_input_handle (), flags) ? 0 : -1;
  if (res < 0)
    __seterrno ();
  syscall_printf ("%d = tcsetattr (console) (,%x) (ENABLE FLAGS %x) (c_lflag %x iflag %x)\n", res, t, flags, t->c_lflag, t->c_iflag);

  return res;  
}

int
fhandler_console::tcsetattr (int a, termios const *t)
{
  int res = output_tcsetattr (a, t);
  if (res != 0)
    return res;
  return input_tcsetattr (a, t);
}
  
int
fhandler_console::tcgetattr (termios *t)
{
  int res;
  memset (t, 0, sizeof (*t));
  
  t->c_ospeed = t->c_ispeed = B38400;
  t->c_cflag |= CS8;

  t->c_iflag |= iflag_;
  t->c_lflag |= lflag_;

#if 0 /* IGNCR doesn't work yet */
  if (!get_r_binary ())
    t->c_iflag |= IGNCR;
#endif
  if (!get_w_binary ())
    t->c_oflag |= ONLCR;

  DWORD flags;

  if (!GetConsoleMode (get_input_handle (), &flags))
    {
      __seterrno ();
      res = -1;
    }
  else
    {
      if (flags & ENABLE_ECHO_INPUT)
	t->c_lflag |= ECHO;

      if (flags & ENABLE_LINE_INPUT)
	t->c_lflag |= ICANON;

      if (flags & ENABLE_PROCESSED_INPUT)
	t->c_iflag |= ISIG;

      /* What about ENABLE_WINDOW_INPUT
	 and ENABLE_MOUSE_INPUT   ? */

      /* All the output bits we can ignore */
      res = 0;
    }
  syscall_printf ("%d = tcgetattr (console) (%x) (win32 ENABLE_ %x) (t->lflag %x) (t->iflag %x)\n", 
                 res, t, flags, t->c_lflag, t->c_iflag);
  return res;  
}

/*
 * Constructor.
 */

fhandler_console::fhandler_console (const char *name) : fhandler_tty (name)
{
  state_ = normal;
  default_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}

/*
 * Clear the screen context from x1/y1 to x2/y2 cell.
 * Negative values represents current screen dimensions
 */
void
fhandler_console::clear_screen (int x1, int y1, int x2, int y2)
{
  COORD tlc;
  DWORD done;
  int num;

  (void)fillin_info ();

  if (x1 < 0)
    x1 = info.dwWinSize.X-1;
  if (y1 < 0)
    y1 = info.winBottom;
  if (x2 < 0)
    x2 = info.dwWinSize.X-1;
  if (y2 < 0)
    y2 = info.winBottom;

  num = abs (y1 - y2) * info.dwWinSize.X + abs (x1 - x2) + 1;

  if ((y2 * info.dwWinSize.X + x2) > (y1 * info.dwWinSize.X + x1))
    {
      tlc.X = x1;
      tlc.Y = y1;
    }
  else
    {
      tlc.X = x2;
      tlc.Y = y2;
    }
  FillConsoleOutputCharacterA (get_output_handle (), ' ',
			       num,
			       tlc,
			       &done);
  FillConsoleOutputAttribute (get_output_handle (), 
                               default_color,
                               num,
                               tlc,
                               &done);
}

void
fhandler_console::cursor_set (BOOL rel_to_top, int x, int y)
{
  COORD pos;

  (void)fillin_info ();
  if (y > info.winBottom) 
    y = info.winBottom;
  else if (y < 0)
    y = 0;
  else if (rel_to_top)
    y += info.winTop;

  if (x > info.dwWinSize.X) 
    x = info.dwWinSize.X - 1;
  else if (x < 0)
    x = 0;

  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition (get_output_handle (), pos);
}

void
fhandler_console::cursor_rel (int x, int y)
{
  fillin_info ();
  x += info.dwCursorPosition.X;
  y += info.dwCursorPosition.Y;
  cursor_set (FALSE, x, y);
}

void
fhandler_console::cursor_get (int *x, int *y)
{
  fillin_info ();
  *y = info.dwCursorPosition.Y;
  *x = info.dwCursorPosition.X;
}

#define BAK 1
#define ESC 2
#define NOR 0
#define IGN 4
#define ERR 5
#define DWN 6
#define BEL 7
#define TAB 8 /* We should't let the console deal with these */
#define CR 13
#define LF 10

static const char base_chars[256] =
{
/*00 01 02 03 04 05 06 07 */ IGN, ERR, ERR, NOR, NOR, NOR, NOR, BEL, 
/*08 09 0A 0B 0C 0D 0E 0F */ BAK, TAB, DWN, ERR, ERR, CR,  ERR, IGN,
/*10 11 12 13 14 15 16 17 */ NOR, NOR, ERR, ERR, ERR, ERR, ERR, ERR, 
/*18 19 1A 1B 1C 1D 1E 1F */ NOR, NOR, ERR, ESC, ERR, ERR, ERR, ERR, 
/*   !  "  #  $  %  &  '  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*(  )  *  +  ,  -  .  /  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*0  1  2  3  4  5  6  7  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*8  9  :  ;  <  =  >  ?  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*@  A  B  C  D  E  F  G  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*H  I  J  K  L  M  N  O  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*P  Q  R  S  T  U  V  W  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*X  Y  Z  [  \  ]  ^  _  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*`  a  b  c  d  e  f  g  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*h  i  j  k  l  m  n  o  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*p  q  r  s  t  u  v  w  */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*x  y  z  {  |  }  ~  7F */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*80 81 82 83 84 85 86 87 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*88 89 8A 8B 8C 8D 8E 8F */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*90 91 92 93 94 95 96 97 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*98 99 9A 9B 9C 9D 9E 9F */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*A0 A1 A2 A3 A4 A5 A6 A7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*A8 A9 AA AB AC AD AE AF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*B0 B1 B2 B3 B4 B5 B6 B7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*B8 B9 BA BB BC BD BE BF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*C0 C1 C2 C3 C4 C5 C6 C7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*C8 C9 CA CB CC CD CE CF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*D0 D1 D2 D3 D4 D5 D6 D7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*D8 D9 DA DB DC DD DE DF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*E0 E1 E2 E3 E4 E5 E6 E7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*E8 E9 EA EB EC ED EE EF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*F0 F1 F2 F3 F4 F5 F6 F7 */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR, 
/*F8 F9 FA FB FC FD FE FF */ NOR, NOR, NOR, NOR, NOR, NOR, NOR, NOR };

/*#define syscall_printf small_printf*/

static int savex, savey; /* for CSI s, CSI u */

void
fhandler_console::char_command (char c)
{
  static int fg = 7, bg = 0, bold = 0;
  int x, y;
  char buf[40];

  switch (c)
    {
    case 'm':   /* Set Graphics Rendition */
       int i;

       for (i = 0; i <= nargs_; i++)
         switch (args_[i])
           {
             case 0:    /* normal color */
               fg = default_color;
               bg = 0;
               bold = 0;
               break;
             case 1:    /* bold */
               fg = default_color;
               bg = 0;
               bold = FOREGROUND_INTENSITY;
               break;
             case 4:    /* underline - simulate with magenta */
               fg = FOREGROUND_BLUE | FOREGROUND_RED;
               bold = FOREGROUND_INTENSITY;
               bg = 0;
               break;
             case 5:
               fg = default_color;
               bg = 0;
               bold = FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
               break;
             case 7:    /* reverse */
               fg = 0;
               bg = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
               bold = 0;
               break;
             case 8:    /* invisible */
               fg = 0;
               bg = 0;
               bold = 0;
               break;
             case 30:        /* BLACK foreground */
               fg = 0;
               break;
             case 31:        /* RED foreground */
               fg = FOREGROUND_RED;
               break;
             case 32:        /* GREEN foreground */
               fg = FOREGROUND_GREEN;
               break;
             case 33:        /* YELLOW foreground */
               fg = FOREGROUND_RED | FOREGROUND_GREEN;
               break;
             case 34:        /* BLUE foreground */
               fg = FOREGROUND_BLUE;
               break;
             case 35:        /* MAGENTA foreground */
               fg = FOREGROUND_RED | FOREGROUND_BLUE;
               break;
             case 36:        /* CYAN foreground */
               fg = FOREGROUND_BLUE | FOREGROUND_GREEN;
               break;
             case 37:    /* WHITE foreg */
               fg = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
               break;
             case 40:        /* BLACK background */
               bg = 0;
               break;
             case 41:        /* RED background */
               bg = BACKGROUND_RED;
               break;
             case 42:        /* GREEN background */
               bg = BACKGROUND_GREEN;
               break;
             case 43:        /* YELLOW background */
               bg = BACKGROUND_RED | BACKGROUND_GREEN;
               break;
             case 44:        /* BLUE background */
               bg = BACKGROUND_BLUE;
               break;
             case 45:        /* MAGENTA background */
               bg = BACKGROUND_RED | BACKGROUND_BLUE;
               break;
             case 46:        /* CYAN background */
               bg = BACKGROUND_BLUE | BACKGROUND_GREEN;
               break;
             case 47:    /* WHITE background */
               bg = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
               break;
             default:
               fg = default_color;
               bg = 0;
               bold = 0;
               break;
           }
         SetConsoleTextAttribute (get_output_handle (), fg | bg | bold);
      break;
    case 'h':
    case 'l':
      /* Ignore */
      break;
    case 'J':
      switch (args_[0])
	{
	case 0:			/* Clear to end of screen */
	  cursor_get (&x, &y);
	  clear_screen (x, y, -1, -1);
	  break;
	case 1:			/* Clear from beginning of screen to cursor */
	  cursor_get (&x, &y);
	  clear_screen (0, 0, x, y);
	  break;
	case 2:			/* Clear screen */
	  clear_screen (0, 0, -1, -1);
	  cursor_set (TRUE, 0,0);
	  break;
	default:
	  goto bad_escape;
	}
      break; 

    case 'A':
      cursor_rel (0, -(args_[0] ? args_[0] : 1));
      break;
    case 'B':
      cursor_rel (0, args_[0] ? args_[0] : 1);
      break;
    case 'C':
      cursor_rel (args_[0] ? args_[0] : 1, 0);
      break;
    case 'D':
      cursor_rel (-(args_[0] ? args_[0] : 1),0);
      break;
    case 'K':
      switch (args_[0])
        {
          case 0:		/* Clear to end of line */
	    cursor_get (&x, &y);
            clear_screen (x, y, -1, y);
            break;
          case 2:		/* Clear line */
	    cursor_get (&x, &y);
            clear_screen (0, y, -1, y);
            break;
          case 1:		/* Clear from bol to cursor */
            cursor_get (&x, &y);
            clear_screen (0, y, x, y);
            break;
          default:
            goto bad_escape;
        }
      break;
    case 'H':
    case 'f':
      cursor_set (TRUE, (args_[1] ? args_[1] : 1) - 1,
			(args_[0] ? args_[0] : 1) - 1);
      break;
    case 'G':   /* hpa - position cursor at column n - 1 */
      cursor_get (&x, &y);
      cursor_set (FALSE, (args_[0] ? args_[0] - 1 : 0), y);
      break;
    case 'd':   /* vpa - position cursor at line n */
      cursor_get (&x, &y);
      cursor_set (TRUE, x, (args_[0] ? args_[0] - 1 : 0));
      break;
    case 's':   /* Save cursor position */
      cursor_get (&savex, &savey);
      break;
    case 'u':   /* Restore cursor position */
      cursor_set (FALSE, savex, savey);
      break;
    case 'I':	/* TAB */
      cursor_get (&x, &y);
      cursor_set (FALSE, 8*(x/8+1), y);
      break;
    case 'L':				/* AL - insert blank lines */
      args_[0] = args_[0] ? args_[0] : 1;
      cursor_get (&x, &y);
      scroll_screen (0, y, -1, -1, 0, y + args_[0]);
      break;
    case 'M':				/* DL - delete lines */
      args_[0] = args_[0] ? args_[0] : 1;
      cursor_get (&x, &y);
      scroll_screen (0, y + args_[0], -1, -1, 0, y);
      break;
    case '@':				/* IC - insert chars */
      args_[0] = args_[0] ? args_[0] : 1;
      cursor_get (&x, &y);
      scroll_screen (x, y, -1, y, x + args_[0], y);
      break;
    case 'P':				/* DC - delete chars */
      args_[0] = args_[0] ? args_[0] : 1;
      cursor_get (&x, &y);
      scroll_screen (x + args_[0], y, -1, y, x, y);
      break;
    case 'S':				/* SF - Scroll forward */
      args_[0] = args_[0] ? args_[0] : 1;
      scroll_screen(0, args_[0], -1, -1, 0, 0);
      break;
    case 'T':				/* SR - Scroll down */
      fillin_info ();
      args_[0] = args_[0] ? args_[0] : 1;
      scroll_screen (0, 0, -1, -1, 0, info.winTop + args_[0]);
      break;
    case 'X':				/* ec - erase chars */
      args_[0] = args_[0] ? args_[0] : 1;
      cursor_get (&x, &y);
      scroll_screen (x + args_[0], y, -1, y, x, y);
      scroll_screen (x, y, -1, y, x + args_[0], y);
      break;
    case 'Z':				/* Back tab */         
      cursor_get (&x, &y);             
      cursor_set (FALSE, ((8 * (x / 8 + 1)) - 8), y); 
      break;                          
    case 'b':				/* Repeat char #1 #2 times */
      while (args_[1]--)
	WriteFile (get_output_handle (), &args_[0], 1, (unsigned int *) &x, 0);
      break;
    case 'c':				/* u9 - Terminal enquire string */
      sprintf (buf, "\033[?6c");
      undo_input (get_input_handle (), buf);
      break;
    case 'n':
      switch (args_[0])
	{
	case 6:				/* u7 - Cursor position request */
	  cursor_get (&x, &y);
	  sprintf (buf, "\033[%d;%dR", x + 1, y + 1);
	  undo_input (get_input_handle (), buf);
	  break;
    default:
	  goto bad_escape;
	}
      break;
    case 'r':				/* Set Scroll region */
      scroll_region.Top = args_[0] ? args_[0] - 1 : 0;
      scroll_region.Bottom = args_[1] ? args_[1] - 1 : -1;
      break;
    case 'g':				/* TAB set/clear */
      break;
    default:
bad_escape:
      small_printf ("Bad escape %d, %d %d (%c)\n", args_[0], args_[1], c, c);
      sleep (1);
      break;
    }
}

const unsigned char *
fhandler_console::write_normal (const unsigned char *src,
				const unsigned char *end)
{
  /* Scan forward to see what a char which needs special treatment */
  DWORD done;
  const unsigned char *found = src;
  while (found < end)
    {
      if (base_chars[*found] != NOR)
	break;
      found++;
    }
  /* Print all the base ones out */
  if (found != src) 
    {
      if (! WriteFile (get_output_handle (), src,  found - src, &done, 0))
	{
	  __seterrno ();
	  return 0;
	}
      src += done;
    }
  if (src < end) 
    {
      int x, y;
      switch (base_chars[*src]) 
	{
	case BEL:
	  Beep (412, 100);
	  break;
	case ESC:
	  state_ = gotesc;
	  break;
	case DWN:		/* WriteFile("\n") always adds CR... */
	  cursor_get (&x, &y);
	  WriteFile (get_output_handle (), "\n", 1, &done, 0);
	  if (get_w_binary ())
	    cursor_rel (x, 0);
          if (y == srBottom && y < info.winBottom)
            {
              scroll_screen (0, srTop + 1, -1, srBottom, 0, srTop);
              cursor_set (FALSE, x, y);
            }
	  break;
	case BAK:
	  cursor_rel (-1, 0);
	  break;
	case IGN:
	  cursor_rel (1, 0);
	  break;
	case CR:
	  WriteFile (get_output_handle (), "\r", 1, &done, 0);
	  break;
        case TAB:
          cursor_get (&x, &y);
          cursor_set (FALSE, 8 * (x / 8 + 1), y);
          break;
	case ERR:
	  small_printf ("Got %d\n", *src);
	  break;
	}
      src ++;
    }
  return src;
}

int
fhandler_console::write (const void *vsrc, size_t len)
{
  /* Run and check for ansi sequences */
  unsigned const char *src = (unsigned char *) vsrc;
  unsigned const char *end = src + len;
  static NO_COPY unsigned rarg;
  static NO_COPY char my_title_buf[TITLESIZE + 1];

  debug_printf ("%x, %d\n", vsrc, len);

  while (src < end)
    {
      debug_printf ("at %d(%c) state is %d\n", *src, isprint (*src) ? *src : ' ', state_);
      switch (state_)
	{
	case normal:
	  src = write_normal (src, end);
          if (src == 0) /* write_normal fail */
            return -1;
	  break;
	case gotesc:
	  if (*src == '[')
	    {
	      state_ = gotsquare;
              for (nargs_ = 0; nargs_ < MAXARGS; nargs_++)
                args_[nargs_] = 0;
              nargs_ = 0;
	    }
	  else if (*src == ']')
	    {
	      rarg = 0;
	      my_title_buf[0] = '\0';
	      state_ = gotrsquare;
	    }
	  else if (*src == 'M')		/* Reverse Index */
	    {
	      fillin_info ();
	      scroll_screen (0, 0, -1, -1, 0, info.winTop + 1);
	      state_ = normal;
	    }
	  else if (*src == 'c')		/* Reset Linux terminal */
	    {
	      clear_screen (0, 0, -1, -1);
	      cursor_set (TRUE, 0, 0);
	      state_ = normal;
	    }
	  else if (*src == '8')		/* Restore cursor position */
	    {
	      cursor_set (FALSE, savex, savey);
	      state_ = normal;
	    }
	  else if (*src == '7')		/* Save cursor position */
	    {
	      cursor_get (&savex, &savey);
	      state_ = normal;
	    }
	  else if (*src == 'R')
	      state_ = normal;
	  else
	    {
	      small_printf ("Bad escape %d (%c)\n", *src,*src);
	      sleep (1);
	      state_ = normal;
	    }
	  src++;
	  break;
	case gotarg1:
	  if (isdigit (*src))
	    {
              args_[nargs_] = args_[nargs_] * 10 + *src - '0';
	      src++;
	    }
	  else if (*src == ';')
	    {
	      src++;
              nargs_++;
              if (nargs_ >= MAXARGS)
                {
                  small_printf ("Too many arguments\n");
                  sleep (1);
                  nargs_--;
	        }
	    }
	  else
	    {
	      state_ = gotcommand;
	    }
	  break;
	case gotcommand:
	  char_command (*src++);
	  state_ = normal;
	  break;
        case gotrsquare:
	  if (isdigit(*src))
	    rarg = rarg * 10 + (*src - '0');
	  else if (*src == ';' && (rarg == 2 || rarg == 0))
	    state_ = gettitle;
	  else
	    state_ = eattitle;
	  src++;
	  break;
	case eattitle:
        case gettitle:
	  {
	    int n = strlen (my_title_buf);
	    if (*src < ' ' || *src >= '\177')
	      {
		if (*src == '\007' && state_ == gettitle)
		  {
		    if (old_title)
		      strcpy (old_title, my_title_buf);
		    set_console_title (my_title_buf);
		  }
		state_ = normal;
	      }
	    else if (n < TITLESIZE)
	      {
		my_title_buf[n++] = *src;
		my_title_buf[n] = '\0';
	      }
	    src++;
	    break;
	  }
	case gotsquare:
	  if (*src == ';') 
	    {
              state_ = gotarg1;
              nargs_++;
	      src++;
	    }
	  else if (isalpha (*src))
	    {
	      state_ = gotcommand;
	    }
	  else if (*src != '@' && !isalpha (*src) && !isdigit (*src))
	    {
	      /* ignore any extra chars between [ and first arg or command */
	      src++;
	    }
	  else 
	    state_ = gotarg1;
	  break;
	}
    }
  syscall_printf ("%d = write_console (,..%d)\n", len, len);
  
  return len;
}

static void
dbg_input_event (INPUT_RECORD *input_rec)
{
  select_printf ("PeekConsoleInput, type 0x%x key: dn %d, st 0x%x\n",
	      input_rec->EventType, 
	      input_rec->Event.KeyEvent.bKeyDown,
	      input_rec->Event.KeyEvent.dwControlKeyState);
  select_printf ("... rpt %d vkc 0x%x vsc 0x%x ascii 0x%x\n",
	      input_rec->Event.KeyEvent.wRepeatCount,
	      input_rec->Event.KeyEvent.wVirtualKeyCode,
	      input_rec->Event.KeyEvent.wVirtualScanCode,
	      input_rec->Event.KeyEvent.AsciiChar);
}

static int
FakeReadFile (HANDLE hndl, void* pv, size_t lenin, unsigned int* done, 
			 OVERLAPPED *ov)
{
  DWORD flags;
  int res;
  int need_chars = 1;
  int copied_chars = 0;
  char *buf;
  res = GetConsoleMode (hndl, &flags);

  debug_printf ("FakeReadFile, res = %d, flags = %x\n", res, flags);

  /* ReadFile(console) fails to read more than 30000 bytes on NT 4.0SP3 :-)
     So, limit number of bytes to read. It's safe enough - will You ever
     enter more than 30000 characters from console at once?-) */
  if (lenin > (size_t)30000)
    lenin = 30000;

  /* if things are special, just do what we used to */
  if ((!res) || (ov != 0))
    {
      return ReadFile (hndl, pv, lenin, done, ov);
    }
  if (flags & ENABLE_LINE_INPUT)
    {
      FlushConsoleInputBuffer (hndl);
      return ReadFile (hndl, pv, lenin, done, ov);
    }

  /* otherwise, do something that works */
  unsigned int num_events = 0, ne2, st;

  st = GetNumberOfConsoleInputEvents (hndl, &num_events);

  debug_printf ("FakeReadFile, GetNumberOfConsoleInputEvents returned = %d\n", st);

  if (!st)
    {
      /* it failed, we're confused */
      return 0;			/* seems to be failure */
    }
  if (num_events == 0)
    {
      select_printf ("gnocie found no events\n");
      /* so are we blocking or what? FIONBIO isn't implemented... */
      /* either spin here and read at least one thing, return none... */
      /* readfile blocks already, so we probably can't do worse... */
      need_chars = 1;
    } 

  INPUT_RECORD input_rec;
  
  buf = (char*) pv;
  while (need_chars || num_events)
    {
      HANDLE waitbuf[2];                                                    
                                                                            
      waitbuf[0] = hndl;                                                    
      waitbuf[1] = signal_arrived;                                       
      switch (WaitForMultipleObjects (use_tty? 1: 2, waitbuf, FALSE, INFINITE))          
        {                                                                     
        case WAIT_OBJECT_0:                     /* key pressed */             
          break;                                                              
        case WAIT_OBJECT_0 + 1:                   /* signal arrived */
	  debug_printf ("FakeReadFile, signal arrived\n");
	  continue;
        default:                                                              
          SetLastError (ERROR_IO_DEVICE); /* Simulate EIO */                   
          return 0;                                                           
        }                                                                     
      st = ReadConsoleInput (hndl, &input_rec, 1, &ne2);
      if (!st)
        {
          /* it failed, we're confused */
          return 0;		/* seems to be failure */
        }
      /* doc says it will return at least one event... */
      if (num_events)
        num_events--;
      /* check if we're just disposing of this one */

      if (input_rec.EventType == WINDOW_BUFFER_SIZE_EVENT && use_tty)
	{
	  _kill (-s->t.gettty (myself->ctty)->getpgid (), SIGWINCH);
          continue;
	}
      if (input_rec.EventType != KEY_EVENT)
        continue;
      if (input_rec.Event.KeyEvent.bKeyDown == 0)
        continue;

      if (input_rec.Event.KeyEvent.AsciiChar == 0)  /* arrow/function keys */
        {
#define NORMAL  0
#define SHIFT	1
#define CONTROL	2
#define ALT	3
	  int index = NORMAL;

	  if (input_rec.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED)
	    index = SHIFT;
	  else if (input_rec.Event.KeyEvent.dwControlKeyState & 
			(LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED))
	    index = CONTROL;
	  else if (input_rec.Event.KeyEvent.dwControlKeyState & 
			(LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
	    index = ALT;

          static struct {
            int vk;
            char *val[4];
          } keytable[] = {
			/* NORMAL */	/* SHIFT */     /* CTRL */      /* ALT */
            VK_LEFT,    "\033[D",	NULL,		NULL,		NULL,
            VK_RIGHT,   "\033[C",	NULL,		NULL,		NULL,
            VK_UP,      "\033[A",	NULL,		NULL,		NULL,
            VK_DOWN,    "\033[B",	NULL,		NULL,		NULL,
            VK_PRIOR,   "\033[5~",	NULL,		NULL,		NULL,
            VK_NEXT,    "\033[6~",	NULL,		NULL,		NULL,
            VK_HOME,    "\033[1~",	NULL,		NULL,		NULL,
            VK_END,     "\033[4~",	NULL,		NULL,		NULL,
            VK_INSERT,  "\033[2~",	NULL,		NULL,		NULL,
            VK_DELETE,  "\033[3~",	NULL,		NULL,		NULL,
            VK_F1,      "\033[[A",	"\033[23~",	NULL,		NULL,
            VK_F2,      "\033[[B",	"\033[24~",	NULL,		NULL,
            VK_F3,      "\033[[C",	"\033[25~",	NULL,		NULL,
            VK_F4,      "\033[[D",	"\033[26~",	NULL,		NULL,
            VK_F5,      "\033[[E",	"\033[28~",	NULL,		NULL,
            VK_F6,      "\033[17~",	"\033[29~",	NULL,		NULL,
            VK_F7,      "\033[18~",	"\033[31~",	NULL,		NULL,
            VK_F8,      "\033[19~",	"\033[32~",	NULL,		NULL,
            VK_F9,      "\033[20~",	"\033[33~",	NULL,		NULL,
            VK_F10,     "\033[21~",	"\033[34~",	NULL,		NULL,
            VK_F11,     "\033[23~",	NULL,		NULL,		NULL,
            VK_F12,     "\033[24~",	NULL,		NULL,		NULL,
	    VK_NUMPAD5, "\033[G",	NULL,		NULL,		NULL,
            0,          "",		NULL,		NULL,		NULL
          };
          char *ptr = NULL;
          int i;

          for (i=0; keytable[i].vk; i++)
            if (input_rec.Event.KeyEvent.wVirtualKeyCode == keytable[i].vk)
              {
                ptr = keytable[i].val[index];
                break;
              }
          if (!ptr)
            continue;
	  while (copied_chars < lenin)
	    if (*ptr)
              buf[copied_chars++] = *ptr++;
	    else
	      break;
	  if (*ptr)
	    undo_input (hndl, ptr);
        }
      else /* keep it */
        {
	  if (input_rec.Event.KeyEvent.dwControlKeyState & LEFT_ALT_PRESSED)
	    {
	      char tmp[2];
	      tmp[0] = tolower (input_rec.Event.KeyEvent.AsciiChar);
	      tmp[1] = 0;
	      buf[copied_chars++] = '\033';
	      if (copied_chars < lenin)
		buf[copied_chars++] = tmp[0];
	      else
	        undo_input (hndl, tmp);
	    }
	  else
            buf[copied_chars++] = input_rec.Event.KeyEvent.AsciiChar;
        }
      if (copied_chars >= lenin)
        {
          /* we got all we could handle */
          num_events = 0;
        }
      need_chars = 0;
    }
  *done = copied_chars;
  return 1;			/* success == true */
}

int
fhandler_console::read (void *pv, size_t lenin)
{
  char *buf = (char *) pv;
  int res;
  DWORD done;
  
  DWORD flags;
  res = GetConsoleMode (get_input_handle (), &flags);
  syscall_printf ("(flags (%d)->%d/0x%x)\n", 
		    get_handle (), res, flags);

  unsigned int num_events = 0, ne2;
  if (GetNumberOfConsoleInputEvents (get_input_handle (), &num_events))
    {
      if (num_events == 0)
	{
	  select_printf ("gnocie found no events\n");
	}
      else
	{
	  INPUT_RECORD input_rec[128];
	  select_printf ("GetNumberOfConsoleInputEvents->%d\n", num_events);

	  if (PeekConsoleInput (get_input_handle (), input_rec, 128, &ne2))
	    {
	      int i;
	      select_printf ("PeekConsoleInput got %d records\n", ne2);
	      for (i = 0; i < ne2; i++)
		  {
		    dbg_input_event (input_rec+i);
		  }	
	    }
	}
    }

  syscall_printf ("read console, r_binary %d\n", get_r_binary ());
  syscall_printf ("args %x %x %x %x %d\n",
		 get_handle (), pv, lenin, &done, 0);
  syscall_printf ("Console handle is %d\n", get_input_handle ());

again:
  if (!FakeReadFile (get_input_handle (), pv, lenin, &done, 0))
    {
      syscall_printf ("rf fail\n");
      __seterrno ();
      res = -1;
    }
  else 
    {
      int len = done;
      DWORD flags;

      GetConsoleMode (get_input_handle (), &flags);
      syscall_printf ("readfile returned - len %d (flags 0x%x)\n", len, flags);
      if (! (flags &ENABLE_LINE_INPUT))
	{
	  /* There are nulls in the stream with this ??!! */
	  char *dst = (char *) pv;
	  
	  char *src = (char *) pv;
	  for (int j = 0; j < len; j++)
	    {
	      char c = *src++;
	      if (c == '\024' && strace() & _STRACE_CACHE)
		{
		  sig_send(NULL, __SIGSTRACE);
		  if (len == 1)
		    goto again;
		  continue;
		}
	      if (c)
		*dst++ = c;
	    }
	  len = (char *) dst - (char *) pv;
	}
      
      syscall_printf ("rf fail 1\n");
      /* Do magic transforms */
      
      for (int j = 0; j < len; j++)
	{
	  syscall_printf ("in %d %d\n", j, buf[j]);
	}

      syscall_printf ("rf fail 2\n");

     /* The console will always return CRLF for LF, and we don't want
         the CR.  !!This should be done as a ReadConsoleInput loop one day */

      /* if (igncr_enabled ()) -- WRONG CASE... */
      if (flags & ENABLE_LINE_INPUT)
	{
	  char *src = buf;
	  char *dst = buf;
          syscall_printf ("rf fail 5 %d\n", len);

	  for (int i = 0; i < len ; i++)
	    {
	      if (*src == '\024' && strace() & _STRACE_CACHE)
		{
		  sig_send(NULL, __SIGSTRACE);
		  if (len == 1)
		    goto again;
		  continue;
		}
	      /* only make CRNL -> NL, don't just nuke CR! */
	      if (*src != '\r')
		*dst++ = *src;
	      else if ((i < len) && (src[1] != '\n'))
		*dst++ = *src;
	      src++;
	    }
	  len = dst - buf;
          syscall_printf ("rf fail len set to  %d\n", len);
	}

      if (iflag_ & ICRNL)
	{
	  /* Turn CR into NL */
	  for (int i = 0; i < len; i++)
	    {
	      if (buf[i] == '\r')
		buf[i] = '\n';
	    }
	}

      syscall_printf ("rf fail 3\n");
      if (iflag_ & INLCR)
	{
	  /* Turn NL into CR */
	  for (int i = 0; i < len; i++)
	    {
	      if (buf[i] == '\n')
		buf[i] = '\r';
	    }
	}
      
      syscall_printf ("rf fail 5\n");
      if (iflag_ & IUCLC)
	{
	  /* Uppercase to lowercase */
	  for (int i = 0; i < len; i++)
	    {
	      if (isupper (buf[i]))
		buf[i] = tolower (buf[i]);
	    }
	}
      res = len;
    }

  if (res > 0) 
    {
      for (int j = 0; j < res; j++)
	syscall_printf ("read %d %c\n", j, buf[j]);  
      
      if (lflag_ & ECHO
	  && !(lflag_ & ICANON))
	{
	  WriteFile (get_output_handle (), pv, res, &done, 0);
	}
    }
  
  syscall_printf ("%d = read (console) (%x, %d);\n", res, pv, lenin);
  return res;
}

void
fhandler_console::init (HANDLE f, int bin, int a, const char *n)
{
  termios t;
  fhandler_tty::init (f, bin, a, n);
  
  /* Ensure both input and output console handles are open */
  int mode;
                                               
  a &= GENERIC_READ | GENERIC_WRITE;
  if (a == GENERIC_READ)
    mode = O_RDONLY;
  if (a == GENERIC_WRITE)
    mode = O_WRONLY;
  if (a == (GENERIC_READ | GENERIC_WRITE))
    mode = O_RDWR;
  open (0, mode);

  /* IGNCR doesn't work yet */
  t.c_iflag = ICRNL /* | IGNCR */;
  t.c_oflag = bin ? 0 : ONLCR;
  t.c_lflag = ECHO | ICANON | ISIG;
  tcsetattr (0, &t);
}

int
fhandler_console::igncr_enabled (void)
{
  return iflag_ & IGNCR;
}

void
set_console_title (char *title)
{
  int rc;
  char buf[257];
  strncpy(buf, title, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  if ((rc = WaitForSingleObject (title_mutex, 15000)) != WAIT_OBJECT_0)
    sigproc_printf ("wait for title mutex failed rc %d, err %d\n",
		    rc, GetLastError ());
  SetConsoleTitle (buf);
  ReleaseMutex (title_mutex);
  debug_printf ("title '%s'\n", buf);
}
