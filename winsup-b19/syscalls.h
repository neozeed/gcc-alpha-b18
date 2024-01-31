/* syscalls.h: syscalls

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <sys/param.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/uio.h>
#include <errno.h>

/* FIXME: We wouldn't need most of these, since we include the headers above.
   Find out why.  Perhaps to keep them all in one place.  */
/* FIXME: This list should be sorted.  */

clock_t times (struct tms * buf);
clock_t _times (struct tms * buf);
int utimes (const char *path, struct timeval *tvp);
int settimeofday (const struct timeval * ,  const  struct timezone *);
int gettimeofday (struct timeval *p, struct timezone *z);
int _gettimeofday (struct timeval *p, struct timezone *z);
char * timezone ();
char *getwd (char *);
int _open (const char *path, int flags, mode_t mode);
int _close (int id);
off_t _lseek (int fd, off_t pos, int dir);
int ioctl (int id, int cmd , void *);
ssize_t _read (int fd, void *ptr, size_t len);
ssize_t _write (int fd, const void *ptr, size_t len);
ssize_t readv (int fd, const struct iovec *, int);
ssize_t writev (int fd, const struct iovec *, int);
void * _sbrk (size_t incr);
int _stat (const char *name, struct stat *buf);
int _fstat (int fd, struct stat *buf);
int fsync (int);
int getdtablesize();
struct passwd *getpwent (void);
void endpwent (void);
struct passwd * getpwuid (uid_t uid);
size_t getpagesize ();
int _setmode (int, int);
int setmode (int, int);
int ftruncate (int, off_t);
int truncate (const char *, off_t);
int symlink (const char *oldpath, const char *newpath);
int readlink (const char *, char *, int);
int gettimeofday (struct timeval *p, struct timezone *z);
char *cuserid (char *src);
struct tm * localtime (const time_t * tim_p);
void export_free (void *p);
void *export_malloc (int size);
void *export_realloc (void *p, int size);
void *export_calloc (size_t nmemb, size_t size);

/* Secure exec() functions family */
pid_t sexecl(HANDLE, const char *path, const char *argv0, ...);
pid_t sexecle(HANDLE, const char *path, const char *argv0, ... /*, char * const *envp */);
pid_t sexeclp(HANDLE, const char *path, const char *argv0, ...);
pid_t sexeclpe(HANDLE, const char *path, const char *argv0, ... /*, char * const *envp */);

pid_t sexecv(HANDLE, const char *path, const char * const *argv);
pid_t sexecve(HANDLE, const char *path, const char * const *argv, const char * const *envp);
pid_t sexecvp(HANDLE, const char *path, const char * const *argv);
pid_t sexecvpe(HANDLE, const char *path, const char * const *argv, const char * const *envp);

#ifdef __cplusplus
}
#endif
