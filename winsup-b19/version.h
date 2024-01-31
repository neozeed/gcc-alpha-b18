/* version.h -- Cygwin32 version numbers

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

/* Cygwin32 version numbers and accompanying documentation: */

/* Increment the major number when a change to the dll invalidates existing
   executables.  This can happen for a number of reasons, including when
   functions are removed from the export list of the dll.  Increment the
   minor number when a change is made that you want to record, but that
   doesn't invalidate existing executables.  Both numbers are recorded in
   the executable and in the dll.

   Think of these numbers as being akin to the version numbers of
   /usr/lib/libc.so.* on SunOS.  SunOS 4.1.3_U1 uses
   /usr/lib/libc.so.1.9.2.  Eventually, there should also be a version
   number for the entire system.  For now, the major/minor number will
   have to suffice.

   Note that there is also the issue of having multiple versions of the
   dll using shared data among many applications.  There is not a version
   number associated with incompatible changes in the shared memory space.
   Instead, we embed a timestamp into the names of the shared memory spaces
   so different builds of the dll running simultaneously will not attempt
   to use the same shared memory.

   For historical reasons, the major number started at 16 because the
   "b15" gnu-win32 release of the compiler tools was out when this file
   was created. */

#define CYGWIN_DLL_VERSION_MAJOR 19
#define CYGWIN_DLL_VERSION_MINOR 1

/* Another important version number is the one that is tied to cygwin's
   interface to the Win32 registry.  This string is used to fetch
   registry values and should be changed whenever incompatible changes
   in registry usage are made.
   
   FIXME: Perhaps this value should be tied to the "system's" version
   number.  Or perhaps there should be code to copy an old version numbered
   entry to the latest one if the latest one isn't found. */

#define CYGWIN_REGISTRY_VERSION "b15.0"
