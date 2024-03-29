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

#ifndef MULTISET_H
#define MULTISET_H

#include <tree.h>

template <class Key, class Compare = less<Key>, class Alloc = alloc>
class multiset {
public:
// typedefs:

    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
private:
    typedef rb_tree<key_type, value_type, 
                    identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;  // red-black tree representing multiset
public:
    typedef rep_type::const_reference reference;
    typedef rep_type::const_reference const_reference;
    typedef rep_type::const_iterator iterator;
    typedef rep_type::const_iterator const_iterator;
    typedef rep_type::const_reverse_iterator reverse_iterator;
    typedef rep_type::const_reverse_iterator const_reverse_iterator;
    typedef rep_type::size_type size_type;
    typedef rep_type::difference_type difference_type;

// allocation/deallocation

    multiset(const Compare& comp = Compare()) : t(comp) {}
    multiset(const value_type* first, const value_type* last, 
             const Compare& comp = Compare()) : t(comp) {
               t.insert_equal(first, last);
    }
    multiset(const_iterator first, const_iterator last, 
             const Compare& comp = Compare()) : t(comp) {
               t.insert_equal(first, last);
    }
    multiset(const multiset<Key, Compare, Alloc>& x) : t(x.t) {}
    multiset<Key, Compare, Alloc>&
    operator=(const multiset<Key, Compare, Alloc>& x) {
        t = x.t; 
        return *this;
    }

// accessors:

    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return t.key_comp(); }
    iterator begin() const { return t.begin(); }
    iterator end() const { return t.end(); }
    reverse_iterator rbegin() const { return t.rbegin(); } 
    reverse_iterator rend() const { return t.rend(); }
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }
    void swap(multiset<Key, Compare, Alloc>& x) { t.swap(x.t); }

// insert/erase
    iterator insert(const value_type& x) { 
      return t.insert_equal(x);
    }
    iterator insert(iterator position, const value_type& x) {
      return t.insert_equal((rep_type::iterator&)position, x);
    }
    void insert(const value_type* first, const value_type* last) {
      t.insert_equal(first, last);
    }
    void insert(const_iterator first, const_iterator last) {
      t.insert_equal(first, last);
    }
    void erase(iterator position) { 
        t.erase((rep_type::iterator&)position); 
    }
    size_type erase(const key_type& x) { 
        return t.erase(x); 
    }
    void erase(iterator first, iterator last) { 
        t.erase((rep_type::iterator&)first, 
                (rep_type::iterator&)last); 
    }
    void clear() { t.clear(); }

// multiset operations:

    iterator find(const key_type& x) const { return t.find(x); }
    size_type count(const key_type& x) const { return t.count(x); }
    iterator lower_bound(const key_type& x) const {
        return t.lower_bound(x);
    }
    iterator upper_bound(const key_type& x) const {
        return t.upper_bound(x); 
    }
    pair<iterator,iterator> equal_range(const key_type& x) const {
        return t.equal_range(x);
    }
  friend bool operator==(const multiset&, const multiset&);
  friend bool operator<(const multiset&, const multiset&);
};

template <class Key, class Compare, class Alloc>
inline bool operator==(const multiset<Key, Compare, Alloc>& x, 
                       const multiset<Key, Compare, Alloc>& y) {
  return x.t == y.t;
}

template <class Key, class Compare, class Alloc>
inline bool operator<(const multiset<Key, Compare, Alloc>& x, 
                      const multiset<Key, Compare, Alloc>& y) {
  return x.t < y.t;
}

#endif
