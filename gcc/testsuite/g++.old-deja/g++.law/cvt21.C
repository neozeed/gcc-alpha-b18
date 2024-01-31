// Build don't link: 
// GROUPS passed conversions
// excess errors test - XFAIL *-*-*
// cvt file
// Message-Id: <9307200528.AA02094@legolas>
// From: Mark Kuzmycz <kuzmycz@deakin.edu.au>
// Subject: int & conversion operator
// Date: Tue, 20 Jul 93 15:28:47 EST





extern "C" {







 






 




 


 





 



 





 





 

 



















typedef int ptrdiff_t;








 




 

 
























typedef unsigned int size_t;














 




 




















 

typedef __wchar_t wchar_t;














 





 









 












}









extern "C" {

int       abs(int);


void volatile abort(void);




double    atof(const char*);
int       atoi(const char*);
long      atol(const char*);

int       atexit(auto void (*p) (void));
int       bsearch (const void *, const void *, size_t, 
                   size_t, auto int (*ptf)(const void*, const void*));
void*     calloc(size_t, size_t);
void      cfree(void*);


void volatile exit(int);




char*     fcvt(double, int, int*, int*);
void      free(void*);
char*     getenv(const char*);
int       getopt(int, char * const *, const char*);
int       getpw(int, char*);
char*     gcvt(double, int, char*);
char*     ecvt(double, int, int*, int*);
extern char**   environ;

long      labs(long);
void*     malloc(size_t);
size_t    malloc_usable_size(void*);
int       putenv(const char*);
extern char*    optarg;
extern int      opterr;
extern int      optind;
void      qsort(void*, size_t, size_t, auto int (*ptf)(void*,void*));
int       rand(void);
void*     realloc(void*, size_t);
int       setkey(const char*);
int       srand(unsigned int);
double    strtod(const char*, char**);
long      strtol(const char*, char**, int);
unsigned long stroul(const char**, int);
int       system(const char*);

long      random(void);
void      srandom(int);
char*     setstate(char*);
char*     initstate(unsigned, char*, int);

double    drand48(void);
void      lcong48(short*);
long      jrand48(short*);
long      lrand48(void);
long      mrand48(void);
long      nrand48(short*);
short*    seed48(short*);
void      srand48(long);

char*     ctermid(char*);
char*     cuserid(char*);
char*     tempnam(const char*, const char*);
char*     tmpnam(char*);

}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 







   

  






typedef long _G_clock_t;
typedef unsigned long _G_dev_t;
typedef long _G_fpos_t;
typedef long _G_gid_t;
typedef unsigned long _G_ino_t;
typedef unsigned long _G_mode_t;
typedef unsigned long _G_nlink_t;
typedef long _G_off_t;
typedef long _G_pid_t;
typedef int _G_ptrdiff_t;
typedef int   _G_sigset_t;
typedef unsigned int _G_size_t;
typedef long _G_time_t;
typedef long _G_uid_t;
typedef long _G_wchar_t;
typedef int _G_ssize_t;
typedef char*   _G_va_list;


















 
 
















class ostream; class streambuf; class backupbuf;

 







extern "C" int __underflow(streambuf*);
extern "C" int __overflow(streambuf*, int);

typedef _G_off_t streamoff;
typedef _G_off_t streampos;  

typedef unsigned long __fmtflags;
typedef unsigned char __iostate;

struct _ios_fields {  
    streambuf *_strbuf;
    ostream* _tie;
    int _width;
    __fmtflags _flags;
    _G_wchar_t _fill;
    __iostate _state;
    __iostate _exceptions;
    int _precision;
};

















class ios : public _ios_fields {
  public:
    typedef __fmtflags fmtflags;
    typedef int iostate;
    typedef int openmode;
    enum io_state {
	goodbit = 0 ,
	eofbit = 1 ,
	failbit = 2 ,
	badbit = 4  };
    enum open_mode {
	in = 1 ,
	out = 2 ,
	ate = 4 ,
	app = 8 ,
	trunc = 16 ,
	nocreate = 32 ,
	noreplace = 64 ,
	bin = 128  };
    enum seek_dir { beg, cur, end};
     
