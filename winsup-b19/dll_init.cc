/* dll_init.cc

   Copyright 1998 Cygnus Solutions.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "dll_init.h"
#include <stdlib.h>

extern void check_sanity_and_sync (per_process *);

/* WARNING: debug can't be called before init !!!! */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// the private structure

typedef enum { NONE, LINK, LOAD } dllType;

struct dll
{
  per_process *p;
  HMODULE handle;
  dllType type;
};

//-----------------------------------------------------------------------------

#define MAX_DLL_BEFORE_INIT	100 // enough ???
static dll _list_before_init[MAX_DLL_BEFORE_INIT]; 

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// local variables

static DllList _the;
static int _last = 0;
static int _max = MAX_DLL_BEFORE_INIT;
static dll *_list = _list_before_init;
static int _initCalled = 0;
static int _numberOfOpenedDlls = 0;
static int _forkeeMustReloadDlls = 0;
static int _in_forkee = 0;
static const char *_dlopenedLib = 0;
static int _dlopenIndex = -1;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static int __dll_global_dtors_recorded = 0;

static void
__dll_global_dtors()
{
  _the.doGlobalDestructorsOfDlls();
}

static void
doGlobalCTORS (per_process *p)
{
  void (**pfunc) () = p->ctors;
  for (int i = 1; pfunc[i]; i++)
    (pfunc[i]) ();
}

static void
doGlobalDTORS (per_process *p)
{
  if (!p)
    return;
  void (**pfunc)() = p->dtors;
  
  /* Run dtors backwards, so skip the first entry and find how many
    there are, then run them.  */
  
  if (pfunc) 
  {
    int i;
    for (i = 1; pfunc[i]; i++);

    for (int j = i - 1; j > 0; j-- )
      (pfunc[j]) ();
  }
}

#define INC 500 

static int
add (HMODULE h, per_process *p, dllType type)
{
  int ret = -1;

  if (p)
    check_sanity_and_sync (p);
  
  if (_last == _max)
  {
    if (!_initCalled) // we try to load more than MAX_DLL_BEFORE_INIT
    {
      small_printf ("try to load more dll than max allowed=%d\n",
		   MAX_DLL_BEFORE_INIT);
      ExitProcess (1);
    }
    
    dll* newArray = new dll[_max+INC];
    if (_list)
    {
      memcpy (newArray, _list, _max * sizeof (dll));
      if (_list != _list_before_init)
	delete []_list;
    }
    _list = newArray;
    _max += INC;
  }
  
  _list[_last].handle = h;
  _list[_last].p = p;
  _list[_last].type = type;
  
  ret = _last++;
  return ret;
}

static int
initOneDll (per_process *p)
{
  /* global variable u must be initialized */
  if (u == 0)
  {
    small_printf ("WARNING: process not inited while trying to init a DLL!\n");
    return 0;
  }

  /* init impure_ptr */
  *(p->impure_ptr_ptr) = *(u->impure_ptr_ptr);

  /* FIXME: init environment (useful?) */
  *(p->envptr) = *(u->envptr);

  /* FIXME: need other initializations? */

  int ret = 1;
  if (!_in_forkee)
  {
    /* global contructors */
    doGlobalCTORS (p);
    
    /* entry point of dll (use main of per_process with null args...) */
    if (p->main)
      ret = (*(p->main)) (0, 0, 0);
  }

  return ret;
}

DllList& DllList::the ()
{
  return _the;
}

void
DllList::currentDlOpenedLib (const char *name)
{
  if (_dlopenedLib != 0)
    small_printf ("WARNING: previous dlopen of %s wasn't correctly performed\n", _dlopenedLib);
  _dlopenedLib = name;
  _dlopenIndex = -1;
}

int
DllList::recordDll (HMODULE h, per_process *p)
{
  int ret = -1;
  
  /* debug_printf ("Record a dll p=%p\n", p); see WARNING */
  dllType type = LINK;
  if (_initCalled)
  {
    type = LOAD;
    _numberOfOpenedDlls++;
  }

  if (type == LOAD && _dlopenedLib !=0)
  {
    char buf[MAXPATHLEN];
    GetModuleFileName (h, buf, MAXPATHLEN);
    // it is not the current dlopened lib
    // so we insert one empty lib to preserve place for current dlopened lib
    if (strcmp (_dlopenedLib, buf) != 0)
    {
      if (_dlopenIndex == -1)
	_dlopenIndex = add (0, 0, NONE);
      ret = add (h, p, type);
    }
    else // it is the current dlopened lib
    {
      if (_dlopenIndex != -1)
      {
	_list[_dlopenIndex].handle = h;
	_list[_dlopenIndex].p = p;
	_list[_dlopenIndex].type = type;
	ret = _dlopenIndex;
	_dlopenIndex = -1;
      }
      else // it this case the dlopened lib doesn't need other lib
	ret = add (h, p, type);
      _dlopenedLib = 0;
    }
  }
  else
    ret = add (h, p, type);
  
  if (_initCalled) // main module is already initialized
  {
    if (!initOneDll (p))
      ret = -1;
  }
  return ret;
}

