// Copyright 2011 Google Inc. All Rights Reserved.
// Author: leg@google.com (Lawrence Greenfield)

#include "base/init_google.h"
#include "base/logging.h"
#include "devtools/gdb/component/gdb_test_utils.h"
#include "util/btree/btree_map.h"
#include "util/btree/btree_set.h"

using util::btree::btree_set;
using util::btree::btree_multiset;
using util::btree::btree_map;
using util::btree::btree_multimap;

static btree_set<int>* empty_set;
static btree_set<int>* small_set;
static btree_set<int>* big_set;
static btree_multiset<int>* small_multiset;

static btree_map<int, int>* empty_map;
static btree_map<int, int>* small_map;
static btree_map<int, int>* big_map;
static btree_multimap<int, int>* small_multimap;

static void SetupBtreeSets() {
  empty_set = new btree_set<int>;
  small_set = new btree_set<int>;
  small_multiset = new btree_multiset<int>;
  big_set = new btree_set<int>;

  for (int i = 0; i < 10; ++i) {
    small_set->insert(i);
    small_multiset->insert(i / 2);
  }

  for (int i = 0; i < 80; ++i) {
    big_set->insert(i);
  }
}

static void SetupBtreeMaps() {
  empty_map = new btree_map<int, int>;
  small_map = new btree_map<int, int>;
  small_multimap = new btree_multimap<int, int>;
  big_map = new btree_map<int, int>;

  for (int i = 0; i < 10; ++i) {
    small_map->insert(make_pair(i, i * 13));
    small_multimap->insert(make_pair(i / 2, i));
  }

  for (int i = 0; i < 80; ++i) {
    big_map->insert(make_pair(i, i * 7));
  }
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = true;
  InitGoogle(argv[0], &argc, &argv, true);
  SetupBtreeSets();
  SetupBtreeMaps();
  StopHereForDebugger();
  return 0;
}
