// Build don't link: 
// GROUPS passed operators
// excess errors test - XFAIL *-*-*
// opr-ampr file
// From: Chris Colohan <colohan@eecg.toronto.edu>
// Date:     Thu, 7 Oct 1993 16:02:36 -0400
// Subject:  Bug Report
// Message-ID: <93Oct7.160240edt.19118@picton.eecg.toronto.edu>

#include <iostream.h>
#include <Complex.h> 

class MyCplx : public Complex {
public:
	void operator=(const MyCplx& c) {
		if(this == &c) return;
		re = c.re;
		im = c.im;
	}
	friend istream& operator>>(istream&, MyCplx&);
};

inline istream& operator>>(istream& strm, MyCplx& c)
{
	double	d;

	strm >> d;
	c = MyCplx(d);

	return strm;
}

struct str {
	MyCplx value;
};

struct str aStruct;


struct str *func(void)
{
	return &aStruct;
}

MyCplx foo()
{
	return func()->value;
}
	
int main(void)
{
	aStruct.value = MyCplx(2,3);

	cout << foo() << endl;

	return 0;
}
