/* Low level Alpha interface, for GDB when running native.
   Copyright 1993, 1995, 1996 Free Software Foundation, Inc.

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

#include "defs.h"
#include "inferior.h"
#include "gdbcore.h"
#include "target.h"
#include "frame.h"

/* See procfs.c and *opennt*.h in config/[alpha,i386] */
CORE_ADDR tramp_start;
CORE_ADDR tramp_end;
CORE_ADDR null_start;
CORE_ADDR null_end;

/* Figure out where the longjmp will land.
   We expect the first arg to be a pointer to the jmp_buf structure from which
   we extract the pc that we will land at.  The pc is copied into PC.
   This routine returns true on success. */

#include <setjmp.h>

int
get_longjmp_target (pc)
     CORE_ADDR *pc;
{
  CORE_ADDR jb_addr;
  char raw_buffer[MAX_REGISTER_RAW_SIZE];

  jb_addr = read_register(A0_REGNUM);

  if (target_read_memory(jb_addr + offsetof(_JUMP_BUFFER,Fir), raw_buffer,
			 sizeof(CORE_ADDR)))
    return 0;

  *pc = extract_address (raw_buffer, sizeof(CORE_ADDR));
  return 1;
}

#ifdef USE_PROC_FS
#include <sys/procfs.h>

/*
 * See the comment in m68k-tdep.c regarding the utility of these functions.
 */

void 
supply_gregset (gregsetp)
     gregset_t *gregsetp;
{
  register int regi;
  register u_quad_t *regp = gregsetp->gregs;
  static char zerobuf[MAX_REGISTER_RAW_SIZE] = {0};

  for (regi = 0; regi < 31; regi++)
    supply_register (regi, (char *)(regp + regi));

  supply_register (PC_REGNUM, (char *)(&gregsetp->fir));

  /* Fill inaccessible registers with zero.  */
  supply_register (ZERO_REGNUM, zerobuf);
  supply_register (FP_REGNUM, zerobuf);
}

void
fill_gregset (gregsetp, regno)
     gregset_t *gregsetp;
     int regno;
{
  int regi;
  register u_quad_t *regp = gregsetp->gregs;

  for (regi = 0; regi < 31; regi++)
    if ((regno == -1) || (regno == regi))
      *(regp + regi) = *(u_quad_t *) &registers[REGISTER_BYTE (regi)];

  if ((regno == -1) || (regno == PC_REGNUM))
    gregsetp->fir = *(u_quad_t *) &registers[REGISTER_BYTE (PC_REGNUM)];
}

/*
 * Now we do the same thing for floating-point registers.
 * Again, see the comments in m68k-tdep.c.
 */

void
supply_fpregset (fpregsetp)
     fpregset_t *fpregsetp;
{
  register int regi;
  register u_quad_t *regp = fpregsetp->fpregs;

  for (regi = 0; regi < 32; regi++)
    supply_register (regi + FP0_REGNUM, (char *)(regp + regi));
}

void
fill_fpregset (fpregsetp, regno)
     fpregset_t *fpregsetp;
     int regno;
{
  int regi;
  register u_quad_t *regp = fpregsetp->fpregs;

  for (regi = FP0_REGNUM; regi < FP0_REGNUM + 32; regi++)
    {
      if ((regno == -1) || (regno == regi))
	{
	  *(regp + regi - FP0_REGNUM) =
	    *(u_quad_t *) &registers[REGISTER_BYTE (regi)];
	}
    }
}

/* the name of the proc status struct depends on the implementation */
#ifdef HAVE_PSTATUS_T
  typedef pstatus_t gdb_prstatus_t;
#else
  typedef prstatus_t gdb_prstatus_t;
#endif

gdb_prstatus_t *procfs_read_current_status();

