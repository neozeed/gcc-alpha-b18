// Bug: new doesn't make sure that the count is an integral value.

typedef __SIZE_TYPE__ size_t;
extern "C" int printf (const char *, ...);
extern "C" void *malloc (size_t);
size_t s;

void * operator new (size_t siz) {
  if (s == 0)
    s = siz;
  else
    s = (s != siz);
  return malloc (siz);
}

main()
{
  s = 0;

  float f = 3;
  int* b1 = new int[(int)f];
  int* b2 = new int[f];

  return s;
}
