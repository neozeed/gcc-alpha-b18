namespace Foo {	// WARNING - namespaces mostly broken
  bar() {
    return 0;
  }
}

using Foo::bar;

main() {
  return bar();
}
