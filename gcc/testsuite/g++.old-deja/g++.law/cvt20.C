// Build don't link: 
// GROUPS passed conversions
// excess errors test - XFAIL *-*-*
// cvt file
// Message-Id: <9307152250.AA24812@volterra>
// From: rst@ai.mit.edu (Robert S. Thau)
// Subject: g++ won't convert char[] to char*&
// Date: Thu, 15 Jul 93 18:50:59 EDT


// Compiles fine with Sun CC 2.1

void f(char *& x)
{
  x++;
}

main()
{
  f ("foo");
}
