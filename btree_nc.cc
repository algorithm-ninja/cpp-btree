// Copyright 2009 Google Inc. All Rights Reserved.
// Author: jmacd@google.com (Josh MacDonald)

#include "util/btree/btree_set.h"

namespace {

template <typename R>
struct Compare {
  R operator()(int a, int b) const { return reinterpret_cast<R>(a < b); }
};

template <typename R>
struct CompareTo : public util::btree::btree_key_compare_to_tag {
  R operator()(int a, int b) const { return reinterpret_cast<R>(a < b); }
};

#define TEST_COMPARE(r)                          \
  void TestCompile() {                           \
    util::btree::btree_set<int, Compare<r> > s;  \
  }

#define TEST_COMPARE_TO(r)                         \
  void TestCompile() {                             \
    util::btree::btree_set<int, CompareTo<r> > s;  \
  }

#if defined(TEST_bool)
TEST_COMPARE(bool);
#elif defined(TEST_int)
TEST_COMPARE(int);
#elif defined(TEST_float)
TEST_COMPARE(float);
#elif defined(TEST_pointer)
TEST_COMPARE(void*);
#elif defined(TEST_compare_to_bool)
TEST_COMPARE_TO(bool);
#elif defined(TEST_compare_to_int)
TEST_COMPARE_TO(int);
#elif defined(TEST_compare_to_float)
TEST_COMPARE_TO(float);
#elif defined(TEST_compare_to_pointer)
TEST_COMPARE_TO(pointer);
#endif

}  // namespace

int main() {
  return 1;
}
