// Copyright 2007 Google Inc. All Rights Reserved.
// Author: jmacd@google.com (Josh MacDonald)
// Author: pmattis@google.com (Peter Mattis)

#include "base/arena-inl.h"
#include "base/init_google.h"
#include "base/integral_types.h"
#include "base/logging.h"
#include "strings/stringpiece.h"
#include "testing/base/public/gunit.h"
#include "util/btree/btree_map.h"
#include "util/btree/btree_set.h"
#include "util/btree/btree_test.h"

namespace util {
namespace btree {
namespace {

template <typename K, int N>
void SetTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  CHECK_EQ(sizeof(btree_set<K>), sizeof(void*));
  BtreeTest<btree_set<K, less<K>, allocator<K>, N>, set<K> >();
  BtreeArenaTest<btree_set<K, less<K>, ArenaAlloc, N> >();
}

template <typename K, int N>
void MapTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  CHECK_EQ(sizeof(btree_map<K, K>), sizeof(void*));
  BtreeTest<btree_map<K, K, less<K>, allocator<K>, N>, map<K, K> >();
  BtreeArenaTest<btree_map<K, K, less<K>, ArenaAlloc, N> >();
  BtreeMapTest<btree_map<K, K, less<K>, allocator<K>, N> >();
}

TEST(Btree, set_int32_32)   { SetTest<int32, 32>(); }
TEST(Btree, set_int32_64)   { SetTest<int32, 64>(); }
TEST(Btree, set_int32_128)  { SetTest<int32, 128>(); }
TEST(Btree, set_int32_256)  { SetTest<int32, 256>(); }
TEST(Btree, set_int64_256)  { SetTest<int64, 256>(); }
TEST(Btree, set_string_256) { SetTest<string, 256>(); }
TEST(Btree, set_cord_256)   { SetTest<Cord, 256>(); }
TEST(Btree, set_pair_256)   { SetTest<pair<int, int>, 256>(); }
TEST(Btree, map_int32_256)  { MapTest<int32, 256>(); }
TEST(Btree, map_int64_256)  { MapTest<int64, 256>(); }
TEST(Btree, map_string_256) { MapTest<string, 256>(); }
TEST(Btree, map_cord_256)   { MapTest<Cord, 256>(); }
TEST(Btree, map_pair_256)   { MapTest<pair<int, int>, 256>(); }

template <typename K, int N>
void MultiSetTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  CHECK_EQ(sizeof(btree_multiset<K>), sizeof(void*));
  BtreeMultiTest<btree_multiset<K, less<K>, allocator<K>, N>,
      multiset<K> >();
  BtreeArenaTest<btree_multiset<K, less<K>, ArenaAlloc, N> >();
}

template <typename K, int N>
void MultiMapTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  CHECK_EQ(sizeof(btree_multimap<K, K>), sizeof(void*));
  BtreeMultiTest<btree_multimap<K, K, less<K>, allocator<K>, N>,
      multimap<K, K> >();
  BtreeMultiMapTest<btree_multimap<K, K, less<K>, allocator<K>, N> >();
  BtreeArenaTest<btree_multimap<K, K, less<K>, ArenaAlloc, N> >();
}

TEST(Btree, multiset_int32_256)  { MultiSetTest<int32, 256>(); }
TEST(Btree, multiset_int64_256)  { MultiSetTest<int64, 256>(); }
TEST(Btree, multiset_string_256) { MultiSetTest<string, 256>(); }
TEST(Btree, multiset_cord_256)   { MultiSetTest<Cord, 256>(); }
TEST(Btree, multiset_pair_256)   { MultiSetTest<pair<int, int>, 256>(); }
TEST(Btree, multimap_int32_256)  { MultiMapTest<int32, 256>(); }
TEST(Btree, multimap_int64_256)  { MultiMapTest<int64, 256>(); }
TEST(Btree, multimap_string_256) { MultiMapTest<string, 256>(); }
TEST(Btree, multimap_cord_256)   { MultiMapTest<Cord, 256>(); }
TEST(Btree, multimap_pair_256)   { MultiMapTest<pair<int, int>, 256>(); }

// Verify that swapping btrees swaps the key comparision functors.
struct SubstringLess {
  SubstringLess() : n(2) {}
  SubstringLess(int length)
      : n(length) {
  }
  bool operator()(const string &a, const string &b) const {
    return StringPiece(a).substr(0, n) < StringPiece(b).substr(0, n);
  }
  int n;
};

TEST(Btree, SwapKeyCompare) {
  typedef btree_set<string, SubstringLess> SubstringSet;
  SubstringSet s1(SubstringLess(1), SubstringSet::allocator_type());
  SubstringSet s2(SubstringLess(2), SubstringSet::allocator_type());

  ASSERT_TRUE(s1.insert("a").second);
  ASSERT_FALSE(s1.insert("aa").second);

  ASSERT_TRUE(s2.insert("a").second);
  ASSERT_TRUE(s2.insert("aa").second);
  ASSERT_FALSE(s2.insert("aaa").second);

  swap(s1, s2);

  ASSERT_TRUE(s1.insert("b").second);
  ASSERT_TRUE(s1.insert("bb").second);
  ASSERT_FALSE(s1.insert("bbb").second);

  ASSERT_TRUE(s2.insert("b").second);
  ASSERT_FALSE(s2.insert("bb").second);
}

TEST(Btree, UpperBoundRegression) {
  // Regress a bug where upper_bound would default-construct a new key_compare
  // instead of copying the existing one.
  typedef btree_set<string, SubstringLess> SubstringSet;
  SubstringSet my_set(SubstringLess(3));
  my_set.insert("aab");
  my_set.insert("abb");
  // We call upper_bound("aaa").  If this correctly uses the length 3
  // comparator, aaa < aab < abb, so we should get aab as the result.
  // If it instead uses the default-constructed length 2 comparator,
  // aa == aa < ab, so we'll get abb as our result.
  SubstringSet::iterator it = my_set.upper_bound("aaa");
  ASSERT_TRUE(it != my_set.end());
  EXPECT_EQ("aab", *it);
}


TEST(Btree, IteratorIncrementBy) {
  // Test that increment_by returns the same position as increment.
  const int kSetSize = 2341;
  btree_set<int32> my_set;
  for (int i = 0; i < kSetSize; ++i) {
    my_set.insert(i);
  }

  {
    // Simple increment vs. increment by.
    btree_set<int32>::iterator a = my_set.begin();
    btree_set<int32>::iterator b = my_set.begin();
    a.increment();
    b.increment_by(1);
    EXPECT_EQ(*a, *b);
  }

  btree_set<int32>::iterator a = my_set.begin();
  for (int i = 1; i < kSetSize; ++i) {
    ++a;
    // increment_by
    btree_set<int32>::iterator b = my_set.begin();
    b.increment_by(i);
    EXPECT_EQ(*a, *b) << ": i=" << i;
  }
}


} // namespace
} // namespace btree
} // namespace util

int main(int argc, char **argv) {
  FLAGS_logtostderr = true;
  InitGoogle(argv[0], &argc, &argv, true);
  return RUN_ALL_TESTS();
}
