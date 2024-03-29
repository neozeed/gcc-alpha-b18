/* Posix dirent.h for WIN32.  */

/* Including this file should not require any Windows headers.  */
   
#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

struct dirent
{
  long __d_reserved[4];
  ino_t d_ino; /* Just for compatibility, it's junk */
  char d_name[256];		/* FIXME: use NAME_MAX? */
};

#define __DIRENT_COOKIE 0xdede4242

typedef struct
{
  /* This is first to set alignment in non _COMPILING_NEWLIB case.  */
  unsigned long __d_cookie;
  struct dirent *__d_dirent;
  char *__d_dirname;		/* directory name with trailing '*' */
  int __d_find_first_called;	/* non-zero if FindFirstFile called */
  unsigned long __d_dirhash;    /* hash of directory name for use by
				   readdir */
  union
    {
#ifdef _COMPILING_NEWLIB
      struct
	{
	  HANDLE __handle;
	  char __open_p;
	} __d_data;
#endif
      char __d_filler[16];
    } __d_u;
} DIR;

DIR *opendir (const char *);
struct dirent *readdir (DIR *);
void rewinddir (DIR *);
int closedir (DIR *);

#endif
