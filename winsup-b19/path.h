/* path.h: path and mount data structures

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

class path_conv 
{
  char path[MAX_PATH];
 public:

  char binary_p;
  char silent_p;
  int  symlink_p;
  int  exec_p;

  int error;

  path_conv (const char * const, int follow_mode = 1);
  inline char *get_win32 () { return path; }
};

/* Symlink marker */
#define SYMLINK_COOKIE "!<symlink>"

/* Maximum depth of symlinks (after which ELOOP is issued).  */
#define MAX_LINK_DEPTH 10

/* Mount table entry.  */

class mount_item
{
public:
  /* FIXME: Nasty static allocation.  Need to have a heap in the shared
     area [with the user being able to configure at runtime the max size].  */

  /* DOS-style mounted partition source ("F:").
     device[0] == 0 for unused entries.  */
  char device[MAX_PATH];
  int devicelen;

  /* UNIX-style mount point ("/mnt") */
  char path[MAX_PATH];
  int pathlen;

  char binary;
  char silent;

  void init (const char *dev, const char *path, int flags);

  struct mntent *getmntent ();
};

/* Mount table.  */

/* Warning: Decreasing this value will cause cygwin.dll to ignore existing
   higher numbered registry entries.  Don't change this number willy-nilly.
   What we need is to have a more dynamic allocation scheme, but the current
   scheme should be satisfactory for a long while yet.  */
#define MAX_MOUNTS 30

class mount_info
{
 public:
  int nmounts;
  mount_item mount[MAX_MOUNTS];

  void init ();
  int add_item (const char *dev, const char *path, int flags);
  int del_item (const char *path);
  void sort ();
  void to_registry ();
  void from_registry ();
  int posix_path_p ();
  int binary_win32_path_p (const char *path);
  int conv_to_win32_path (const char *src_path, char *win32_path,
			  char *full_win32_path);
  int conv_to_posix_path (const char *src_path, char *posix_path,
			  int keep_rel_p);
  struct mntent *getmntent (int x);
};

/* These are exported from the dll as cygwin32_foo.  */
extern "C" {
  void conv_to_win32_path (const char *src_path, char *win32_path);
  void conv_to_full_win32_path (const char *src_path, char *win32_path);
  void conv_to_posix_path (const char *src_path, char *posix_path);
  void conv_to_full_posix_path (const char *src_path, char *posix_path);
  int posix_path_list_p (const char *path);
  int win32_to_posix_path_list_buf_size (const char *path_list);
  int posix_to_win32_path_list_buf_size (const char *path_list);
  void win32_to_posix_path_list (char *win32, char *posix);
  void posix_to_win32_path_list (char *posix, char *win32);
  void split_path (const char *path, char *dir, char *file);
}
