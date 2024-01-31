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

#if 0
/* See procfs.c and *opennt*.h in config/[alpha,i386] */
CORE_ADDR tramp_start;
CORE_ADDR tramp_end;
CORE_ADDR null_start;
CORE_ADDR null_end;
#endif

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
base=(CORE_ADDR)-1;
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
#if 0 
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
#endif
      pdata=pe_data(exec_bfd)->pe_opthdr.DataDirectory[3].VirtualAddress + base;
      pdata_size=pe_data(exec_bfd)->pe_opthdr.DataDirectory[3].Size;

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



