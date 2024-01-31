namespace Foo {	// WARNING - namespaces mostly broken
  bar() {
    return 0;
  }
}

main() {
  return Foo::bar();
}
