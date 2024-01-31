/* mmap.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include <stddef.h>
#include <sys/mman.h>
#include <errno.h>
/* STD defines/includes */
#define times __hide_times
#define __THROW_BAD_ALLOC return 0
#include <list.h>
#include <map.h>
#undef times

#include "winsup.h"

/* STL includes */
/*
 * Simple class used to keep a record of all current
 * mmap areas in a process. Needed so that
 * they can be duplicated after a fork().
 */

class mmap_record
{
  private:
    HANDLE mapping_handle_;
    DWORD access_mode_;
    DWORD offset_;
    DWORD size_to_map_;
    void *base_address_;

  public:
    mmap_record (HANDLE h, DWORD ac, DWORD o, DWORD s, void *b) :
       mapping_handle_ (h), access_mode_ (ac), offset_ (o),
       size_to_map_ (s), base_address_ (b) { ; }

    /* Default Copy constructor/operator=/destructor are ok */

    /* Simple accessors */
    HANDLE get_handle () const { return mapping_handle_; }
    DWORD get_access () const { return access_mode_; }
    DWORD get_offset () const { return offset_; }
    DWORD get_size () const { return size_to_map_; }
    void *get_address () const { return base_address_; }
};

/*
 * Code to keep a record of all mmap'ed areas in a process.
 * Needed to duplicate tham in a child of fork().
 * mmap_record classes are kept in an STL list in an STL map, keyed
 * by file descriptor. This is *NOT* duplicated accross a fork(), it
 * needs to be specially handled by the fork code.
 */

static NO_COPY map <int, list <mmap_record> * > *mmapped_areas;

extern "C"
caddr_t
mmap (caddr_t addr, size_t len, int prot, int flags, int fd, off_t off)
{
  syscall_printf ("addr = %x, len = %d, prot = %x, flags = %x, fd = %d, off = %d\n",
                   addr, len, prot, flags, fd, off);

  /* Windows 95 does not have fixed addresses */
  if ((get_os_type () == win95) && (flags & MAP_FIXED))
    {
      set_errno (EINVAL);
      syscall_printf ("-1 = mmap(): win95 and MAP_FIXED\n");
      return (caddr_t) -1;
    }

  if (mmapped_areas == 0)
    {
      /* First mmap call, create STL map */
      mmapped_areas = new map< int, list<mmap_record> * >;
      if (mmapped_areas == 0)
        {
          set_errno (ENOMEM);
          syscall_printf ("-1 = mmap(): ENOMEM\n");
          return (caddr_t) -1;
        }
    }

  DWORD access = (prot & PROT_WRITE) ? FILE_MAP_WRITE : FILE_MAP_READ;
  access |= (flags & MAP_PRIVATE) ? FILE_MAP_COPY : 0;
  DWORD protect;
  
  if (access & FILE_MAP_COPY)
    protect = PAGE_WRITECOPY;
  else if (access & FILE_MAP_WRITE)
    protect = PAGE_READWRITE;
  else
    protect = PAGE_READONLY;

  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.bInheritHandle = TRUE;
  sa.lpSecurityDescriptor = 0;

  HANDLE hFile;

  if (fd == -1)
    hFile = (HANDLE) 0xFFFFFFFF;
  else
    {
      /* Ensure that fd is open */
      if (NOT_OPEN_FD (fd))
        {
          set_errno (EBADF);
          syscall_printf ("-1 = mmap(): EBADF\n");
          return (caddr_t) -1;
        }
      hinfo_vec *hvec = &myself->hmap;
      hFile = (*hvec) [fd].h->get_handle ();
    }

  HANDLE h = CreateFileMapping (hFile, &sa, protect, 0, len, NULL);
  if (h == 0)
    {
      __seterrno ();
      syscall_printf ("-1 = mmap(): CreateFileMapping failed with %d\n",
                         GetLastError ());
      return (caddr_t) -1;
    }

  void *base;

  if (flags & MAP_FIXED)
    {
      base = MapViewOfFileEx (h, access, 0, off, len, addr);
      if (base != addr)
        {
          __seterrno ();
          syscall_printf ("-1 = mmap(): MapViewOfFileEx failed with %d\n",
                             GetLastError ());
          CloseHandle (h);
          return (caddr_t) -1;
        }
    }
  else
    {
      base = MapViewOfFile (h, access, 0, off, len);
      if (base == 0)
        {
          __seterrno ();
          syscall_printf ("-1 = mmap(): MapViewOfFile failed with %d\n",
                             GetLastError ());
          CloseHandle (h);
          return (caddr_t) -1;
        }
    }

  /* Now we should have a successfully mmaped area.
     Need to save it so forked children can reproduce it.
  */

  mmap_record mmap_rec (h, access, off, len, base);

  /* Get list of mmapped areas for this fd, create a new one if
     one does not exist yet. 
  */

  list<mmap_record> *l = (*mmapped_areas) [fd];
  if (l == 0)
    {
      /* Create a new one */
      l = new list<mmap_record>;
      if (l == 0)
        {
          UnmapViewOfFile (base);
          CloseHandle (h);
          set_errno (ENOMEM);
          syscall_printf ("-1 = mmap(): ENOMEM\n");
          return (caddr_t) -1;
        }
      (*mmapped_areas)[fd] = l;
  }

  /* Insert into the list */
  l->push_front (mmap_rec);

  syscall_printf ("%x = mmap() succeeded\n", base);
  return (caddr_t) base;
}

