// From: Ove.Ewerlid@syscon.uu.se (Ove Ewerlid)
// Subject: ss-940630:cc1plus: internal error
// Date: Sat, 2 Jul 1994 05:07:20 +0200
// Special g++ Options:
// Build don't link:

class qwerty {
public:
    qwerty (const unsigned short userkey[8]);
   ~qwerty ();
};

class foo {
private:
    const unsigned char * const dummy_key = (unsigned char*)"ThisIs a dummy!";
public:
    void bar ();
};

void
foo::bar ()
{
    qwerty QWERTY ((unsigned short*)dummy_key);
}
