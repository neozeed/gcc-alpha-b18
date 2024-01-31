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

#ifndef __SGI_STL_LIST_H
#define __SGI_STL_LIST_H

#include <stddef.h>
#include <algobase.h>
#include <iterator.h>
#include <alloc.h>

template <class T> struct __list_iterator;
template <class T> struct __list_const_iterator;

template <class T>
struct __list_node {
  typedef void* void_pointer;
  void_pointer next;
  void_pointer prev;
  T data;
};

template<class T>
struct __list_iterator {
  typedef __list_iterator<T> iterator;
  typedef __list_const_iterator<T> const_iterator;
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef __list_node<T>* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  link_type node;

  __list_iterator(link_type x) : node(x) {}
  __list_iterator() {}
  bool operator==(const iterator& x) const { return node == x.node; }
  bool operator!=(const iterator& x) const { return node != x.node; }
  reference operator*() const { return (*node).data; }
  iterator& operator++() { 
    node = (link_type)((*node).next);
    return *this;
  }
  iterator operator++(int) { 
    iterator tmp = *this;
    ++*this;
    return tmp;
  }
  iterator& operator--() { 
    node = (link_type)((*node).prev);
    return *this;
  }
  iterator operator--(int) { 
    iterator tmp = *this;
    --*this;
    return tmp;
  }
};

template<class T>
struct __list_const_iterator {
  typedef __list_iterator<T> iterator;
  typedef __list_const_iterator<T> const_iterator;
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef __list_node<T>* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  link_type node;

  __list_const_iterator(link_type x) : node(x) {}
  __list_const_iterator() {}
  __list_const_iterator(const iterator& x) : node(x.node) {}
  bool operator==(const const_iterator& x) const { return node == x.node; } 
  bool operator!=(const const_iterator& x) const { return node != x.node; } 
  const_reference operator*() const { return (*node).data; }
  const_iterator& operator++() { 
    node = (link_type)((*node).next);
    return *this;
  }
  const_iterator operator++(int) { 
    const_iterator tmp = *this;
    ++*this;
    return tmp;
  }
  const_iterator& operator--() { 
    node = (link_type)((*node).prev);
    return *this;
  }
  const_iterator operator--(int) { 
    const_iterator tmp = *this;
    --*this;
    return tmp;
  }
};

template <class T>
inline bidirectional_iterator_tag
iterator_category(const __list_iterator<T>&) {
  return bidirectional_iterator_tag();
}

template <class T>
inline __list_iterator<T>::value_type*
value_type(const  __list_iterator<T>&) {
  return (__list_iterator<T>::value_type*) 0;
}

template <class T>
inline __list_iterator<T>::difference_type*
distance_type(const  __list_iterator<T>&) {
  return (__list_iterator<T>::difference_type*) 0;
}

template <class T>
inline bidirectional_iterator_tag
iterator_category(const  __list_const_iterator<T>&) {
  return bidirectional_iterator_tag();
}

template <class T>
inline __list_const_iterator<T>::value_type*
value_type(const __list_const_iterator<T>&) {
  return (__list_const_iterator<T>::value_type*) 0;
}

template <class T>
inline __list_const_iterator<T>::difference_type*
distance_type(const __list_const_iterator<T>&) {
  return (__list_const_iterator<T>::difference_type*) 0;
}


template <class T, class Alloc = alloc>
class list {
protected:
    typedef void* void_pointer;
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:      
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }

protected:
    link_type node;
    size_type length;
public:
    typedef __list_iterator<T> iterator;
    typedef __list_const_iterator<T> const_iterator;

    typedef reverse_bidirectional_iterator<const_iterator, value_type,
                                           const_reference, difference_type>
	const_reverse_iterator;
    typedef reverse_bidirectional_iterator<iterator, value_type, reference,
                                           difference_type>
        reverse_iterator; 

public:
    list() : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
    }
    iterator begin() { return (link_type)((*node).next); }
    const_iterator begin() const { return (link_type)((*node).next); }
    iterator end() { return node; }
    const_iterator end() const { return node; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { 
        return const_reverse_iterator(end()); 
    }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { 
        return const_reverse_iterator(begin());
    } 
    bool empty() const { return length == 0; }
    size_type size() const { return length; }
    size_type max_size() const { return size_type(-1); }
    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(--end()); }
    const_reference back() const { return *(--end()); }
    void swap(list<T, Alloc>& x) {
	::swap(node, x.node);
	::swap(length, x.length);
    }
    iterator insert(iterator position, const T& x) {
	link_type tmp = get_node();
	construct(&((*tmp).data), x);
	(*tmp).next = position.node;
	(*tmp).prev = (*position.node).prev;
	(*(link_type((*position.node).prev))).next = tmp;
	(*position.node).prev = tmp;
	++length;
	return tmp;
    }
    iterator insert(iterator position) { return insert(position, T()); }
    void insert(iterator position, const T* first, const T* last);
    void insert(iterator position, const_iterator first,
		const_iterator last);
    void insert(iterator position, size_type n, const T& x);
    void push_front(const T& x) { insert(begin(), x); }
    void push_back(const T& x) { insert(end(), x); }
    void erase(iterator position) {
	(*(link_type((*position.node).prev))).next = (*position.node).next;
	(*(link_type((*position.node).next))).prev = (*position.node).prev;
	destroy(&(*position.node).data);
	put_node(position.node);
	--length;
    }
    void erase(iterator first, iterator last);
    void resize(size_type new_size, const T& x);
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear();

    void pop_front() { erase(begin()); }
    void pop_back() { 
	iterator tmp = end();
	erase(--tmp);
    }
    list(size_type n, const T& value) : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
	insert(begin(), n, value);
    }
    list(size_type n) : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
	insert(begin(), n, T());
    }
    list(const T* first, const T* last) : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
	insert(begin(), first, last);
    }
    list(const_iterator first, const_iterator last) : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
	insert(begin(), first, last);
    }
    list(const list<T, Alloc>& x) : length(0) {
	node = get_node();
	(*node).next = node;
	(*node).prev = node;
	insert(begin(), x.begin(), x.end());
    }
    ~list() {
        clear();
	put_node(node);
    }
    list<T, Alloc>& operator=(const list<T, Alloc>& x);

