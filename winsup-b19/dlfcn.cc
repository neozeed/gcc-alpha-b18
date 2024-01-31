/* dlfcn.cc

   Copyright 1998 Cygnus Solutions

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "dlfcn.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dll_init.h"

static int _dl_error = 0;
static char _dl_buffer[256];

static void
set_dl_error (const char *s)
{
  sprintf (_dl_buffer, "%s: Win32 Error #%d", s, GetLastError ());
  _dl_error = 1;
}

static const char *
checkAccess (const char *dir, const char *name)
{
  static char buf[MAXPATHLEN];
  const char *ret = 0;
  
  buf[0] = 0;
  strcpy (buf, dir);
  strcat (buf, "\\");
  strcat (buf, name);

  if (!access (buf, F_OK))
    ret = buf;
  return ret;
}

static const char *
checkPathAccess (const char *path, const char *name)
{
  static char buf[MAXPATHLEN];
  const char *ret = 0;

  int len = strlen (path);
  int start = 0;
  int i;

  for (i = 0; i < len && !ret; i++)
  {
    if (path[i] == ':')
    {
      strncpy (buf, path+start, i-start);
      buf[i-start] = 0;
      start = i + 1;
      ret = checkAccess (buf, name);
    }
  }

  if (!ret)
  {
    // process the last
    strncpy (buf, path+start, i - start);
    buf[i-start] = 0;
    ret = checkAccess (buf, name);
  }
  return ret;
}

// this function simulates the same search as LoadLibary
// + check environment variable LD_LIBRARY_PATH
static const char *
getFullPathOfDll (const char* str)
{
  if (str == 0)
    return str;
  
  static const char *ret = 0;
  char buf[MAXPATHLEN];
  char name[MAXPATHLEN];

  // add extension if necessary
  strcpy (name, str);
  int len = strlen (str);

  // empty string?
  if (len == 0)
    return str;
  
  // trailing "." => no extension
  if (str[len - 1] == '.')
    name[len - 1] = 0;
  else // then check if it ends with .xxx
  {
    if (len < 4 || str[len - 4] != '.' )
      strcat (name, ".dll");
  }
  
  // first check if leading "/" or "\"
  if (name[0] == '/' || name[0] == '\\')
    ret = name;
  
  // directory from which the application loaded
  if (!ret)
  {
  }

  // current directory
  if (!ret)
  {
    if (GetCurrentDirectory (MAXPATHLEN, buf) == 0)
      small_printf ("WARNING: getFullPathOfDll can't get current directory win32 error %d\n", GetLastError ());
    else
      ret = checkAccess (buf, name);
  }

  // LD_LIBRARY_PATH
  if (!ret)
  {
    char *path = getenv ("LD_LIBRARY_PATH");
    if (path)
      ret = checkPathAccess (path, name);
  }

  if (!ret)
  {
    // system directory
    if (GetSystemDirectory (buf, MAXPATHLEN) == 0)
      small_printf ("WARNING: getFullPathOfDll can't get system directory win32 error %d\n", GetLastError ());
    else
      ret = checkAccess (buf, name);
  }

  // 16 bits system directory
  if (!ret && (get_os_type () == winNT))
  {
    // we assume last dir was xxxxx\SYSTEM32, so we remove 32
    int len = strlen (buf);
    buf[len - 2] = 0;
    ret = checkAccess (buf, name);
  }

  // windows directory
  if (!ret)
  {
    if (GetWindowsDirectory (buf, MAXPATHLEN) == 0)
      small_printf ("WARNING: getFullPathOfDll can't get Windows directory win32 error %d\n", GetLastError ());
    else
      ret = checkAccess (buf, name);
  }

  // PATH
  if (!ret)
  {
    char *path = getenv ("PATH");
    if (path)
      ret = checkPathAccess (path, name);
  }

  return ret;
}

void *
dlopen (const char *name, int)
{
  const char *fullpath = getFullPathOfDll (name);
  DllList::the().currentDlOpenedLib (fullpath);
  void *ret = (void *) LoadLibrary (fullpath);
  if (!ret)
    set_dl_error ("dlopen");
  debug_printf ("ret = %x\n", ret);
  return ret;
}

void *
dlsym (void *handle, const char *name)
{
  void *ret = (void *) GetProcAddress (handle, name);
  if (!ret)
    set_dl_error ("dlsym");
  debug_printf ("ret = %x\n", ret);
  return ret;
}

int
dlclose (void *handle)
{
  int ret = -1;
  if (FreeLibrary (handle))
    ret = 0;
  if (ret)
    set_dl_error ("dlclose");
  return ret;
}

char *
dlerror ()
{
  char *ret = 0;
  if (_dl_error)
    ret = _dl_buffer;
  return ret;
}