    enum { skipws=01, left=02, right=04, internal=010,
	   dec=020, oct=040, hex=0100,
	   showbase=0200, showpoint=0400, uppercase=01000, showpos=02000,
	   scientific=04000, fixed=010000, unitbuf=020000, stdio=040000,
	   dont_close=0x80000000  
	   };
    enum {  
	basefield=dec+oct+hex,
	floatfield = scientific+fixed,
	adjustfield = left+right+internal
    };



    ostream* tie() const { return _tie; }
    ostream* tie(ostream* val) { ostream* save=_tie; _tie=val; return save; }

     
    _G_wchar_t fill() const { return (_G_wchar_t)_fill; }
    _G_wchar_t fill(_G_wchar_t newf)
	{_G_wchar_t oldf = (_G_wchar_t)_fill; _fill = (char)newf; return oldf;}
    fmtflags flags() const { return _flags; }
    fmtflags flags(fmtflags new_val) {
	fmtflags old_val = _flags; _flags = new_val; return old_val; }
    int precision() const { return _precision; }
    int precision(int newp) {
	unsigned short oldp = _precision; _precision = (unsigned short)newp;
	return oldp; }
    fmtflags setf(fmtflags val) {
	fmtflags oldbits = _flags;
	_flags |= val; return oldbits; }
    fmtflags setf(fmtflags val, fmtflags mask) {
	fmtflags oldbits = _flags;
	_flags = (_flags & ~mask) | (val & mask); return oldbits; }
    fmtflags unsetf(fmtflags mask) {
	fmtflags oldbits = _flags & mask;
	_flags &= ~mask; return oldbits; }
    int width() const { return _width; }
    int width(int val) { int save = _width; _width = val; return save; }




    void _throw_failure() { }


    streambuf* rdbuf() const { return _strbuf; }
    void clear(iostate state = 0) {
	_state = _strbuf ? state : state|badbit;
	if (_state & _exceptions) _throw_failure(); }
    void set(iostate flag) { _state |= flag;
	if (_state & _exceptions) _throw_failure(); }
    int good() const { return _state == 0; }
    int eof() const { return _state & ios::eofbit; }
    int fail() const { return _state & (ios::badbit|ios::failbit); }
    int bad() const { return _state & ios::badbit; }
    iostate rdstate() const { return _state; }
    operator void*() const { return fail() ? (void*)0 : (void*)(-1); }
    int operator!() const { return fail(); }
    iostate exception(iostate enable) {
	iostate old = _exceptions; _exceptions = enable;
	if (_state & _exceptions) _throw_failure();
	return old; }

    static int sync_with_stdio(int on);
    static void sync_with_stdio() { sync_with_stdio(1); }









  protected:
    ios(streambuf* sb = 0, ostream* tie = 0);
    virtual ~ios();
    void init(streambuf* sb) { _state=0; _strbuf=sb; }
};




typedef ios::seek_dir _seek_dir;


 
 
 
 
 




















 
 
class streammarker {
    friend class streambuf;



    friend int __underflow(streambuf*);

    struct streammarker *_next;   
    streambuf *_sbuf;  
    streampos _spos;  
    void set_streampos(streampos sp) { _spos = sp; }
    void set_offset(int offset) { _pos = offset; _spos = (streampos)(-2); }
     
     
    int _pos;
  public:
    streammarker(streambuf *sb);
    ~streammarker();
    int saving() { return  _spos == -2; }
    int delta(streammarker&);
    int delta();
};

struct __streambuf {
     
