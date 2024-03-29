// Special g++ Options: -fexceptions
// excess errors test - XFAIL hppa*-*-* a29k-*-* sparc64-*-elf sh-*-* z8k-*-* arm-*-pe**-*

void my_unexpected() {
  throw 42;
}

template <class T> int foo(T) throw (int) { throw "Hi"; }

main() {
  set_unexpected (my_unexpected);
  try {
    foo(1);
  } catch (int i) {
    if (i == 42)
      return 0;
  }
  return 1;
}
