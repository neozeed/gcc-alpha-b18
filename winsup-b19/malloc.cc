/* malloc.cc for WIN32.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Written by Steve Chamberlain of Cygnus Support
   sac@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include "winsup.h"

/* we provide these stubs to call into a user's
   provided malloc if there is one - otherwise
   functions we provide - like strdup will cause
   problems if malloced on our heap and free'd on theirs

   Disgusting but true.
*/

static int export_malloc_called = 0;
static int use_internal_malloc = 1;

#undef in
#undef out
#define in(x) 
#define out(x)

/* Call though the application pointer,
   which either points to export_malloc, or the application's
   own version. */

void *
malloc (size_t size)
{
  void *res;
  in ("malloc");
  res = u->malloc (size);
  out ("malloc");
  return res;
}

void
free (void *p)
{
  in ("free");
  u->free (p);
  out ("free");
}

void *
realloc (void *p, size_t size)
{
  void *res;
  in ("realloc");
  res = u->realloc (p, size);
  out ("realloc");
  return res;
}

void *
calloc (size_t nmemb, size_t size)
{
  void *res;
  in ("calloc");
  res = u->calloc (nmemb, size);
  out ("calloc");
  return res;
}

/* These routines are used by the application if it
   doesn't provide its own malloc. */
   
void
export_free (void *p)
{
  in ("export_free");
  if (use_internal_malloc)
    _free_r (_impure_ptr, p);
  else
    u->free (p);
  out ("export_free");
}

void *
export_malloc (int size)
{
  void *res;
  in ("export_malloc");
  export_malloc_called = 1;
  if (use_internal_malloc)
    res = _malloc_r (_impure_ptr, size);
  else
    res = u->malloc (size);
  out ("export_malloc");
  return res;
}

void *
export_realloc (void *p, int size)
{
  void *res;
  in ("export_realloc");
  if (use_internal_malloc)
    res = _realloc_r (_impure_ptr, p, size);
  else
    res = u->realloc (p, size);
  out ("export_realloc");
  return res;
}

void *
export_calloc (size_t nmemb, size_t size)
{
  void *res;
  in ("export_calloc");
  if (use_internal_malloc)
    res = _calloc_r (_impure_ptr, nmemb, size);
  else
    res = u->calloc (nmemb, size);
  out ("export_calloc");
  return res;
}

/* We use a critical section to lock access to the malloc data
   structures.  This permits malloc to be called from different
   threads.  Note that it does not make malloc reentrant, and it does
   not permit a signal handler to call malloc.  The malloc code in
   newlib will call __malloc_lock and __malloc_unlock at appropriate
   times.  */

static NO_COPY CRITICAL_SECTION malloc_critical_section;

void
malloc_init ()
{
  InitializeCriticalSection (&malloc_critical_section);
  /* Check if mallock is provided by application. If so, redirect all
     calls to export_malloc/free/realloc to application provided. This may
     happen if some other dll calls cygwin's malloc, but main code provides
     its own malloc */
  if (!u->forkee)
    {
      free (malloc (16));
      if (!export_malloc_called)
        use_internal_malloc = 0;
    }
}

extern "C"
void
__malloc_lock (struct _reent *ptr)
{
  EnterCriticalSection (&malloc_critical_section);
}

extern "C"
void
__malloc_unlock (struct _reent *ptr)
{
  LeaveCriticalSection (&malloc_critical_section);
}


