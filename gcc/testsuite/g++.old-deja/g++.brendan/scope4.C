// Build don't link: 
// excess errors test - XFAIL *-*-*
// GROUPS passed scoping
class BitString {
public:
    int i;
    int length() const;
};

typedef BitString BS;

class V {
public:
    class BitString {
    public:
        static int x(const ::BitString& value);
        static int y(const class ::BitString& value);
        static int z(const BS& value);
    };
};

int
V::BitString::x(const ::BitString& value)
{ return value.length(); }

int
V::BitString::y(const class ::BitString& value)
{ return value.length(); }

int
V::BitString::z(const BS& value)
{ return value.length(); }
