/* window.cc: hidden windows for signals/itimer support

   Copyright 1997, 1998 Cygnus Solutions.

   Written by Sergey Okhapkin <sos@prospect.com.ru>

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/time.h>
#include <stdlib.h>
#include "winsup.h"

static NO_COPY UINT timer_active = 0;
static NO_COPY struct itimerval itv;
static NO_COPY DWORD start_time;
static NO_COPY HWND ourhwnd = NULL;

static NO_COPY UINT Vtimer_active = 0;
static NO_COPY struct itimerval Vitv;
static NO_COPY DWORD Vstart_time;

static LRESULT CALLBACK
WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  _strace_wm (uMsg, wParam, lParam);
  switch (uMsg)
    {
    case WM_PAINT: 
      return 0; 
    case WM_DESTROY:
      PostQuitMessage (0);
      return 0;
    case WM_TIMER:
      if (wParam == timer_active)
	{
	  UINT elapse = itv.it_interval.tv_sec * 1000 + 
			itv.it_interval.tv_usec / 1000;
	  if (elapse)
	    {
	      timer_active = SetTimer (hwnd, 1, elapse, NULL);
	      start_time = GetTickCount ();
	      itv.it_value = itv.it_interval;
	    }
	  else
	    {
	      KillTimer (hwnd, timer_active);
	      timer_active = 0;
	    }
	  raise(SIGALRM);
	}
	if (wParam == Vtimer_active)
	{
	  UINT elapse = Vitv.it_interval.tv_sec * 1000 + 
			Vitv.it_interval.tv_usec / 1000;
	  if (elapse)
	    {
	      Vtimer_active = SetTimer (hwnd, 1, elapse, NULL);
	      Vstart_time = GetTickCount ();
	      Vitv.it_value = Vitv.it_interval;
	    }
	  else
	    {
	      KillTimer (hwnd, Vtimer_active);
	      Vtimer_active = 0;
	    }
	  raise(SIGVTALRM);
	}
      return 0;
    case WM_ASYNCIO:
      raise (SIGIO);
      return 0;
    default: 
      return DefWindowProc (hwnd, uMsg, wParam, lParam); 
    } 
} 
 
static HANDLE window_started;

static DWORD
Winmain (VOID *arg)
{ 
  MSG msg; 
  WNDCLASS wc; 
  static char classname[] = "Cygwin32WndClass";

  /* Register the window class for the main window. */ 
 
  wc.style = 0;
  wc.lpfnWndProc = (WNDPROC) WndProc; 
  wc.cbClsExtra = 0; 
  wc.cbWndExtra = 0; 
  wc.hInstance = u->hmodule;
  wc.hIcon = NULL; 
  wc.hCursor = NULL; 
  wc.hbrBackground = NULL; 
  wc.lpszMenuName = NULL; 
  wc.lpszClassName = classname; 
 
  if (!RegisterClass (&wc))
    {
      system_printf ("Cannot register window class\n");
      return FALSE;
    }
 
  /* Create hidden window. */ 
  ourhwnd = CreateWindow (classname, classname, 
	WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 
	CW_USEDEFAULT, CW_USEDEFAULT, (HWND) NULL, 
	(HMENU) NULL, u->hmodule, (LPVOID) NULL); 
 
  SetEvent (window_started);

  if (!ourhwnd) 
    {
      system_printf ("Cannot create window\n");
      return FALSE;
    }

  /* Start the message loop. */ 
 
  while (GetMessage (&msg, ourhwnd, 0, 0) == TRUE)
    {
      DispatchMessage (&msg); 
    } 
 
  return msg.wParam; 
} 
 
HANDLE
gethwnd ()
{

  if (ourhwnd != NULL)
    return ourhwnd;

  DWORD tid;
  HANDLE hThread;

  window_started = CreateEvent (NULL, TRUE, FALSE, NULL);
  hThread = CreateThread (NULL, 0, Winmain, NULL, 0, &tid);
  if (!hThread)
    {
      system_printf ("Cannot start window thread\n");
    }
  else
    {
      SetThreadPriority (hThread, THREAD_PRIORITY_HIGHEST);
      CloseHandle (hThread);
    }
  WaitForSingleObject (window_started, INFINITE);
  CloseHandle (window_started);
  return ourhwnd;
}

