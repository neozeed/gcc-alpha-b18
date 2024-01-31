// Build don't link: 
// GROUPS passed templates overloading
// excess errors test - XFAIL *-*-*
template<class T> class Vector { };
template<class T> struct Sort { static void sort (Vector<T::foo> &); };
template<class T> void Sort<T>::sort (Vector<T::foo> &) { }
struct whee { typedef int foo; };

void f (Vector<int> &vi) { Sort<whee>::sort (vi); }