/* munmap () removes an mmapped area.  It insists that base area
   requested is the same as that mmapped, error if not. */

extern "C"
int
munmap (caddr_t addr, size_t len)
{
  syscall_printf ("munmap (addr = %x, len = %d)\n", addr, len);

  /* Check if a mmap'ed area was ever created */
  if (mmapped_areas == 0)
    {
      syscall_printf ("-1 = munmap(): mmapped_areas == 0\n");
      set_errno (EINVAL);
      return -1;
    }

  /* Iterate through the map, looking for the mmapped area.
     Error if not found. */

  map<int, list<mmap_record> *>::iterator it;

  for (it = mmapped_areas->begin (); it != mmapped_areas->end (); ++it)
    {
      list<mmap_record> *l = (*it).second;
      if (l != 0)
        {
          list<mmap_record>::iterator li;
          for (li = l->begin (); li != l->end (); ++li)
            {
              mmap_record rec = *li;
              if (rec.get_address () == addr)
                {
                  /* Unmap the area */
                  UnmapViewOfFile (addr);
                  CloseHandle (rec.get_handle ());
                  /* Delete the entry. */
                  l->erase (li);
                  syscall_printf ("0 = munmap(): %x\n", addr);
                  return 0;
                }
             }
         }
     }
  set_errno (EINVAL);

  syscall_printf ("-1 = munmap(): EINVAL\n");

  return -1;
}                

/* Sync file with memory. Ignore flags for now. */

extern "C"
int
msync (caddr_t addr, size_t len, int flags)
{
  syscall_printf ("addr = %x, len = %d, flags = %x\n",
                  addr, len, flags);

  if (FlushViewOfFile (addr, len) == 0)
    {
      syscall_printf ("-1 = msync: LastError = %x\n", GetLastError ());
      __seterrno ();
      return -1;
    }
  syscall_printf ("0 = msync\n");
  return 0;
}

/* Set memory protection */

extern "C"
int
mprotect (caddr_t addr, size_t len, int prot)
{
  DWORD old_prot;
  DWORD new_prot = 0;

  syscall_printf ("mprotect (addr = %x, len = %d, prot = %x)\n",
                  addr, len, prot);

  if (prot & PROT_NONE)
    new_prot = PAGE_NOACCESS;
  else 
    {
      switch (prot)
        {
          case PROT_READ|PROT_WRITE|PROT_EXEC:
            new_prot = PAGE_EXECUTE_READWRITE;
            break;
          case PROT_READ|PROT_WRITE:
            new_prot = PAGE_READWRITE;
            break;
          case PROT_READ|PROT_EXEC:
            new_prot = PAGE_EXECUTE_READ;
            break;
          case PROT_READ:
            new_prot = PAGE_READONLY;
            break;
          default:
            syscall_printf ("-1 = mprotect (): invalid prot value\n");
            set_errno (EINVAL);
            return -1;
         }
     }

  if (VirtualProtect (addr, len, prot, &old_prot) == 0)
    {
      __seterrno ();
      syscall_printf ("-1 = mprotect (): lasterror = %x\n", GetLastError ());
      return -1;
    }

  syscall_printf ("0 = mprotect ()\n");
  return 0;
}

/*
 * Call to re-create all the file mappings in a forked
 * child. Called from the child in initialization. At this
 * point we are passed a valid mmaped_areas map, and all the
 * HANDLE's are valid for the child, but none of the
 * maped areas are in our address space. We need to iterate
 * through the map, doing the MapViewOfFile calls.
 */

extern "C"
int
recreate_mmaps_after_fork (void *param)
{
  map< int, list<mmap_record> * > *areas = (map< int, list<mmap_record> * > *)param;
  void *base;

  debug_printf ("recreate_mmaps_after_fork, mmapped_areas = %x\n", areas);

  /* Check if a mmapped area was ever created */
  if (areas == 0)
    return 0;

  /* Iterate through the map */

  map< int, list<mmap_record> * >::iterator it;

  for (it = areas->begin (); it != areas->end (); ++it)
    {
      list<mmap_record> *l = (*it).second;
      if (l != 0)
        {
          list<mmap_record>::iterator li;
          for (li = l->begin (); li != l->end (); ++li)
            {
              mmap_record rec = *li;

              debug_printf ("h = %x, access = %x, offset = %d, size = %d, address = %x\n",
                  rec.get_handle (), rec.get_access (), rec.get_offset (),
                  rec.get_size (), rec.get_address ());

              /* Now re-create the MapViewOfFileEx call */
              base = MapViewOfFileEx (rec.get_handle (), 
                                      rec.get_access (), 0, 
                                      rec.get_offset (), 
                                      rec.get_size (), 
                                      rec.get_address ());
              if (base != rec.get_address ())
                {
                  small_printf ("recreate_mmaps_after_fork: base address %x fails to match requested address %x\n", rec.get_address ());
                  return -1;
                }
             }
          }
      }

  /* Now set our mmap record in case the child forks. */
  mmapped_areas = areas;

  debug_printf ("succeeded\n");

  return 0;
}

/* Set a child mmap ptr from our static one. Used to set child mmap
   pointer for fork. */

extern "C"
void
set_child_mmap_ptr (pinfo *child)
{
  child->mmap_ptr = (void *) mmapped_areas;
}
