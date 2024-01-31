/* registry.h: registry data structures

   Copyright 1996, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

class reg_key
{
  HKEY key_;

public:

  int fillone_string (char *dst, const char *name, const char *def, int max);
  int setone_string (const char *src, const char *name);
  int setone_int (const char *key, int val);
  int getone_string (char *dst, const char *name, int len);

  void init (const char *name, HKEY r, REGSAM access);
  int open(const char *name, HKEY r, REGSAM access);

  void close();

  reg_key (reg_key &parent, const char *name, REGSAM access = KEY_ALL_ACCESS);
  reg_key ();
  HKEY get_key ();

  int get_int (const char *,int def);
  int get_string (const char *, char *buf, size_t len, const char *def);
  int set_string (const char *,const char *);
  int set_int (const char *,int val);
  void kill (const char *child);

  ~reg_key ();
};

class reg_session
{
  reg_key majorkey_;
  reg_key minorkey_;
  reg_key versionkey_;
  reg_key vminorkey_;

public:
  reg_session (HKEY key = HKEY_CURRENT_USER, REGSAM access = KEY_ALL_ACCESS);
  ~reg_session ();
  reg_key &get_key ();
};
