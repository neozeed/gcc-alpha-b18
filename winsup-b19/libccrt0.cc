/* libccrt0.cc: crt0 for libc [newlib calls this one]

   Copyright 1996, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include <reent.h>
#include <stdlib.h>

/* For fork */
#if defined( _POWER) || defined(__alpha)
extern char __data_start__;
extern char __data_end__;
extern char __bss_start__;
extern char __bss_end__;
#else
extern char _data_start__;
extern char _data_end__;
extern char _bss_start__;
extern char _bss_end__;
#endif

typedef int (*MainFunc) (int argc, char *argc[], char **environ);

extern "C" 
{
  char **environ;
  void cygwin_crt0 (MainFunc);
  int cygwin32_attach_dll (HMODULE, MainFunc);
  extern void (*__CTOR_LIST__) (void);
  extern void (*__DTOR_LIST__) (void);
  int main (int, char **, char **);
  struct _reent *_impure_ptr;
  int _fmode;
};

extern "C" 
{
 int getsp();
}

static per_process cygwin_statu;

/* Set up pointers to various pieces so the dll can then use them,
   and then jump to the dll.  */

static void cygwin_crt0_common (MainFunc f)
{
  /* This is used to record what the initial sp was.  The value is needed
     when copying the parent's stack to the child during a fork.  */
  int onstack;

  /* The version numbers are the main source of compatibility checking.
     As a backup to them, we use the size of the per_process struct.  */
  cygwin_statu.magic_biscuit = sizeof (per_process);

  /* cygwin.dll version number in effect at the time the app was created.  */
  cygwin_statu.version_major = CYGWIN_DLL_VERSION_MAJOR;
  cygwin_statu.version_minor = CYGWIN_DLL_VERSION_MINOR;

  cygwin_statu.ctors = &__CTOR_LIST__;
  cygwin_statu.dtors = &__DTOR_LIST__;
  cygwin_statu.envptr = &environ;
  cygwin_statu.impure_ptr_ptr = &_impure_ptr;
  cygwin_statu.main = f;
  cygwin_statu.fmode_ptr = &_fmode;
#ifndef __alpha
  cygwin_statu.initial_sp = (char *) &onstack;
#else
  cygwin_statu.initial_sp = (char *) getsp();
#endif
  /* Remember whatever the user linked his application with - or
     point to entries in the dll.  */
  cygwin_statu.malloc = &malloc; 
  cygwin_statu.free = &free;
  cygwin_statu.realloc = &realloc;
  cygwin_statu.calloc = &calloc;

  /* Setup the module handle so fork can get the path name. */
  cygwin_statu.hmodule = GetModuleHandle (0);

  /* variables for fork */
#if defined (_POWER) || defined(__alpha)
  cygwin_statu.data_start = &__data_start__;
  cygwin_statu.data_end = &__data_end__;
  cygwin_statu.bss_start = &__bss_start__;
  cygwin_statu.bss_end = &__bss_end__;
#else
  cygwin_statu.data_start = &_data_start__;
  cygwin_statu.data_end = &_data_end__;
  cygwin_statu.bss_start = &_bss_start__;
  cygwin_statu.bss_end = &_bss_end__;
#endif
}

/* for main module */
void cygwin_crt0 (MainFunc f)
{
  cygwin_crt0_common (f);
  
 /* Jump into the dll. */
  dll_crt0 (&cygwin_statu); 
}

/* for a loaded dll */
int cygwin32_attach_dll (HMODULE h, MainFunc f)
{
  cygwin_crt0_common (f);

  /* jump into the dll. */
   return dll_dllcrt0 (h, &cygwin_statu);
}

#ifdef OLDWAY
/* This was originally needed to terminate the list of import stuff */
asm (".section .idata$3\n" ".long 0,0,0,0,0,0,0,0");
#endif
