/* dlfcn.h

   Copyright 1998 Cygnus Solutions

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#ifdef __cplusplus
extern "C" {
#endif

/* declarations used for dynamic linking support routines */
extern void *dlopen (const char *, int);
extern void *dlsym (void *, const char *);
extern int dlclose (void *);
extern char *dlerror (void);

/* specific CYGWIN32 */
#define FORK_RELOAD	1
#define FORK_NO_RELOAD	0

extern void dlfork (int); 

/* following doesn't exist in Win32 API .... */
  
/* valid values for mode argument to dlopen */
#define RTLD_LAZY	1	/* lazy function call binding */
#define RTLD_NOW	2	/* immediate function call binding */
#define RTLD_GLOBAL	4	/* symbols in this dlopen'ed obj are visible to other dlopen'ed objs */

#ifdef __cplusplus
}
#endif
