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

#ifndef __SGI_STL_DEQUE_H
#define __SGI_STL_DEQUE_H

#include <stddef.h>
#include <algobase.h>
#include <alloc.h>

inline size_t __deque_buf_size(size_t sz)
{
  return sz < 4096 ? size_t(4096 / sz) : size_t(1);
}

template <class T> struct __deque_iterator;
template <class T> struct __deque_const_iterator;

template <class T>
struct __deque_iterator {
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef pointer* map_pointer;
  typedef __deque_iterator<T> iterator;
  typedef __deque_const_iterator<T> const_iterator;

  pointer current;
  pointer first;
  pointer last;
  map_pointer node;

  static size_type buffer_size() {
    return __deque_buf_size(sizeof(value_type)); }

  __deque_iterator(pointer x, map_pointer y) 
    : current(x), first(*y), last(*y + buffer_size()), node(y) {}
  __deque_iterator() : current(0), first(0), last(0), node(0) {}
  reference operator*() const { return *current; }
  difference_type operator-(const iterator& x) const {
    return node == x.node 
      ? current - x.current 
      : difference_type(buffer_size() * (node - x.node - 1) +
                        (current - first) + (x.last - x.current));
  }
  iterator& operator++() {
    if (++current == last) {
      first = *(++node);
      current = first;
      last = first + buffer_size();
    }
    return *this; 
  }
  iterator operator++(int)  {
    iterator tmp = *this;
    ++*this;
    return tmp;
  }
  iterator& operator--() {
    if (current == first) {
      first = *(--node);
      last = first + buffer_size();
      current = last;
    }
    --current;
    return *this;
  }
  iterator operator--(int) {
    iterator tmp = *this;
    --*this;
    return tmp;
  }
  iterator& operator+=(difference_type n) {
    difference_type offset = n + (current - first);
    difference_type num_node_to_jump = offset >= 0
      ? offset / buffer_size()
      : -((-offset + buffer_size() - 1) / buffer_size());
    if (num_node_to_jump == 0)
      current += n;
    else {
      node = node + num_node_to_jump;
      first = *node;
      last = first + buffer_size();
      current = first + (offset - num_node_to_jump * buffer_size());
    }
    return *this;
  }
  iterator& operator-=(difference_type n) { return *this += -n; }
  iterator operator+(difference_type n) const {
    iterator tmp = *this;
    return tmp += n;
  }
  iterator operator-(difference_type n) const {
    iterator tmp = *this;
    return tmp -= n;
  }
  reference operator[](difference_type n) const { return *(*this + n); }
  bool operator==(const iterator& x) const {      
    return current == x.current || 
      ((current == first || x.current == x.first) && 
       *this - x == 0);
  }
  bool operator!=(const iterator& x) const { return !(*this == x); }
  bool operator<(const iterator& x) const {
    return (node == x.node) ? (current < x.current) : (node < x.node);
  }
};


template <class T>
struct __deque_const_iterator {
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef pointer* map_pointer;
  typedef __deque_iterator<T> iterator;
  typedef __deque_const_iterator<T> const_iterator;

  pointer current;
  pointer first;
  pointer last;
  map_pointer node;

  static size_type buffer_size() {
    return __deque_buf_size(sizeof(value_type)); }

  __deque_const_iterator(pointer x, map_pointer y) 
    : current(x), first(*y), last(*y + buffer_size()), node(y) {}


  __deque_const_iterator() : current(0), first(0), last(0), node(0) {}
  __deque_const_iterator(const iterator& x) 
    : current(x.current), first(x.first), last(x.last), node(x.node) {}     
  const_reference operator*() const { return *current; }
  difference_type operator-(const const_iterator& x) const {
    return node == x.node 
      ? current - x.current 
      : difference_type(buffer_size() * (node - x.node - 1) +
                        (current - first) + (x.last - x.current));
  }
  const_iterator& operator++() {
    if (++current == last) {
      first = *(++node);
      current = first;
      last = first + buffer_size();
    }
    return *this; 
  }
  const_iterator operator++(int)  {
    const_iterator tmp = *this;
    ++*this;
    return tmp;
  }
  const_iterator& operator--() {
    if (current == first) {
      first = *(--node);
      last = first + buffer_size();
      current = last;
    }
    --current;
    return *this;
  }
  const_iterator operator--(int) {
    const_iterator tmp = *this;
    --*this;
    return tmp;
  }
  const_iterator& operator+=(difference_type n) {
    difference_type offset = n + (current - first);
    difference_type num_node_to_jump = offset >= 0
      ? offset / buffer_size()
      : -((-offset + buffer_size() - 1) / buffer_size());
    if (num_node_to_jump == 0)
      current += n;
    else {
      node = node + num_node_to_jump;
      first = *node;
      last = first + buffer_size();
      current = first + (offset - num_node_to_jump * buffer_size());
    }
    return *this;
  }
  const_iterator& operator-=(difference_type n) { return *this += -n; }
  const_iterator operator+(difference_type n) const {
    const_iterator tmp = *this;
    return tmp += n;
  }
  const_iterator operator-(difference_type n) const {
    const_iterator tmp = *this;
    return tmp -= n;
  }
  const_reference operator[](difference_type n) const { return *(*this + n); }
  bool operator==(const const_iterator& x) const {      
    return current == x.current || 
      ((current == first || x.current == x.first) && 
       *this - x == 0);
  }
  bool operator!=(const const_iterator& x) const {return !(*this == x); }
  bool operator<(const const_iterator& x) const {
    return (node == x.node) ? (current < x.current) : (node < x.node);
  }
};


