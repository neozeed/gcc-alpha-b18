// GROUPS passed
extern "C" printf(...);
extern "C" void exit(int);

class A {
public:
  virtual ~A() {
    printf("FAIL\n");
    exit (1);
  }
};

class B : public A {
public:
  virtual ~B() {
    printf("PASS\n");
    exit (0);
  }
};

main() {
  B b;
  A *ap = &b;
  ap->~A();  // This should call the destructor virtually.
  printf("FAIL\n");
  return 1;
}
