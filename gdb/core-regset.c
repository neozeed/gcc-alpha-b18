/* Machine independent GDB support for core files on systems using "regsets".
   Copyright 1993-1996 Free Software Foundation, Inc.

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


/*			N  O  T  E  S

This file is used by most systems that implement /proc.  For these systems,
the general registers are laid out the same way in both the core file and
the gregset_p structure.  The current exception to this is Irix-4.*, where
the gregset_p structure is split up into two pieces in the core file.

The general register and floating point register sets are manipulated by
separate ioctl's.  This file makes the assumption that if FP0_REGNUM is
defined, then support for the floating point register set is desired,
regardless of whether or not the actual target has floating point hardware.

 */

#include "defs.h"

#include <time.h>
#ifdef HAVE_SYS_PROCFS_H
#include <sys/procfs.h>
#endif
#include <fcntl.h>
#include <errno.h>
#include "gdb_string.h"

#include "inferior.h"
#include "target.h"
#include "command.h"
#include "gdbcore.h"

static void fetch_core_registers PARAMS ((char *, unsigned, int, CORE_ADDR));

/*

GLOBAL FUNCTION

	fetch_core_registers -- fetch current registers from core file

SYNOPSIS

	void fetch_core_registers (char *core_reg_sect,
					  unsigned core_reg_size,
					  int which, CORE_ADDR reg_addr)

DESCRIPTION

	Read the values of either the general register set (WHICH equals 0)
	or the floating point register set (WHICH equals 2) from the core
	file data (pointed to by CORE_REG_SECT), and update gdb's idea of
	their current values.  The CORE_REG_SIZE parameter is ignored.

NOTES

	Use the indicated sizes to validate the gregset and fpregset
	structures.
*/

static void
fetch_core_registers (core_reg_sect, core_reg_size, which, reg_addr)
     char *core_reg_sect;
     unsigned core_reg_size;
     int which;
     CORE_ADDR reg_addr;	/* Unused in this version */
{
#if defined (HAVE_GREGSET_T) && defined (HAVE_FPREGSET_T)
  gregset_t gregset;
  fpregset_t fpregset;

  if (which == 0)
    {
      if (core_reg_size != sizeof (gregset))
	{
	  warning ("wrong size gregset struct in core file");
	}
      else
	{
	  memcpy ((char *) &gregset, core_reg_sect, sizeof (gregset));
	  supply_gregset (&gregset);
	}
    }
  else if (which == 2)
    {
      if (core_reg_size != sizeof (fpregset))
	{
	  warning ("wrong size fpregset struct in core file");
	}
      else
	{
	  memcpy ((char *) &fpregset, core_reg_sect, sizeof (fpregset));
#if defined (FP0_REGNUM)
	  supply_fpregset (&fpregset);
#endif
	}
    }
#endif	/* defined(HAVE_GREGSET_T) && defined (HAVE_FPREGSET_T) */
}


/* Register that we are able to handle ELF file formats using standard
   procfs "regset" structures.  */

static struct core_fns regset_core_fns =
{
  bfd_target_elf_flavour,
  fetch_core_registers,
  NULL
};

void
_initialize_core_regset ()
{
  add_core_fns (&regset_core_fns);
}
