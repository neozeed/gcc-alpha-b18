// Bug: g++ fails to actually instantiate templates to the specifications of
// guiding decls.
// Special g++ Options: -g -ansi -pedantic-errors

template <class T> inline T min (T a, T b) { return a<b?a:b; }
double min (double, double);

main () {
  return (int) min (0, 1.0);
}
