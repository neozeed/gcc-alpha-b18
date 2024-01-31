/* init.cc for WIN32.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include "winsup.h"

extern "C" 
{
  int WINAPI dll_entry (HANDLE h, DWORD reason, void *ptr);
};

DWORD NO_COPY waitq_storage;
char cygwin_dll_id[MAX_PATH];

void
set_dllname (HANDLE h)
{
  char *p, *fn;
  char buf[MAX_PATH];
  extern char cygwin_dlldate[];

  if (!cygwin_dll_id[0] &&
      !GetModuleFileName(h, buf, sizeof (cygwin_dll_id) - 1))
    fn = strcpy (buf, "cygwin");
  else if ((p = strrchr (buf, '\\')) != NULL)
    fn = p + 1;
  else
    fn = buf;

  if ((p = strrchr (fn, '.')) != NULL)
    *p = '\0';
  __small_sprintf (cygwin_dll_id, "%s.%s", fn, cygwin_dlldate);
}

int
WINAPI dll_entry (HANDLE hdll, DWORD reason, void *)
{
  waitq *w;
  switch (reason) 
    {
    case DLL_PROCESS_ATTACH:
      char *p;
      waitq_storage = TlsAlloc ();
      set_dllname (hdll);
      break;
    case DLL_THREAD_ATTACH:
      if ((w = (waitq *) TlsGetValue (waitq_storage)) == NULL)
	break;
      memset (w, 0, sizeof *w); // This is sometimes preserved following
	 		        // a fork in Windows 95
      system_printf ("dll_entry: cleared waitq_storage\n");
      break;
    case DLL_PROCESS_DETACH:
      break;
    case DLL_THREAD_DETACH:
      if ((w = (waitq *) TlsGetValue (waitq_storage)) == NULL)
	break;
      if (w->thread_ev != NULL)
	{
	  system_printf ("dll_entry: closing %p\n", w->thread_ev);
	  (void) CloseHandle (w->thread_ev);
	}
      memset (w, 0, sizeof(*w));
      break;
    }
  return 1;
}
