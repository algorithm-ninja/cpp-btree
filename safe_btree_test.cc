// Copyright 2007 Google Inc. All Rights Reserved.
// Author: jmacd@google.com (Josh MacDonald)
// Author: pmattis@google.com (Peter Mattis)

// TODO(pmattis): Add some tests that iterators are not invalidated by
// insertion and deletion.

#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "base/arena-inl.h"
#include "base/init_google.h"
#include "base/integral_types.h"
#include "base/logging.h"
#include "strings/cord.h"
#include "testing/base/public/gunit.h"
#include "util/btree/btree_test.h"
#include "util/btree/safe_btree_map.h"
#include "util/btree/safe_btree_set.h"

class UnsafeArena;

namespace util {
namespace btree {
namespace {

template <typename K, int N>
void SetTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  BtreeTest<safe_btree_set<K, less<K>, allocator<K>, N>, set<K> >();
  BtreeArenaTest<safe_btree_set<K, less<K>, ArenaAlloc, N> >();
}

template <typename K, int N>
void MapTest() {
  typedef ArenaAllocator<K, UnsafeArena> ArenaAlloc;
  BtreeTest<safe_btree_map<K, K, less<K>, allocator<K>, N>, map<K, K> >();
  BtreeArenaTest<safe_btree_map<K, K, less<K>, ArenaAlloc, N> >();
  BtreeMapTest<safe_btree_map<K, K, less<K>, allocator<K>, N> >();
}

TEST(SafeBtree, set_int32_32)   { SetTest<int32, 32>(); }
TEST(SafeBtree, set_int32_64)   { SetTest<int32, 64>(); }
TEST(SafeBtree, set_int32_128)  { SetTest<int32, 128>(); }
TEST(SafeBtree, set_int32_256)  { SetTest<int32, 256>(); }
TEST(SafeBtree, set_int64_256)  { SetTest<int64, 256>(); }
TEST(SafeBtree, set_string_256) { SetTest<string, 256>(); }
TEST(SafeBtree, set_cord_256)   { SetTest<Cord, 256>(); }
TEST(SafeBtree, set_pair_256)   { SetTest<pair<int, int>, 256>(); }
TEST(SafeBtree, map_int32_256)  { MapTest<int32, 256>(); }
TEST(SafeBtree, map_int64_256)  { MapTest<int64, 256>(); }
TEST(SafeBtree, map_string_256) { MapTest<string, 256>(); }
TEST(SafeBtree, map_cord_256)   { MapTest<Cord, 256>(); }
TEST(SafeBtree, map_pair_256)   { MapTest<pair<int, int>, 256>(); }

} // namespace
} // namespace btree
} // namespace util

int main(int argc, char **argv) {
  FLAGS_logtostderr = true;
  InitGoogle(argv[0], &argc, &argv, true);
  return RUN_ALL_TESTS();
}