void
window_terminate ()
{
  if (ourhwnd)
    SendMessage (ourhwnd, WM_DESTROY, 0, 0);
}

extern "C"
int
setitimer (int which, const struct itimerval *value, struct itimerval *oldvalue)
{
  UINT elapse;

  if (which != ITIMER_REAL || which != ITIMER_VIRTUAL)
    {
      set_errno (EINVAL);
      return -1;
    }
 if (which == ITIMER_REAL) {
  if (timer_active)
    {
      KillTimer (gethwnd(), timer_active);
      timer_active = 0;
    }
  if (oldvalue)
    *oldvalue = itv;
  if (value == NULL)
    {
      set_errno (EFAULT);
      return -1;
    }
  itv = *value;
  elapse = itv.it_value.tv_sec * 1000 + itv.it_value.tv_usec / 1000;
  if (elapse == 0)
    return 0;
  if (!(timer_active = SetTimer (gethwnd(), 1, elapse, NULL)))
    {
      __seterrno ();
      return -1;
    }
  start_time = GetTickCount ();
  return 0;
 }
 else {
  if (Vtimer_active)
    {
      KillTimer (gethwnd(), Vtimer_active);
      Vtimer_active = 0;
    }
  if (oldvalue)
    *oldvalue = Vitv;
  if (value == NULL)
    {
      set_errno (EFAULT);
      return -1;
    }
  Vitv = *value;
  elapse = Vitv.it_value.tv_sec * 1000 + Vitv.it_value.tv_usec / 1000;
  if (elapse == 0)
    return 0;
  if (!(Vtimer_active = SetTimer (gethwnd(), 1, elapse, NULL)))
    {
      __seterrno ();
      return -1;
    }
  Vstart_time = GetTickCount ();
  return 0;
 } 
}

extern "C"
int 
getitimer (int which, struct itimerval *value)
{
  UINT elapse, val;

  if (which != ITIMER_REAL || which != ITIMER_VIRTUAL)
    {
      set_errno (EINVAL);
      return -1;
    }
  if (value == NULL)
    {
      set_errno (EFAULT);
      return -1;
    }
if (which == ITIMER_REAL) { 
  *value = itv;
  if (!timer_active)
    {
      value->it_value.tv_sec = 0;
      value->it_value.tv_usec = 0;
      return 0;
    }
  elapse = GetTickCount () - start_time;
  val = itv.it_value.tv_sec * 1000 + itv.it_value.tv_usec / 1000;
  val -= elapse;
  value->it_value.tv_sec = val/1000;
  value->it_value.tv_usec = val%1000;
}
else {
  *value = Vitv;
  if (!Vtimer_active)
    {
      value->it_value.tv_sec = 0;
      value->it_value.tv_usec = 0;
      return 0;
    }
  elapse = GetTickCount () - Vstart_time;
  val = Vitv.it_value.tv_sec * 1000 + Vitv.it_value.tv_usec / 1000;
  val -= elapse;
  value->it_value.tv_sec = val/1000;
  value->it_value.tv_usec = val%1000;
}
  return 0;
}

extern "C"
unsigned int
alarm (unsigned int seconds)
{
  int ret;
  struct itimerval newt, oldt;
  
  getitimer (ITIMER_REAL, &oldt);

  newt.it_value.tv_sec = seconds;
  newt.it_value.tv_usec = 0;
  newt.it_interval.tv_sec = 0;
  newt.it_interval.tv_usec = 0;
  setitimer (ITIMER_REAL, &newt, NULL);
  ret = oldt.it_value.tv_sec;
  if (ret == 0 && oldt.it_value.tv_usec)
    ret = 1;
  return ret;
}