alpha_float_info ()
{
  int regi;
  extern char registers[];
  double mydouble;
  int i;
  char *fptr;
  int top;
  fpregset_t *fpregs;

  fpregs = (fpregset_t *)&(procfs_read_current_status())->pr_lwp.pr_context.uc_mcontext.gregs;

  for (regi = 0; regi < 32; regi++)
    {
	printf_filtered("f%d", regi);
	if (regi < 10) printf_filtered(" ");
	printf_filtered("  0x%16.16llx", 
	   *(LONGEST *)&registers[REGISTER_BYTE (FP0_REGNUM + regi)]);
	printf_filtered(" %#- 24.20g ", 
	   *(double *)&registers[REGISTER_BYTE (FP0_REGNUM + regi)]);
	printf_filtered("\n");
    }

}

#define COFF_WITH_PE
#define COFF_IMAGE_WITH_PE
#include "../include/coff/nt_alpha.h"
#include "../include/coff/internal.h"
#include "../include/coff/pe.h"
#include "gdbcore.h"
#include "../bfd/libcoff.h"

runtime_function find_pdata_entry(CORE_ADDR addr)
{
  CORE_ADDR base, t, pdata, ImageBase;
  unsigned long pdata_size;
  char raw_buffer[MAX_REGISTER_RAW_SIZE];
  runtime_function current;
  int nelts, curelt, curmin, curmax;

  base = proc_allocation_base(addr);

  /* a base might reasonably be 0, so we use -1 instead for no-match */
  if (base == (CORE_ADDR)-1) 
    {
       /* The most likely reason for this to fail is that the process hasn't
	  started yet, so we'll check the current image.  We have to get
	  pdata from the private headers; this is cheating a bit, but
	  this is a pretty odd situation to add to the general bfd interface.*/
       if (exec_bfd == NULL 
	   || pe_data(exec_bfd) == NULL)
	   goto fail;
       pdata=pe_data(exec_bfd)->pe_opthdr.DataDirectory[3].VirtualAddress
	     + bfd_getImageBase(exec_bfd);
       pdata_size=pe_data(exec_bfd)->pe_opthdr.DataDirectory[3].Size;
    }
  else
    {

      if (target_read_memory(base + offsetof(FILHDR, nt_signature),
	   raw_buffer, 4))
	goto fail;

      t = extract_unsigned_integer (raw_buffer, 4);

      /* is it "PE\0\0" (little endian) */
      if (t!=0x4550)
	goto fail;

      /* skip over the file header to the PE header */
      base += FILHSZ;
      if (target_read_memory(base + offsetof(PEAOUTHDR, ImageBase), raw_buffer, 4))
	goto fail;

      ImageBase = extract_unsigned_integer (raw_buffer, 4);

      if (target_read_memory(base + offsetof(PEAOUTHDR, DataDirectory[3][0]), 
	raw_buffer, 4))
	goto fail;

      pdata = extract_unsigned_integer (raw_buffer, 4) + ImageBase;

      if (target_read_memory(base + offsetof(PEAOUTHDR, DataDirectory[3][1]), 
	raw_buffer, 4))
	goto fail;

      pdata_size = extract_unsigned_integer (raw_buffer, 4);
    }

  nelts = pdata_size/sizeof(runtime_function);

  curelt = nelts/2;
  curmin = 0;
  curmax = nelts;

  while (1) 
    {
      if (target_read_memory(
	  pdata+curelt*sizeof(runtime_function),
	  (char *)&current, sizeof(runtime_function)))
	goto fail;

      if (current.begin <= addr && addr < current.end)
	{
	   return current;
	}

      if (addr < current.begin) 
	{
	  if (curelt == curmax)
	    {
	      goto fail;
	    }
	  curmax = curelt;
	}
      else
	{
	  if (curelt == curmin)
	    {
	      goto fail;
	    }
	  curmin = curelt;
	}
      curelt = (curmax+curmin)/2;
    }
fail:
    current.begin = (unsigned long)-1;
    return current;
}

#endif	/* HAVE_SYS_PROCFS_H */

