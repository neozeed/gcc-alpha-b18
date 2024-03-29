// Special g++ Options: -Wno-pmf-conversions
// prms-id: 10769

#define PMF2PF(PMF) ((void (*)())(PMF))

int ok = 0;

class A {
public:
  void f1a() { ok += 3; }
  void f1b() { ok += 5; }
  void f2a() { ok += 7; }
  void f2b() { }
  const static void (*table[2][2])();
  void main();
} a;

const void (*A::table[2][2])()
  = { { PMF2PF(&A::f1a), PMF2PF(&A::f1b) },
      { PMF2PF(&A::f2a), PMF2PF(&A::f1b) },
  };

void
dispatch (A *obj, int i, int j)
{
  (*(void (*)(A *))A::table[i][j])(obj);
}

void A::main() {
  dispatch (&a, 0, 0);
  void (A::*mPtr)(A*) = &A::f1a;

  (*(void (*)(A*))PMF2PF(mPtr))(&a);
  (*(void (*)(A*))PMF2PF(f2a))(&a);
}

int main() {
  a.A::main();
  dispatch (&a, 0, 1);
  void (A::*mPtr)(A*) = &A::f1b;

  (*(void (*)(A*))PMF2PF(a.*mPtr))(&a);
  (*(void (*)(A*))PMF2PF(a.f2a))(&a);
  return ok != 3+3+5+5+7+7;
}
