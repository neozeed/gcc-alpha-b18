/* This program shows two aspects of a problem with 64-bit (and possibly
   smaller, altho THIS test won't catch it) architectures that pass structure
   values in registers, and which rely upon TRULY_NOOP_TRUNCATE.  This
   occurred on the Alpha.

   1) Pass a struct in a register, such that the last field is a "whole"
      word.
   2) Pass that last whole word to an intrinsic function

   The code to do this (on the alpha) is a bis (register to register copy)
   of all 64 bits; the high bits (which contain some other part of the struct)
   are copied, and NOT zeroed or extended over.

   If R->R copies are done with TRULY_NOOP_TRUNCATE always true (which
   appears to be nearly universal), they must be the right width.

   The first test calls shows a problem with calling the divide intrinsic,
   where the dividend picks up the extra bits; the second is memcpy(),
   where the size picks up the extra bits and memfaults. */


#include <signal.h>

struct _ffetarget_char_1_
  {
    long length;
    unsigned char *text;
  };
typedef struct _ffetarget_char_1_ ffetargetCharacter1;
typedef unsigned char ffetargetCharacterUnit1;
typedef unsigned long long int ffetargetTypeless;
typedef ffetargetCharacter1 ffetargetCharacterDefault;

union _ffebld_constant_union_
  {
    ffetargetTypeless typeless;
    ffetargetCharacter1 character1;
  };
typedef union _ffebld_constant_union_ ffebldConstantUnion;

union _ffebld_constant_array_
  {
    ffetargetTypeless typeless;
    ffetargetCharacterUnit1 *character1;
  };
typedef union _ffebld_constant_array_ ffebldConstantArray;

void
ffebld_constantarray_put (ffebldConstantArray array, int bt,
   int kt, int offset, ffebldConstantUnion constant)
{
	  memcpy (array.character1 + offset,
		  (( constant.character1 ).text) ,
		  (( constant.character1 ).length) );
}

int
test_divide (ffebldConstantArray array, int bt,
   int kt, int offset, ffebldConstantUnion constant)
{
	return constant.character1.length/bt;
}

void handler(int sig)
{
    abort();
}

main()
{
	ffebldConstantArray a;
	ffebldConstantUnion u;
	char c[10];
	int i;

	u.character1.text = (char *)0xffffffff;
	u.character1.length = 10;
	i = test_divide(a, 5, 0, 0, u);

	if (i!=2) abort();

	u.character1.text = "xxxxx";
	u.character1.length = 5;

	a.character1=c;

	signal(SIGSEGV, handler);
	ffebld_constantarray_put(a, 0, 0, 0, u);

	exit(0);
}
