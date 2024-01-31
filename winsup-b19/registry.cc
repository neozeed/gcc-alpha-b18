/* registry.cc: registry interface

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "registry.h"

reg_session::reg_session (HKEY key, REGSAM access)
{
  majorkey_.init ("SOFTWARE", key, access);
  minorkey_.init ("Cygnus Solutions", majorkey_.get_key (), access);
  versionkey_.init ("CYGWIN.DLL setup", minorkey_.get_key (), access);
  vminorkey_.init (CYGWIN_REGISTRY_VERSION, versionkey_.get_key (), access);
}

reg_key &
reg_session::get_key ()
{
  return vminorkey_;
}

reg_session::~reg_session ()
{
}

void
reg_key::init (const char *name, HKEY r, REGSAM access)
{
  DWORD disp;
  int res = RegCreateKeyExA (r,
			     name,
			     0,
			     "cygnus",
			     REG_OPTION_NON_VOLATILE,
			     access,
			     0,
			     &key_,
			     &disp);

  if (res != ERROR_SUCCESS) 
    {
      key_ = (HKEY)INVALID_HANDLE_VALUE;
      strace_printf ("Failed to create key %s in the registry\n", name);
    }
}

int
reg_key::open(const char *name, HKEY r, REGSAM access)
{
  int res = (int)RegOpenKeyExA(r,
			  name,
			  0,
			  access,
			  &key_);
  if(res != ERROR_SUCCESS)
    {
      key_ = (HKEY)INVALID_HANDLE_VALUE;
    }
  return res;
}

int
reg_key::get_int (const char *name, int def)
{
  DWORD type;
  DWORD dst;
  DWORD size = sizeof (dst);

  LONG res = RegQueryValueExA (key_, 
			       name,
			       0, 
			       &type,
			       (unsigned char *)&dst, &size);

  if (type != REG_DWORD || res != ERROR_SUCCESS)
    {
      return def;
    }
  return dst;
}

int
reg_key::set_int (const char *name, int val)
{
  DWORD value = val;
  return (int)RegSetValueExA (key_, 
		  name,
		  0, REG_DWORD,(unsigned char *)  &value,  sizeof (value));
}

int
reg_key::get_string (const char *name, char *dst, size_t max, const char * def)
{
  DWORD size = max;
  DWORD type;
  LONG res = RegQueryValueExA (key_, name, 0, &type, (unsigned char *) dst,
								&size);

  if ((def != 0) && ((type != REG_SZ) || (res != ERROR_SUCCESS)))
    {
      strcpy (dst, def);
    }
  return (int)res;
}

int
reg_key::set_string (const char *name, const char *src)
{
  return (int)RegSetValueExA (key_,name, 0, REG_SZ, (unsigned char*) src,
		  strlen (src)+1);
}

int
reg_key::setone_string (const char *src, const char *name)
{
  return (int) RegSetValueExA (key_, name, 0, REG_SZ,
				(const unsigned char *) src, strlen (src)+1);
}

reg_key::reg_key () 
{
  key_ = (HKEY)INVALID_HANDLE_VALUE;
}

HKEY
reg_key::get_key ()
{
  return key_;
}

reg_key::reg_key (reg_key &parent, const char *name, REGSAM access)
{
  init (name, parent.get_key (), access);
}

void
reg_key::kill (const char *name)
{
  RegDeleteKeyA(key_, name);
}

void
reg_key::close()
{
  if (key_ != (HKEY)INVALID_HANDLE_VALUE)
    RegCloseKey (key_);
  key_ = (HKEY)INVALID_HANDLE_VALUE;
}

reg_key::~reg_key ()
{
  close();
}