    int _flags;		 
    char* _gptr;	 
    char* _egptr;	 
    char* _eback;	 
    char* _pbase;	 
    char* _pptr;	 
    char* _epptr;	 
    char* _base;	 
    char* _ebuf;	 
    struct streambuf *_chain;

     
    friend class streammarker;
    char *_other_gbase;  
    char *_aux_limit;   
    char *_other_egptr;  
    streammarker *_markers;


     
    unsigned short _cur_column;
    char _unused;
    char _shortbuf[1];
};

extern unsigned __adjust_column(unsigned start, const char *line, int count);

struct streambuf : private __streambuf {
    friend class ios;
    friend class istream;
    friend class ostream;
    friend class streammarker;



    friend int __underflow(streambuf*);

  protected:
    static streambuf* _list_all;  
    streambuf*& xchain() { return _chain; }
    void _un_link();
    void _link_in();
    char* gptr() const { return _gptr; }
    char* pptr() const { return _pptr; }
    char* egptr() const { return _egptr; }
    char* epptr() const { return _epptr; }
    char* pbase() const { return _pbase; }
    char* eback() const { return _eback; }
    char* base() const { return _base; }
    char* ebuf() const { return _ebuf; }
    int blen() const { return _ebuf - _base; }
    void xput_char(char c) { *_pptr++ = c; }
    int xflags() { return _flags; }
    int xflags(int f) { int fl = _flags; _flags = f; return fl; }
    void xsetflags(int f) { _flags |= f; }
    void xsetflags(int f, int mask) { _flags = (_flags & ~mask) | (f & mask); }
    void gbump(int n) { _gptr += n; }
    void pbump(int n) { _pptr += n; }
    void setb(char* b, char* eb, int a=0);
    void setp(char* p, char* ep) { _pbase=_pptr=p; _epptr=ep; }
    void setg(char* eb, char* g, char *eg) { _eback=eb; _gptr=g; _egptr=eg; }
    char *shortbuf() { return _shortbuf; }

    int in_backup() { return _flags & 0x100 ; }
     
    char *Gbase() { return in_backup() ? _other_gbase : _eback; }
     
    char *eGptr() { return in_backup() ? _other_egptr : _egptr; }
     
    char *Bbase() { return in_backup() ? _eback : _other_gbase; }
    char *Bptr() { return _aux_limit; }
     
    char *eBptr() { return in_backup() ? _egptr : _other_egptr; }
    char *Nbase() { return _other_gbase; }
    char *eNptr() { return _other_egptr; }
    int have_backup() { return _other_gbase != ((void *)0) ; }
    int have_markers() { return _markers != ((void *)0) ; }
    int _least_marker();
    void switch_to_main_get_area();
    void switch_to_backup_area();
    void free_backup_area();
    void unsave_markers();  
    int put_mode() { return _flags & 0x800 ; }
    int switch_to_get_mode();
    
    streambuf(int flags=0);
  public:
    static int flush_all();
    static void flush_all_linebuffered();  
    virtual int underflow() = 0;  
    virtual int overflow(int c = (-1) ) = 0;  
    virtual int doallocate();
    virtual streampos seekoff(streamoff, _seek_dir, int mode=ios::in|ios::out);
    virtual streampos seekpos(streampos pos, int mode = ios::in|ios::out);
    int seekmark(streammarker& mark, int delta = 0);
    int sputbackc(char c);
    int sungetc();
    virtual ~streambuf();
    int unbuffered() { return _flags & 2  ? 1 : 0; }
    int linebuffered() { return _flags & 0x200  ? 1 : 0; }
    void unbuffered(int i)
	{ if (i) _flags |= 2 ; else _flags &= ~2 ; }
    void linebuffered(int i)
	{ if (i) _flags |= 0x200 ; else _flags &= ~0x200 ; }
    int allocate() {  
	if (base() || unbuffered()) return 0;
	else return doallocate(); }
     
