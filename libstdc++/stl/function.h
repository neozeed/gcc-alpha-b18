/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#include <stddef.h>
#ifndef __GNUG__
#include <bool.h>
#endif

template <class T>
inline bool operator!=(const T& x, const T& y) {
    return !(x == y);
}

template <class T>
inline bool operator>(const T& x, const T& y) {
    return y < x;
}

template <class T>
inline bool operator<=(const T& x, const T& y) {
    return !(y < x);
}

template <class T>
inline bool operator>=(const T& x, const T& y) {
    return !(x < y);
}

template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};      

template <class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};

template <class T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x - y; }
};

template <class T>
struct multiplies : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x * y; }
};

template <class T>
struct divides : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x / y; }
};

template <class T>
struct modulus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x % y; }
};

template <class T>
struct negate : public unary_function<T, T> {
    T operator()(const T& x) const { return -x; }
};

template <class T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

template <class T>
struct not_equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x != y; }
};

template <class T>
struct greater : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x > y; }
};

template <class T>
struct less : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x < y; }
};

template <class T>
struct greater_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x >= y; }
};

template <class T>
struct less_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x <= y; }
};

template <class T>
struct logical_and : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x && y; }
};

template <class T>
struct logical_or : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x || y; }
};

template <class T>
struct logical_not : public unary_function<T, bool> {
    bool operator()(const T& x) const { return !x; }
};

template <class Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type, bool> {
protected:
    Predicate pred;
public:
    unary_negate(const Predicate& x) : pred(x) {}
    bool operator()(const argument_type& x) const { return !pred(x); }
};

template <class Predicate>
unary_negate<Predicate> not1(const Predicate& pred) {
    return unary_negate<Predicate>(pred);
}

template <class Predicate> 
class binary_negate 
    : public binary_function<typename Predicate::first_argument_type,
			     typename Predicate::second_argument_type, bool> {
protected:
    Predicate pred;
public:
    binary_negate(const Predicate& x) : pred(x) {}
    bool operator()(const first_argument_type& x, 
		    const second_argument_type& y) const {
	return !pred(x, y); 
    }
};

template <class Predicate>
binary_negate<Predicate> not2(const Predicate& pred) {
    return binary_negate<Predicate>(pred);
}

template <class Operation> 
class binder1st : public unary_function<typename Operation::second_argument_type,
					typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    binder1st(const Operation& x, const typename Operation::first_argument_type& y)
	: op(x), value(y) {}
    result_type operator()(const argument_type& x) const {
	return op(value, x); 
    }
};

template <class Operation, class T>
binder1st<Operation> bind1st(const Operation& op, const T& x) {
    return binder1st<Operation>(op, typename Operation::first_argument_type(x));
}

template <class Operation> 
class binder2nd : public unary_function<typename Operation::first_argument_type,
					typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    binder2nd(const Operation& x, const typename Operation::second_argument_type& y) 
	: op(x), value(y) {}
    result_type operator()(const argument_type& x) const {
	return op(x, value); 
    }
};

template <class Operation, class T>
binder2nd<Operation> bind2nd(const Operation& op, const T& x) {
    return binder2nd<Operation>(op, typename Operation::second_argument_type(x));
}

template <class Operation1, class Operation2>
class unary_compose : public unary_function<typename Operation2::argument_type,
                                            typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
public:
    unary_compose(const Operation1& x, const Operation2& y) : op1(x), op2(y) {}
    result_type operator()(const argument_type& x) const {
	return op1(op2(x));
    }
};

template <class Operation1, class Operation2>
unary_compose<Operation1, Operation2> compose1(const Operation1& op1, 
					       const Operation2& op2) {
    return unary_compose<Operation1, Operation2>(op1, op2);
}

template <class Operation1, class Operation2, class Operation3>
class binary_compose : public unary_function<typename Operation2::argument_type,
                                             typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
    Operation3 op3;
public:
    binary_compose(const Operation1& x, const Operation2& y, 
		   const Operation3& z) : op1(x), op2(y), op3(z) { }
    result_type operator()(const argument_type& x) const {
	return op1(op2(x), op3(x));
    }
};