void
DllList::detachDll (int index)
{
  if (index != -1)
  {
    dll *aDll = &(_list[index]);
    doGlobalDTORS (aDll->p);
    if (aDll->type == LOAD)
      _numberOfOpenedDlls--;
    aDll->type = NONE;
  }
  else
    small_printf ("WARNING: try to detach an already detached dll ...\n");
}

void
DllList::initAll ()
{
  // init for destructors
  // because initAll isn't called in forked process, this exit function will
  // be recorded only once
  if (!__dll_global_dtors_recorded)
  {
    atexit (__dll_global_dtors);
    __dll_global_dtors_recorded = 1;
  }

  if (!_initCalled)
  {
    debug_printf ("call to DllList::initAll\n");
    for (int i = 0; i < _last; i++)
    {
      per_process *p = _list[i].p;
      if (p)
	initOneDll (p);
    }
    _initCalled = 1;
  }
}

void
DllList::doGlobalDestructorsOfDlls ()
{
  // global destructors in reverse order
  for (int i = _last - 1; i >= 0; i--)
  {
    if (_list[i].type != NONE)
    {
      per_process *p = _list[i].p;
      if (p)
	doGlobalDTORS (p);
    }
  }
}

int
DllList::numberOfOpenedDlls ()
{
  return _numberOfOpenedDlls;
}

int
DllList::forkeeMustReloadDlls ()
{
  return _forkeeMustReloadDlls;
}

void
DllList::forkeeMustReloadDlls (int i)
{
  _forkeeMustReloadDlls = i;
}

void
DllList::forkeeStartLoadedDlls ()
{
  _initCalled = 1;
  _in_forkee = 1;
}

void
DllList::forkeeEndLoadedDlls ()
{
  _in_forkee = 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// iterators

DllListIterator::DllListIterator (int type) : _index (-1), _type (type)
{
  operator++ ();
}

DllListIterator::~DllListIterator ()
{
}

DllListIterator::operator per_process* ()
{
  return _list[index ()].p;
}

void
DllListIterator::operator++ ()
{
  _index++;
  while (_index < _last && (int) (_list[_index].type) != _type)
    _index++;
  if (_index == _last)
    _index = -1;
}

DllNameIterator::DllNameIterator (int type) : DllListIterator (type)
{
}

DllNameIterator::~DllNameIterator ()
{
}

static char buffer[MAXPATHLEN];

DllNameIterator::operator const char* ()
{
  char *ret = 0;
  if (GetModuleFileName (_list[index ()].handle, buffer, MAXPATHLEN))
    ret = buffer;
  else
    small_printf ("WARNING: can't get name of loaded module, win32 error %d",
		 GetLastError ());
  return ret;
}

LinkedDllIterator::LinkedDllIterator () : DllListIterator ((int) LINK)
{
}

LinkedDllIterator::~LinkedDllIterator ()
{
}

LoadedDllIterator::LoadedDllIterator () : DllListIterator ((int) LOAD)
{
}

LoadedDllIterator::~LoadedDllIterator ()
{
}

LinkedDllNameIterator::LinkedDllNameIterator () : DllNameIterator ((int) LINK)
{
}

LinkedDllNameIterator::~LinkedDllNameIterator ()
{
}

LoadedDllNameIterator::LoadedDllNameIterator () : DllNameIterator ((int) LOAD)
{
}

LoadedDllNameIterator::~LoadedDllNameIterator ()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// the extern symbols

extern "C"
int
dll_dllcrt0 (HMODULE h, per_process *p)
{
  return _the.recordDll (h, p);
}

extern "C"
void
cygwin32_detach_dll (int index)
{
  _the.detachDll (index);
}

extern "C"
void
dlfork (int val)
{
  _the.forkeeMustReloadDlls (val);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