    void allocbuf() { if (base() == ((void *)0) ) doallocbuf(); }
    void doallocbuf();
    virtual int sync();
    virtual int pbackfail(int c);
    virtual streambuf* setbuf(char* p, int len);
    int in_avail() { return _egptr - _gptr; }
    int out_waiting() { return _pptr - _pbase; }
    virtual int xsputn(const char* s, int n);
    int sputn(const char* s, int n) { return xsputn(s, n); }
    int padn(char pad, int n);  
    virtual int xsgetn(char* s, int n);
    int sgetn(char* s, int n) { return xsgetn(s, n); }
    int ignore(int);
    virtual int get_column();
    virtual int set_column(int);
    long sgetline(char* buf, _G_size_t n, char delim, int putback_delim);
    int sbumpc() {
	if (_gptr >= _egptr && __underflow(this) == (-1) ) return (-1) ;
	else return *(unsigned char*)_gptr++; }
    int sgetc() {
	if (_gptr >= _egptr && __underflow(this) == (-1) ) return (-1) ;
	else return *(unsigned char*)_gptr; }
    int snextc() {
	if (_gptr >= _egptr && __underflow(this) == (-1) ) return (-1) ;
	return _gptr++, sgetc(); }
    int sputc(int c) {
	if (_pptr >= _epptr) return __overflow(this, (unsigned char)c);
	else return *_pptr++ = c, (unsigned char)c; }
    void stossc() { if (_gptr < _egptr) _gptr++; }
    int vscan(char const *fmt0, _G_va_list ap, ios* stream = ((void *)0) );
    int scan(char const *fmt0 ...);
    int vform(char const *fmt0, _G_va_list ap);
    int form(char const *fmt0 ...);




};

 
 

 
 
 
 

class backupbuf : public streambuf {
    friend class streammarker;
  protected:
    backupbuf(int flags=0) : streambuf(flags| 0x4000 ) { }
  public:
    virtual int pbackfail(int c);
    virtual int underflow();
    virtual int overflow(int c = (-1) );
};

struct __file_fields {
    short _fileno;
    int _blksize;
    _G_fpos_t  _offset;
 
};

class filebuf : public backupbuf {
  protected:
    struct __file_fields _fb;
    void init();
  public:
    static const int openprot;  
    filebuf();
    filebuf(int fd);
    filebuf(int fd, char* p, int len);
    ~filebuf();
    filebuf* attach(int fd);
    filebuf* open(const char *filename, const char *mode);
    filebuf* open(const char *filename, ios::openmode mode, int prot = 0664);
    virtual int underflow();
    virtual int overflow(int c = (-1) );
    int is_open() const { return _fb._fileno >= 0; }
    int fd() const { return is_open() ? _fb._fileno : (-1) ; }
    filebuf* close();
    virtual int doallocate();
    virtual streampos seekoff(streamoff, _seek_dir, int mode=ios::in|ios::out);
    virtual streambuf* setbuf(char* p, int len);
    int xsputn(const char* s, int n);
    int xsgetn(char* s, int n);
    virtual int sync();
  protected:  
 
    int is_reading() { return eback() != egptr(); }
    char* cur_ptr() { return is_reading() ?  gptr() : pptr(); }
     
    char* file_ptr() { return eGptr(); }
    int do_write(const char *data, int to_do);
    int do_flush() { return do_write(_pbase, _pptr-_pbase); }
     
    virtual _G_ssize_t sys_read(char* buf, _G_size_t size);
    virtual _G_fpos_t  sys_seek(_G_fpos_t , _seek_dir);
    virtual _G_ssize_t sys_write(const void*, long);
    virtual int sys_stat(void*);  
    virtual int sys_close();
};

inline ios::ios(streambuf* sb  , ostream* tie  ) {
		_state = sb ? ios::goodbit : ios::badbit; _exceptions=0;
		_strbuf=sb; _tie = tie; _width=0; _fill=' ';
		_flags=ios::skipws|ios::dec; _precision=6; }
inline ios::~ios() {
    if (!(_flags & (unsigned int)ios::dont_close)) delete _strbuf; }




