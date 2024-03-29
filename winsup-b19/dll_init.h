/* dll_init.h

   Copyright 1998 Cygnus Solutions

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

//-----------------------------------------------------------------------------
// list of loaded DLL (used by fork & init)
class DllList
{
public:
  static DllList& the ();
  
  // return dll index used for freeDll
  int recordDll (HMODULE, per_process*);
  void detachDll (int dll_index);

  // called after initialization of main module in dll_crt0
  void initAll ();

  // global destructors of loaded dlls
  void doGlobalDestructorsOfDlls ();

  // number of dlls dlopened
  int numberOfOpenedDlls ();
  
  // boolean to determine if forked process must reload dlls opened with
  // LoadLibrary or dlopen ...
  // default = 0 (FALSE)
  int forkeeMustReloadDlls ();
  void forkeeMustReloadDlls (int);

  void forkeeStartLoadedDlls ();
  void forkeeEndLoadedDlls ();

  // set name of current library opened with dlopen
  void currentDlOpenedLib (const char*);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class DllListIterator
{
  int _type;
  int _index;

protected:
  DllListIterator (int type);
  int index () const { return _index; }

public:
  virtual ~DllListIterator();

  int ok() { return _index!=-1; }
  void operator++ ();
  void operator++ (int) { operator++ (); }
  operator per_process* ();
};

//-----------------------------------------------------------------------------

class DllNameIterator : public DllListIterator
{
protected:
  DllNameIterator (int type);
  
public:
  virtual ~DllNameIterator ();
  
  operator const char* ();
};

//-----------------------------------------------------------------------------

class LinkedDllIterator : public DllListIterator
{
public:
  LinkedDllIterator ();
  ~LinkedDllIterator ();
};

//-----------------------------------------------------------------------------

class LoadedDllIterator : public DllListIterator
{
public:
  LoadedDllIterator ();
  ~LoadedDllIterator ();
};

//-----------------------------------------------------------------------------

class LinkedDllNameIterator : public DllNameIterator
{
public:
  LinkedDllNameIterator ();
  ~LinkedDllNameIterator ();
};

//-----------------------------------------------------------------------------

class LoadedDllNameIterator : public DllNameIterator
{
public:
  LoadedDllNameIterator ();
  ~LoadedDllNameIterator ();
};

//-----------------------------------------------------------------------------

#define DO_LINKED_DLL(var)						      \
{									      \
LinkedDllIterator iterator;						      \
while (iterator.ok ())					                      \
{									      \
  per_process *var = (per_process *) iterator;
									      
#define DO_LOADED_DLL(var)						      \
{									      \
LoadedDllIterator iterator;						      \
while (iterator.ok ())					                      \
{									      \
  per_process *var = (per_process *) iterator;

#define DO_LINKED_DLL_NAMES(var)					      \
{									      \
LinkedDllNameIterator iterator;						      \
while (iterator.ok ())					                      \
{									      \
  const char *var= (const char *) iterator;
									      
#define DO_LOADED_DLL_NAMES(var)					      \
{									      \
LoadedDllNameIterator iterator;						      \
while (iterator.ok ())					                      \
{									      \
  const char *var = (const char *) iterator;

#define DONE								      \
  iterator++;								      \
}									      \
}