protected:
    void transfer(iterator position, iterator first, iterator last) {
      if (position != last) {
	(*(link_type((*last.node).prev))).next = position.node;
	(*(link_type((*first.node).prev))).next = last.node;
	(*(link_type((*position.node).prev))).next = first.node;  
	link_type tmp = link_type((*position.node).prev);
	(*position.node).prev = (*last.node).prev;
	(*last.node).prev = (*first.node).prev; 
	(*first.node).prev = tmp;
      }
    }

public:
    void splice(iterator position, list<T, Alloc>& x) {
	if (!x.empty()) {
	    transfer(position, x.begin(), x.end());
	    length += x.length;
	    x.length = 0;
	}
    }
    void splice(iterator position, list<T, Alloc>& x, iterator i) {
	iterator j = i;
	if (position == i || position == ++j) return;
	transfer(position, i, j);
	++length;
	--x.length;
    }
    void splice(iterator position, list<T, Alloc>& x, iterator first, iterator last) {
	if (first != last) {
	    if (&x != this) {
		difference_type n = 0;
	    	distance(first, last, n);
	    	x.length -= n;
	    	length += n;
	    }
	    transfer(position, first, last);
	}
    }
    void remove(const T& value);
    void unique();
    void merge(list<T, Alloc>& x);
    void reverse();
    void sort();
};

template <class T, class Alloc>
inline bool operator==(const list<T, Alloc>& x, const list<T, Alloc>& y) {
    return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc>
inline bool operator<(const list<T, Alloc>& x, const list<T, Alloc>& y) {
    return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position, const T* first, const T* last) {
    while (first != last) insert(position, *first++);
}
	 
template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position, const_iterator first,
		     const_iterator last) {
    while (first != last) insert(position, *first++);
}

template <class T, class Alloc>
void list<T, Alloc>::insert(iterator position, size_type n, const T& x) {
    while (n--) insert(position, x);
}

template <class T, class Alloc>
void list<T, Alloc>::erase(iterator first, iterator last) {
    while (first != last) erase(first++);
}

template <class T, class Alloc>
void list<T, Alloc>::resize(size_type new_size, const T& x)
{
  if (new_size < size()) {
    iterator f;
    if (new_size < size() / 2) {
      f = begin();
      advance(f, new_size);
    }
    else {
      f = end();
      advance(f, difference_type(size()) - difference_type(new_size));
    }
    erase(f, end());
  }
  else
    insert(end(), new_size - size(), x);
}

template <class T, class Alloc> 
void list<T, Alloc>::clear()
{
  link_type cur = (link_type) node->next;
  while (cur != node) {
    link_type tmp = cur;
    cur = (link_type) cur->next;
    destroy(&(tmp->data));
    put_node(tmp);
  }
  node->next = node;
  node->prev = node;
  length = 0;
}

template <class T, class Alloc>
list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& x) {
    if (this != &x) {
	iterator first1 = begin();
	iterator last1 = end();
	const_iterator first2 = x.begin();
	const_iterator last2 = x.end();
	while (first1 != last1 && first2 != last2) *first1++ = *first2++;
	if (first2 == last2)
	    erase(first1, last1);
	else
	    insert(last1, first2, last2);
    }
    return *this;
}

template <class T, class Alloc>
void list<T, Alloc>::remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
	iterator next = first;
	++next;
	if (*first == value) erase(first);
	first = next;
    }
}

template <class T, class Alloc>
void list<T, Alloc>::unique() {
    iterator first = begin();
    iterator last = end();
    if (first == last) return;
    iterator next = first;
    while (++next != last) {
	if (*first == *next)
	    erase(next);
	else
	    first = next;
	next = first;
    }
}

template <class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x) {
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();
    while (first1 != last1 && first2 != last2)
	if (*first2 < *first1) {
	    iterator next = first2;
	    transfer(first1, first2, ++next);
	    first2 = next;
	} else
	    ++first1;
    if (first2 != last2) transfer(last1, first2, last2);
    length += x.length;
    x.length= 0;
}

template <class T, class Alloc>
void list<T, Alloc>::reverse() {
    if (size() < 2) return;
    for (iterator first = ++begin(); first != end();) {
	iterator old = first++;
	transfer(begin(), old, first);
    }
}    

template <class T, class Alloc>
void list<T, Alloc>::sort() {
    if (size() < 2) return;
    list<T, Alloc> carry;
    list<T, Alloc> counter[64];
    int fill = 0;
    while (!empty()) {
	carry.splice(carry.begin(), *this, begin());
	int i = 0;
	while(i < fill && !counter[i].empty()) {
	    counter[i].merge(carry);
	    carry.swap(counter[i++]);
	}
	carry.swap(counter[i]);         
	if (i == fill) ++fill;
    } 

    for (int i = 1; i < fill; ++i) counter[i].merge(counter[i-1]);
    swap(counter[fill-1]);
}

#endif /* __SGI_STL_LIST_H */