class istream; class ostream;
typedef ios& (*__manip)(ios&);
typedef istream& (*__imanip)(istream&);
typedef ostream& (*__omanip)(ostream&);

extern istream& ws(istream& ins);
extern ostream& flush(ostream& outs);
extern ostream& endl(ostream& outs);
extern ostream& ends(ostream& outs);

class ostream : virtual public ios
{
     
    void do_osfx();
  public:
    ostream() { }
    ostream(streambuf* sb, ostream* tied=((void *)0) );
    int opfx() {
	if (!good()) return 0; else { if (_tie) _tie->flush(); return 1;} }
    void osfx() { if (flags() & (ios::unitbuf|ios::stdio))
		      do_osfx(); }
    streambuf* ostreambuf() const { return _strbuf; }
    ostream& flush();
    ostream& put(char c) { _strbuf->sputc(c); return *this; }
    ostream& put(unsigned char c) { return put((char)c); }

    ostream& write(const char *s, int n);
    ostream& write(const unsigned char *s, int n) { return write((const char*)s, n);}

    ostream& put(signed char c) { return put((char)c); }
    ostream& write(const signed char *s, int n) { return write((const char*)s, n);}

    ostream& write(const void *s, int n) { return write((const char*)s, n);}
    ostream& seekp(streampos);
    ostream& seekp(streamoff, _seek_dir);
    streampos tellp();
    ostream& form(const char *format ...);
    ostream& vform(const char *format, _G_va_list args);

    ostream& operator<<(char c);
    ostream& operator<<(unsigned char c) { return (*this) << (char)c; }

    ostream& operator<<(signed char c) { return (*this) << (char)c; }

    ostream& operator<<(const char *s);
    ostream& operator<<(const unsigned char *s)
	{ return (*this) << (const char*)s; }

    ostream& operator<<(const signed char *s)
	{ return (*this) << (const char*)s; }

    ostream& operator<<(void *p);
    ostream& operator<<(int n);
    ostream& operator<<(unsigned int n);
    ostream& operator<<(long n);
    ostream& operator<<(unsigned long n);

    ostream& operator<<(long long n);
    ostream& operator<<(unsigned long long n);

    ostream& operator<<(short n) {return operator<<((int)n);}
    ostream& operator<<(unsigned short n) {return operator<<((unsigned int)n);}
    ostream& operator<<(double n);
    ostream& operator<<(float n) { return operator<<((double)n); }
    ostream& operator<<(__omanip func) { return (*func)(*this); }
    ostream& operator<<(__manip func) {(*func)(*this); return *this;}
    ostream& operator<<(streambuf*);
};

class istream : virtual public ios
{
     
    _G_ssize_t _gcount;

    int _skip_ws();
  public:
    istream() { _gcount = 0; }
    istream(streambuf* sb, ostream*tied=((void *)0) );
    streambuf* istreambuf() const { return _strbuf; }
    istream& get(char* ptr, int len, char delim = '\n');
    istream& get(unsigned char* ptr, int len, char delim = '\n')
	{ return get((char*)ptr, len, delim); }
    istream& get(char& c);
    istream& get(unsigned char& c) { return get((char&)c); }
    istream& getline(char* ptr, int len, char delim = '\n');
    istream& getline(unsigned char* ptr, int len, char delim = '\n')
	{ return getline((char*)ptr, len, delim); }

    istream& get(signed char& c)  { return get((char&)c); }
    istream& get(signed char* ptr, int len, char delim = '\n')
	{ return get((char*)ptr, len, delim); }
    istream& getline(signed char* ptr, int len, char delim = '\n')
	{ return getline((char*)ptr, len, delim); }

    istream& read(char *ptr, int n);
    istream& read(unsigned char *ptr, int n) { return read((char*)ptr, n); }

    istream& read(signed char *ptr, int n) { return read((char*)ptr, n); }

