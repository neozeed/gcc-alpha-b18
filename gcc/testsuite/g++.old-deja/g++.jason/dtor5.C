// PRMS Id: 5286
// Bug: g++ forgets side-effects of object in call to nonexistent destructor.

void * operator new (__SIZE_TYPE__ s, void * p) { return p; }

int r;

template <class T> struct A {
  T *p;
  int i;
  A() { i = 0; p = (T*) new char[sizeof (T)]; new (p + i++) T; }
  ~A() { p[--i].~T(); r = i; }
};

main()
{
  { A<int> a; }

  int* p = (int*) new char[sizeof (int)];
  new (p + r++) int;
  p[--r].~int();
  
  return r;
}
