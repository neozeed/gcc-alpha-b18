// Build don't link:

template<class Repr>
class syHandle
{
protected:
  syHandle();
  ~syHandle();
  Repr *_repr;
};

template<class Repr>
syHandle<Repr>::~syHandle()
{
}

typedef char * char_ptr_t;
syHandle<char_ptr_t>::syHandle() 
{
    _repr = 0;
}

syHandle<char_ptr_t>::~syHandle() 
{
    _repr = 0;
}
