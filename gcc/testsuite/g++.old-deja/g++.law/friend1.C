// Build don't link: 
// GROUPS passed friends
// friends file
// From: rwave!myersn%rwave.roguewave@cs.orst.edu (Nathan Myers)
// Date:     Thu, 17 Dec 92 16:33 PST
// Subject:  2.3.2: friend decl of new confuses constructor
// Message-ID: <m0n2Vec-0000GrC@rwave.roguewave.com>

#include <stddef.h>
struct Foo {
  friend void* operator new(size_t);
  friend void operator delete(void*) throw ();
  Foo();
  ~Foo();
};
Foo::Foo() { }
Foo::~Foo() { }
