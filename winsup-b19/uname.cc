/* uname.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.
   Written by Steve Chamberlain of Cygnus Support, sac@cygnus.com
   Rewritten by Geoffrey Noer of Cygnus Solutions, noer@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdio.h>
#include <sys/utsname.h>
#include "winsup.h"

/* uname: POSIX 4.4.1.1 */
extern "C"
int
uname (struct utsname *name)
{
  DWORD len, version;
  SYSTEM_INFO sysinfo;
  os_type our_os;

  GetSystemInfo (&sysinfo);

  /* name of computer */
  memset (name, 0, sizeof (*name));
  len = sizeof (name->nodename) - 1;
  GetComputerNameA (name->nodename, &len);

  /* operating system type */
  our_os = get_os_type ();

  switch (our_os)
    {
      case winNT:
        strcpy (name->sysname, "CYGWIN32_NT");
        break;
      case win95:
        strcpy (name->sysname, "CYGWIN32_95");
        break;
      default:
        strcpy (name->sysname, "CYGWIN32_Unsupported");
        break;
    }

  /* operating system revision */
  version = GetVersion ();
  sprintf (name->release, "%d.%d", version & 255, (version >> 8) & 255);

  /* Cygwin32 dll revision */
  sprintf (name->version, "%d.%d",
	   CYGWIN_DLL_VERSION_MAJOR, CYGWIN_DLL_VERSION_MINOR);

  /* CPU type */
  switch (sysinfo.u.s.wProcessorArchitecture)
    {
      case PROCESSOR_ARCHITECTURE_INTEL:
        /* But which of the x86 chips are we? */
        /* Default to i386 if the specific chip cannot be determined */
        switch (our_os)
          {
            case win95:
              /* dwProcessorType only valid in Windows 95 */
              if ((sysinfo.dwProcessorType == PROCESSOR_INTEL_386) ||
                  (sysinfo.dwProcessorType == PROCESSOR_INTEL_486) ||
                  (sysinfo.dwProcessorType == PROCESSOR_INTEL_PENTIUM))
                sprintf (name->machine, "i%d", sysinfo.dwProcessorType);
              else
                strcpy (name->machine, "i386");
              break;
            case winNT:
              /* wProcessorLevel only valid in Windows NT */
              sprintf (name->machine, "i%d86", sysinfo.wProcessorLevel);
              break;
            default:
              strcpy (name->machine, "i386");
              break;
          }
        break;
      case PROCESSOR_ARCHITECTURE_PPC:
        strcpy (name->machine, "ppc");
        break;
      case PROCESSOR_ARCHITECTURE_ALPHA:
        strcpy (name->machine, "alpha");
        break;
      case PROCESSOR_ARCHITECTURE_MIPS:
        strcpy (name->machine, "mips");
        break;
      default:
        sprintf (name->machine, "unknown");
        break;
    }

  return 0;
}
