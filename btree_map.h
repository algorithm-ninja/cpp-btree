// Copyright 2007 Google Inc. All Rights Reserved.
// Author: jmacd@google.com (Josh MacDonald)
// Author: pmattis@google.com (Peter Mattis)
//
// A btree_map<> implements the STL unique sorted associative container
// interface and the pair associative container interface (a.k.a map<>) using a
// btree. A btree_multimap<> implements the STL multiple sorted associative
// container interface and the pair associtive container interface (a.k.a
// multimap<>) using a btree. See btree.h for details of the btree
// implementation and caveats.

#ifndef UTIL_BTREE_BTREE_MAP_H__
#define UTIL_BTREE_BTREE_MAP_H__

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "util/btree/btree.h"  // IWYU pragma: export
#include "util/btree/btree_container.h"  // IWYU pragma: export

namespace util {
namespace btree {

// The btree_map class is needed mainly for it's constructors.
template <typename Key, typename Value,
          typename Compare = less<Key>,
          typename Alloc = std::allocator<pair<const Key, Value> >,
          int TargetNodeSize = 256>
class btree_map : public btree_map_container<
  btree<btree_map_params<Key, Value, Compare, Alloc, TargetNodeSize> > > {

  typedef btree_map<Key, Value, Compare, Alloc, TargetNodeSize> self_type;
  typedef btree_map_params<
    Key, Value, Compare, Alloc, TargetNodeSize> params_type;
  typedef btree<params_type> btree_type;
  typedef btree_map_container<btree_type> super_type;

 public:
  typedef typename btree_type::key_compare key_compare;
  typedef typename btree_type::allocator_type allocator_type;

 public:
  // Default constructor.
  btree_map(const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
      : super_type(comp, alloc) {
  }

  // Copy constructor.
  btree_map(const self_type &x)
      : super_type(x) {
  }

  // Range constructor.
  template <class InputIterator>
  btree_map(InputIterator b, InputIterator e,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
      : super_type(comp, alloc) {
  }
};

template <typename K, typename V, typename C, typename A, int N>
inline void swap(btree_map<K, V, C, A, N> &x,
                 btree_map<K, V, C, A, N> &y) {
  x.swap(y);
}

// The btree_multimap class is needed mainly for it's constructors.
template <typename Key, typename Value,
          typename Compare = less<Key>,
          typename Alloc = std::allocator<pair<const Key, Value> >,
          int TargetNodeSize = 256>
class btree_multimap : public btree_multi_container<
  btree<btree_map_params<Key, Value, Compare, Alloc, TargetNodeSize> > > {

  typedef btree_multimap<Key, Value, Compare, Alloc, TargetNodeSize> self_type;
  typedef btree_map_params<
    Key, Value, Compare, Alloc, TargetNodeSize> params_type;
  typedef btree<params_type> btree_type;
  typedef btree_multi_container<btree_type> super_type;

 public:
  typedef typename btree_type::key_compare key_compare;
  typedef typename btree_type::allocator_type allocator_type;
  typedef typename btree_type::data_type data_type;
  typedef typename btree_type::mapped_type mapped_type;

 public:
  // Default constructor.
  btree_multimap(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
      : super_type(comp, alloc) {
  }

  // Copy constructor.
  btree_multimap(const self_type &x)
      : super_type(x) {
  }

  // Range constructor.
  template <class InputIterator>
  btree_multimap(InputIterator b, InputIterator e,
                 const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
      : super_type(b, e, comp, alloc) {
  }
};

template <typename K, typename V, typename C, typename A, int N>
inline void swap(btree_multimap<K, V, C, A, N> &x,
                 btree_multimap<K, V, C, A, N> &y) {
  x.swap(y);
}

} // namespace btree
} // namespace util

#endif  // UTIL_BTREE_BTREE_MAP_H__