    istream& read(void *ptr, int n) { return read((char*)ptr, n); }
     
    istream& get(streambuf& sb, char delim = '\n');
    istream& gets(char **s, char delim = '\n');
    int ipfx(int need) {
	if (!good()) { set(ios::failbit); return 0; }
	if (_tie && (need == 0 || rdbuf()->in_avail() < need)) _tie->flush();
	if (!need && (flags() & ios::skipws)) return _skip_ws();
	return 1;
    }
    int ipfx0() {  
	if (!good()) { set(ios::failbit); return 0; }
	if (_tie) _tie->flush();
	if (flags() & ios::skipws) return _skip_ws();
	return 1;
    }
    int ipfx1() {  
	if (!good()) { set(ios::failbit); return 0; }
	if (_tie && rdbuf()->in_avail() == 0) _tie->flush();
	return 1;
    }
    int get() { if (!ipfx1()) return (-1) ;
		int ch = _strbuf->sbumpc();
		if (ch == (-1) ) set(ios::eofbit);
		return ch; }
    int peek() { if (!ipfx1()) return (-1) ;
		int ch = _strbuf->sgetc();
		if (ch == (-1) ) set(ios::eofbit);
		return ch; }
    _G_ssize_t gcount() { return _gcount; }
    istream& ignore(int n=1, int delim = (-1) );
    istream& seekg(streampos);
    istream& seekg(streamoff, _seek_dir);
    streampos tellg();
    istream& putback(char ch) {
	if (good() && _strbuf->sputbackc(ch) == (-1) ) clear(ios::badbit);
	return *this;}
    istream& unget() {
	if (good() && _strbuf->sungetc() == (-1) ) clear(ios::badbit);
	return *this;}
    istream& scan(const char *format ...);
    istream& vscan(const char *format, _G_va_list args);





    istream& operator>>(char*);
    istream& operator>>(unsigned char* p) { return operator>>((char*)p); }

    istream& operator>>(signed char*p) { return operator>>((char*)p); }

    istream& operator>>(char& c);
    istream& operator>>(unsigned char& c) {return operator>>((char&)c);}

    istream& operator>>(signed char& c) {return operator>>((char&)c);}

    istream& operator>>(int&);
    istream& operator>>(long&);

    istream& operator>>(long long&);

    istream& operator>>(short&);
    istream& operator>>(unsigned int&);
    istream& operator>>(unsigned long&);

    istream& operator>>(unsigned long long&);

    istream& operator>>(unsigned short&);
    istream& operator>>(float&);
    istream& operator>>(double&);
    istream& operator>>( __manip func) {(*func)(*this); return *this;}
    istream& operator>>(__imanip func) { return (*func)(*this); }
    istream& operator>>(streambuf*);
};


class iostream : public istream, public ostream
{
    _G_ssize_t _gcount;
  public:
    iostream() { _gcount = 0; }
    iostream(streambuf* sb, ostream*tied=((void *)0) );
};

extern istream cin;
extern ostream cout, cerr, clog;  

struct Iostream_init { } ;   

inline ios& dec(ios& i)
{ i.setf(ios::dec, ios::dec|ios::hex|ios::oct); return i; }
inline ios& hex(ios& i)
{ i.setf(ios::hex, ios::dec|ios::hex|ios::oct); return i; }
inline ios& oct(ios& i)
{ i.setf(ios::oct, ios::dec|ios::hex|ios::oct); return i; }




class Int
{
	public:
		Int(void);
		Int(int);
		Int(const Int&);
	
		Int* copy(void) const;
		
		operator int&();
		
		Int& operator ++(void);
		Int& operator --(void);
		
	private:
		int value;
};



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






main()
{
  Int data = 2;
  Int test;

  test = data * 12;

  cout << "data = " << data << "\n";

  data += 1;
  cout << data << "\n";
  cout << "Test = "<< test << "\n";
}

// UNKNOWN "FAIL"
