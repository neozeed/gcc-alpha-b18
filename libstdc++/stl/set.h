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

#ifndef SET_H
#define SET_H

#include <tree.h>

template <class Key, class Compare = less<Key>, class Alloc = alloc>
class set {
public:
// typedefs:

    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
private:
    typedef rb_tree<key_type, value_type, 
                    identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;  // red-black tree representing set
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

    set(const Compare& comp = Compare()) : t(comp) {}
    set(const value_type* first, const value_type* last, 
        const Compare& comp = Compare()) : t(comp) {
          t.insert_unique(first, last);
    }
    set(const_iterator first, const_iterator last, 
        const Compare& comp = Compare()) : t(comp) {
          t.insert_unique(first, last);
    }
    set(const set<Key, Compare, Alloc>& x) : t(x.t) {}
    set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x) { 
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
    void swap(set<Key, Compare, Alloc>& x) { t.swap(x.t); }

// insert/erase
    typedef  pair<iterator, bool> pair_iterator_bool; 
    pair<iterator,bool> insert(const value_type& x) { 
        pair<rep_type::iterator, bool> p = t.insert_unique(x); 
        return pair<iterator, bool>(p.first, p.second);
    }
    iterator insert(iterator position, const value_type& x) {
        return t.insert_unique((rep_type::iterator&)position, x);
    }
    void insert(const_iterator first, const_iterator last) {
      t.insert_unique(first, last);
    }
    void insert(const value_type* first, const value_type* last) {
      t.insert_unique(first, last);
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

// set operations:

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
  friend bool operator==(const set&, const set&);
  friend bool operator<(const set&, const set&);
};

template <class Key, class Compare, class Alloc>
inline bool operator==(const set<Key, Compare, Alloc>& x, 
                       const set<Key, Compare, Alloc>& y) {
  return x.t == y.t;
}

template <class Key, class Compare, class Alloc>
inline bool operator<(const set<Key, Compare, Alloc>& x, 
                      const set<Key, Compare, Alloc>& y) {
  return x.t < y.t;
}

#endif
