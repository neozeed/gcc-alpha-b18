// Build don't link: 
// GROUPS passed templates
// excess errors test - XFAIL *-*-*
template<class T>
class Vector
{
  int sz;
  T *v;
public:
  Vector (int s) : sz (s) { v = new T[sz]; }
  ~Vector () { delete[] v; }
  T &operator[] (int i) { return v[i]; }
  int size () { return sz; }
};

template<class T>
struct Comparator
{
  typedef T T;
  static lessthan (T &a, T &b) { return a < b; }
};

template<class Comp>
struct Sort
{
  static void sort (Vector<Comp::T> &);
};

template<class Comp>
void Sort<Comp>::sort (Vector<Comp::T> &v)
{
  int n = v.size ();

  for (int i = 0; i < n - 1; i++)
    for (int j = n - 1; i < j; j--)
      if (Comp::lessthan (v[j], v[j - 1]))
	{
	  Comp::T temp = v[j];
	  v[j] = v[j - 1];
	  v[j - 1] = temp;
	}
}

void
f (Vector<int> &vi)
{
  Sort<Comparator<int> >::sort (vi);
}
