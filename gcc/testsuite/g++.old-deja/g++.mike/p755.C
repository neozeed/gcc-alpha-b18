// It checks to see if you can define your own global new operator.
// prms-id: 755

typedef __SIZE_TYPE__ size_t;
extern "C" void exit(int);

void* operator new(size_t sz) {
  void* p = 0;
  exit(0);
  return p;
}

main () {
  int* i = new int;
  delete i;
  return 1;
}
