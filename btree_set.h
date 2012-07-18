// Copyright 2007 Google Inc. All Rights Reserved.
// Author: jmacd@google.com (Josh MacDonald)
// Author: pmattis@google.com (Peter Mattis)
//
// A btree_set<> implements the STL unique sorted associative container
// interface (a.k.a set<>) using a btree. A btree_multiset<> implements the STL
// multiple sorted associative container interface (a.k.a multiset<>) using a
// btree. See btree.h for details of the btree implementation and caveats.

#ifndef UTIL_BTREE_BTREE_SET_H__
#define UTIL_BTREE_BTREE_SET_H__

#include <functional>
#include <memory>
#include <string>

#include "btree.h"
#include "btree_container.h"

namespace btree {

// The btree_set class is needed mainly for it's constructors.
template <typename Key,
          typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>,
          int TargetNodeSize = 256>
class btree_set : public btree_unique_container<
  btree<btree_set_params<Key, Compare, Alloc, TargetNodeSize> > > {

  typedef btree_set<Key, Compare, Alloc, TargetNodeSize> self_type;
  typedef btree_set_params<Key, Compare, Alloc, TargetNodeSize> params_type;
  typedef btree<params_type> btree_type;
  typedef btree_unique_container<btree_type> super_type;

 public:
  typedef typename btree_type::key_compare key_compare;
  typedef typename btree_type::allocator_type allocator_type;

 public:
  // Default constructor.
  btree_set(const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
      : super_type(comp, alloc) {
  }

  // Copy constructor.
  btree_set(const self_type &x)
      : super_type(x) {
  }

  // Range constructor.
  template <class InputIterator>
  btree_set(InputIterator b, InputIterator e,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
      : super_type(b, e, comp, alloc) {
  }
};

template <typename K, typename C, typename A, int N>
inline void swap(btree_set<K, C, A, N> &x, btree_set<K, C, A, N> &y) {
  x.swap(y);
}

// The btree_multiset class is needed mainly for it's constructors.
template <typename Key,
          typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>,
          int TargetNodeSize = 256>
class btree_multiset : public btree_multi_container<
  btree<btree_set_params<Key, Compare, Alloc, TargetNodeSize> > > {

  typedef btree_multiset<Key, Compare, Alloc, TargetNodeSize> self_type;
  typedef btree_set_params<Key, Compare, Alloc, TargetNodeSize> params_type;
  typedef btree<params_type> btree_type;
  typedef btree_multi_container<btree_type> super_type;

 public:
  typedef typename btree_type::key_compare key_compare;
  typedef typename btree_type::allocator_type allocator_type;

 public:
  // Default constructor.
  btree_multiset(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
      : super_type(comp, alloc) {
  }

  // Copy constructor.
  btree_multiset(const self_type &x)
      : super_type(x) {
  }

  // Range constructor.
  template <class InputIterator>
  btree_multiset(InputIterator b, InputIterator e,
                 const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
      : super_type(b, e, comp, alloc) {
  }
};

template <typename K, typename C, typename A, int N>
inline void swap(btree_multiset<K, C, A, N> &x,
                 btree_multiset<K, C, A, N> &y) {
  x.swap(y);
}

} // namespace btree

#endif  // UTIL_BTREE_BTREE_SET_H__