template <class T>
inline random_access_iterator_tag
iterator_category(const __deque_iterator<T>&) {
  return random_access_iterator_tag();
}

template <class T>
inline __deque_iterator<T>::value_type*
value_type(const __deque_iterator<T>&) {
  return (__deque_iterator<T>::value_type*) 0;
}

template <class T>
inline __deque_iterator<T>::difference_type*
distance_type(const __deque_iterator<T>&) {
  return (__deque_iterator<T>::difference_type*) 0;
}

template <class T>
inline random_access_iterator_tag
iterator_category(const __deque_const_iterator<T>&) {
  return random_access_iterator_tag();
}

template <class T>
inline __deque_const_iterator<T>::value_type*
value_type(const __deque_const_iterator<T>&) {
  return (__deque_const_iterator<T>::value_type*) 0;
}

template <class T>
inline __deque_const_iterator<T>::difference_type*
distance_type(const __deque_const_iterator<T>&) {
  return (__deque_const_iterator<T>::difference_type*) 0;
}


template <class T, class Alloc = alloc> 
class deque {
public:
    friend struct __deque_iterator<T>;
    friend struct __deque_const_iterator<T>;
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    static size_type buffer_size() {
      return __deque_buf_size(sizeof(value_type)); }
    static size_type init_map_size() {
      return __deque_buf_size(sizeof(pointer)); }
    typedef pointer* map_pointer;
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;
public:
    typedef __deque_iterator<T> iterator;
    typedef __deque_const_iterator<T> const_iterator;
    typedef reverse_iterator<const_iterator, value_type, const_reference, 
                             difference_type>  const_reverse_iterator;
    typedef reverse_iterator<iterator, value_type, reference, difference_type>
        reverse_iterator; 
protected:    
    iterator start;
    iterator finish;
    size_type length;
    map_pointer map;
    size_type map_size;

    void allocate_at_begin();
    void allocate_at_end();
    void deallocate_at_begin();
    void deallocate_at_end();

public:
    deque() : start(), finish(), length(0), map(0), map_size(0) { }
    iterator begin() { return start; }
    const_iterator begin() const { return start; }
    iterator end() { return finish; }
    const_iterator end() const { return finish; }
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
    reference operator[](size_type n) { return *(begin() + n); }
    const_reference operator[](size_type n) const { return *(begin() + n); }
    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }
    void push_front(const T& x) {
	if (empty() || begin().current == begin().first)
	    allocate_at_begin();
	--start.current;
	construct(start.current, x);
	++length;
	if (end().current == end().last) allocate_at_end();
    }
    void push_back(const T& x) {
	if (empty()) allocate_at_end();
	construct(finish.current, x);
	++finish.current;
	++length;
	if (end().current == end().last) allocate_at_end();
    }
    void pop_front() {
	destroy(start.current);
	++start.current;
	--length; 
	if (empty() || begin().current == begin().last)
	    deallocate_at_begin();
    }
    void pop_back() {
	if (end().current == end().first) deallocate_at_end();
	--finish.current;
	destroy(finish.current);
	--length; 
	if (empty()) deallocate_at_end();
    }
    void swap(deque<T, Alloc>& x) {
	::swap(start, x.start);
	::swap(finish, x.finish);
	::swap(length, x.length);
	::swap(map, x.map);
	::swap(map_size, x.map_size);
    }
    iterator insert(iterator position, const T& x);
    iterator insert(iterator position) { return insert(position, T()); }
    void insert(iterator position, size_type n, const T& x);
