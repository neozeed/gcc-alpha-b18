// Test that function calls using thunks work right.
// Special g++ Options: -fvtable-thunks
// excess errors test - XFAIL mips*-*-* alpha*-*-[!o] rs6000-*-*

#include <stdarg.h>

struct A {
  void* p;
  A (void* q): p (q) { }
  A (const A& a): p (a.p) { }
};

class CBase {
public:
   void BaseFunc();
};

class MMixin {
public:
   virtual A MixinFunc(int arg, ...) = 0;
};

class CExample : public CBase, public MMixin {
public:
   A MixinFunc(int arg, ...);
};

void CBase::BaseFunc()
{
}

A CExample::MixinFunc(int arg, ...)
{
  va_list ap;
  va_start (ap, arg);

  if (arg != 1 || va_arg (ap, int) != 2 || va_arg (ap, int) != 3
      || va_arg (ap, int) != 4 || va_arg (ap, int) != 5
      || va_arg (ap, int) != 6 || va_arg (ap, int) != 7
      || va_arg (ap, int) != 8 || va_arg (ap, int) != 9)
    return 0;
  return this;
}

void* test(MMixin& anExample)
{
  return anExample.MixinFunc(1,2,3,4,5,6,7,8,9).p;
}

main ()
{
  CExample c;

  if (test(c) != &c)
    return 1;
  return 0;
}
