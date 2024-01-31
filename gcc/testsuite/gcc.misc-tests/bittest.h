struct a_type {
   int a;
   unsigned char b;
   unsigned c:7;
   int d;
   unsigned e:3;
   unsigned f:9;
   unsigned char g:7;
   int h;
   unsigned int i:6;
   unsigned int :0;
   unsigned int j:6;
} NATIVE ;

struct b_type {
   int a;
   unsigned char b;
   unsigned int c:7;
   int d;
   unsigned int e:3;
   unsigned int f:9;
   unsigned char g:7;
   int h;
   unsigned char i:6;
   unsigned char :0;
   unsigned char j:6;

} NATIVE ;

struct c_type {
   int a;
   unsigned char b;
   unsigned short c:7;
   int d;
   unsigned short e:3;
   unsigned short f:9;
   unsigned char g:7;
   short h;
   unsigned short i:6;
   unsigned short :0;
   unsigned short j:6;
} NATIVE ;

struct d_type {
   int a:3;
   int b:4;
   int c:4;
   int d:6;
   int e:5;
   int f:5;
   int g:5;
} NATIVE ;
