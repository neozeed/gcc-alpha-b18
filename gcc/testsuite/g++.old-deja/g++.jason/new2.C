// PRMS Id: 6267
// Special g++ Options: -fthis-is-variable

struct A {
  int i;
  A() { i = 2; }
};
 
main()
{
  A *p = new A ();
}