template <class Operation1, class Operation2, class Operation3>
binary_compose<Operation1, Operation2, Operation3> 
compose2(const Operation1& op1, const Operation2& op2, const Operation3& op3) {
    return binary_compose<Operation1, Operation2, Operation3>(op1, op2, op3);
}

template <class Arg, class Result>
class pointer_to_unary_function : public unary_function<Arg, Result> {
protected:
    Result (*ptr)(Arg);
public:
    pointer_to_unary_function() {}
    pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) {}
    Result operator()(Arg x) const { return ptr(x); }
};

template <class Arg, class Result>
pointer_to_unary_function<Arg, Result> ptr_fun(Result (*x)(Arg)) {
    return pointer_to_unary_function<Arg, Result>(x);
}

template <class Arg1, class Arg2, class Result>
class pointer_to_binary_function : public binary_function<Arg1, Arg2, Result> {
protected:
    Result (*ptr)(Arg1, Arg2);
public:
    pointer_to_binary_function() {}
    pointer_to_binary_function(Result (*x)(Arg1, Arg2)) : ptr(x) {}
    Result operator()(Arg1 x, Arg2 y) const { return ptr(x, y); }
};

template <class Arg1, class Arg2, class Result>
pointer_to_binary_function<Arg1, Arg2, Result> 
ptr_fun(Result (*x)(Arg1, Arg2)) {
    return pointer_to_binary_function<Arg1, Arg2, Result>(x);
}

template <class T>
struct identity : public unary_function<T, T> {
    const T& operator()(const T& x) const { return x; }
};

template <class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
  const typename Pair::first_type& operator()(const Pair& x) const
  {
    return x.first;
  }
};

template <class Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type> {
  const typename Pair::second_type& operator()(const Pair& x) const
  {
    return x.second;
  }
};

template <class Arg1, class Arg2>
struct project1st : public binary_function<Arg1, Arg2, Arg1> {
  Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
};

template <class Arg1, class Arg2>
struct project2nd : public binary_function<Arg1, Arg2, Arg2> {
  Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
};

template <class Result>
struct constant_void_fun
{
  typedef Result result_type;
  result_type val;
  constant_void_fun(const result_type& v) : val(v) {}
  const result_type& operator()() const { return val; }
};  

template <class Result, class Argument = Result>
struct constant_unary_fun : public unary_function<Argument, Result> {
  result_type val;
  constant_unary_fun(const result_type& v) : val(v) {}
  const result_type& operator()(const argument_type&) const { return val; }
};

template <class Result, class Arg1 = Result, class Arg2 = Arg1>
struct constant_binary_fun : public binary_function<Arg1, Arg2, Result> {
  result_type val;
  constant_binary_fun(const result_type& v) : val(v) {}
  const result_type& operator()(const first_argument_type&, 
                                const second_argument_type&) const {
    return val;
  }
};

template <class Result>
inline constant_void_fun<Result> constant0(const Result& val)
{
  return constant_void_fun<Result>(val);
}

template <class Result>
inline constant_unary_fun<Result> constant1(const Result& val)
{
  return constant_unary_fun<Result>(val);
}

template <class Result>
inline constant_binary_fun<Result> constant2(const Result& val)
{
  return constant_binary_fun<Result>(val);
}

// Note: this code assumes that int is 32 bits.
class subtractive_rng : public unary_function<unsigned int, unsigned int> {
private:
  unsigned int table[55];
  size_t index1;
  size_t index2;
public:
  unsigned int operator()(unsigned int limit) {
    index1 = (index1 + 1) % 55;
    index2 = (index2 + 1) % 55;
    table[index1] = table[index1] - table[index2];
    return table[index1] % limit;
  }

  void initialize(unsigned int seed)
  {
    unsigned int k = 1;
    table[54] = seed;
    size_t i;
    for (i = 0; i < 54; i++) {
        size_t ii = (21 * (i + 1) % 55) - 1;
        table[ii] = k;
        k = seed - k;
        seed = table[ii];
    }
    for (int loop = 0; loop < 4; loop++) {
        for (i = 0; i < 55; i++)
            table[i] = table[i] - table[(1 + i + 30) % 55];
    }
    index1 = 0;
    index2 = 31;
  }

  subtractive_rng(unsigned int seed) { initialize(seed); }
  subtractive_rng() { initialize(161803398u); }
};


#endif
