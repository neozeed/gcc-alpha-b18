// Build don't link: 
// GROUPS passed arg-matching
// excess errors test - XFAIL *-*-*
// From: gustavo@cpqd.br (Gustavo Chaves)
// Date:     Wed, 25 May 94 09:38:00 EST
// Subject:  problem with user defined conversions in initialization
// Message-ID: <9405251238.AA19815@moon.cpqd.br>

struct String { String(const char*); };

struct Ack { Ack(String); };

struct S { void method(Ack); };

void function(Ack);

foo(S *o)
{
    function("adsf");
    o->method("adsf");
}
