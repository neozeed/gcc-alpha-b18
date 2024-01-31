class Foo {
};

namespace A {	// WARNING - namespaces mostly broken
  namespace Foo {
    bar() {
      return 0;
    }
  }

  mymain() {
    return Foo::bar();
  }
}

main() {
  return A::mymain();
}