//  template <class Iterator> void insert(iterator position,
//                                        Iterator first, Iterator last);
    void insert(iterator position, const T* first, const T* last);
    void insert(iterator position, const_iterator first, const_iterator last);
    void erase(iterator position);
    void erase(iterator first, iterator last);    
    void resize(size_type new_size, const T& x) {
      if (new_size < size()) 
        erase(begin() + new_size, end());
      else
        insert(end(), new_size - size(), x);
    }
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() { while (!empty()) pop_front(); }
public:
    deque(size_type n, const T& value)
	: start(), finish(), length(0), map(0), map_size(0) {
	insert(begin(), n, value);
    }
    deque(size_type n)
	: start(), finish(), length(0), map(0), map_size(0) {
	insert(begin(), n, T());
    }
//  template <class Iterator> deque(Iterator first, Iterator last);
    deque(const T* first, const T* last)
	: start(), finish(), length(0), map(0), map_size(0) {
	copy(first, last, back_inserter(*this));
    }
    deque(const_iterator first, const_iterator last)
	: start(), finish(), length(0), map(0), map_size(0) {
	copy(first, last, back_inserter(*this));
    }
    deque(const deque<T, Alloc>& x)
	: start(), finish(), length(0), map(0), map_size(0) {
	copy(x.begin(), x.end(), back_inserter(*this));
    }
    deque<T, Alloc>& operator=(const deque<T, Alloc>& x) {
	if (this != &x)
	    if (size() >= x.size()) 
		erase(copy(x.begin(), x.end(), begin()), end());
	    else 
		copy(x.begin() + size(), x.end(),
		     inserter(*this, copy(x.begin(), x.begin() + size(),
					  begin())));
	return *this;
    }
    ~deque() { clear(); }
};

template <class T, class Alloc>
bool operator==(const deque<T, Alloc>& x, const deque<T, Alloc>& y) {
    return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc>
bool operator<(const deque<T, Alloc>& x, const deque<T, Alloc>& y) {
    return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T, class Alloc>
void deque<T, Alloc>::allocate_at_begin() {
    pointer p = data_allocator::allocate(buffer_size());
    if (!empty()) {
	if (start.node == map) {
	    difference_type i = finish.node - start.node;
            size_type old_map_size = map_size;
	    map_size = (i + 1) * 2;
	    map_pointer tmp = map_allocator::allocate(map_size);
	    copy(start.node, finish.node + 1, tmp + map_size / 4 + 1);
	    map_allocator::deallocate(map, old_map_size);
	    map = tmp;
	    map[map_size / 4] = p;
	    start = iterator(p + buffer_size(), map + map_size / 4);
	    finish = iterator(finish.current, map + map_size / 4 + i + 1);
	} else {
	    *--start.node = p;
	    start = iterator(p + buffer_size(), start.node);
	}
    } else {
	map_size = init_map_size();
	map = map_allocator::allocate(map_size);
	map[map_size / 2] = p;
	start = iterator(p + buffer_size() / 2 + 1, map + map_size / 2);
	finish = start;
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::allocate_at_end() {
    pointer p = data_allocator::allocate(buffer_size());
    if (!empty()) {
	if (finish.node == map + map_size - 1) {
	    difference_type i = finish.node - start.node;
            size_type old_map_size = map_size;
	    map_size = (i + 1) * 2;
	    map_pointer tmp = map_allocator::allocate(map_size);
	    copy(start.node, finish.node + 1, tmp + map_size / 4);
	    map_allocator::deallocate(map, old_map_size);
	    map = tmp;
	    map[map_size / 4 + i + 1] = p;
	    start = iterator(start.current, map + map_size / 4);
	    finish = iterator(p, map + map_size / 4 + i + 1);
	} else {
	    *++finish.node = p;
	    finish = iterator(p, finish.node);
	}
    } else {
        map_size = init_map_size();
	map = map_allocator::allocate(map_size);
	map[map_size / 2] = p;
	start = iterator(p + buffer_size() / 2, map + map_size / 2);
	finish = start;
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::deallocate_at_begin() {
    data_allocator::deallocate(*start.node++, buffer_size());
    if (empty()) {
	if (finish.current == finish.first) 
	    data_allocator::deallocate(*start.node, buffer_size());
	start = iterator();
	finish = start;
	map_allocator::deallocate(map, map_size);
    } else
	start = iterator(*start.node, start.node);
}

template <class T, class Alloc>
void deque<T, Alloc>::deallocate_at_end() {
    data_allocator::deallocate(*finish.node--, buffer_size());
    if (empty()) {
	start = iterator();
	finish = start;
	map_allocator::deallocate(map, map_size);
    } else
	finish = iterator(*finish.node + buffer_size(), finish.node);
}

template <class T, class Alloc>
deque<T, Alloc>::iterator deque<T, Alloc>::insert(iterator position, const T& x) {
    if (position == begin()) {
	push_front(x);
	return begin();
    } else if (position == end()) {
	push_back(x);
	return end() - 1;
    } else {
	difference_type index = position - begin();
	if (index < length / 2) {
	    push_front(*begin());
	    copy(begin() + 2, begin() + index + 1, begin() + 1); 
	} else {
	    push_back(*(end() - 1));
	    copy_backward(begin() + index, end() - 2, end() - 1); 
        }
	*(begin() + index) = x;
	return begin() + index;
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::insert(iterator position, size_type n, const T& x) {
    difference_type index = position - begin();
    difference_type remainder = length - index;
    if (remainder > index) {
	if (n > index) {
	    difference_type m = n - index;
	    while (m-- > 0) push_front(x);
	    difference_type i = index;
	    while (i--) push_front(*(begin() + n - 1));
	    fill(begin() + n, begin() + n + index, x);
	} else {
	    difference_type i = n;
	    while (i--) push_front(*(begin() + n - 1));
	    copy(begin() + n + n, begin() + n + index, begin() + n);
	    fill(begin() + index, begin() + n + index, x);
	}
    } else {
	difference_type orig_len = index + remainder;
	if (n > remainder) {
	    difference_type m = n - remainder;
	    while (m-- > 0) push_back(x);
	    difference_type i = 0;
	    while (i < remainder) push_back(*(begin() + index + i++));
	    fill(begin() + index, begin() + orig_len, x);
	} else {
	    difference_type i = 0;
	    while (i < n) push_back(*(begin() + orig_len - n + i++));
	    copy_backward(begin() + index, begin() + orig_len - n, 
			  begin() + orig_len);
	    fill(begin() + index, begin() + index + n, x);
	}
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::insert(iterator position, const T* first, const T* last) {
    difference_type index = position - begin();
    difference_type remainder = length - index;
    size_type n = 0;
    distance(first, last, n);
    if (remainder > index) {
	if (n > index) {
	    const T* m = last - index;
	    while (m != first) push_front(*--m);
	    difference_type i = index;
	    while (i--) push_front(*(begin() + n - 1));
	    copy(last - index, last, begin() + n);
	} else {
	    difference_type i = n;
	    while (i--) push_front(*(begin() + n - 1));
	    copy(begin() + n + n, begin() + n + index, begin() + n);
	    copy(first, last, begin() + index);
	}
    } else {
	difference_type orig_len = index + remainder;
	if (n > remainder) {
	    const T* m = first + remainder;
	    while (m != last) push_back(*m++);
	    difference_type i = 0;
	    while (i < remainder) push_back(*(begin() + index + i++));
	    copy(first, first + remainder, begin() + index);
	} else {
	    difference_type i = 0;
	    while (i < n) push_back(*(begin() + orig_len - n + i++));
	    copy_backward(begin() + index, begin() + orig_len - n, 
			  begin() + orig_len);
	    copy(first, last, begin() + index);
	}
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::insert(iterator position, const_iterator first, const_iterator last) {
    difference_type index = position - begin();
    difference_type remainder = length - index;
    size_type n = 0;
    distance(first, last, n);
    if (remainder > index) {
	if (n > index) {
	    const_iterator m = last - index;
	    while (m != first) push_front(*--m);
	    difference_type i = index;
	    while (i--) push_front(*(begin() + n - 1));
	    copy(last - index, last, begin() + n);
	} else {
	    difference_type i = n;
	    while (i--) push_front(*(begin() + n - 1));
	    copy(begin() + n + n, begin() + n + index, begin() + n);
	    copy(first, last, begin() + index);
	}
    } else {
	difference_type orig_len = index + remainder;
	if (n > remainder) {
	    const_iterator m = first + remainder;
	    while (m != last) push_back(*m++);
	    difference_type i = 0;
	    while (i < remainder) push_back(*(begin() + index + i++));
	    copy(first, first + remainder, begin() + index);
	} else {
	    difference_type i = 0;
	    while (i < n) push_back(*(begin() + orig_len - n + i++));
	    copy_backward(begin() + index, begin() + orig_len - n, 
			  begin() + orig_len);
	    copy(first, last, begin() + index);
	}
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::erase(iterator position) {
    if (end() - position > position - begin()) {
	copy_backward(begin(), position, position + 1);
	pop_front();
    } else {
	copy(position + 1, end(), position);
	pop_back();
    }
}
    
template <class T, class Alloc>
void deque<T, Alloc>::erase(iterator first, iterator last) {
	 difference_type n = last - first;
    if (end() - last > first - begin()) {
	copy_backward(begin(), first, last);
	while(n-- > 0) pop_front();
    } else   {
	copy(last, end(), first);
	while(n-- > 0) pop_back();
    }
}



#endif /* __SGI_STL_DEQUE_H */

