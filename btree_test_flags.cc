// Copyright 2007 Google Inc. All Rights Reserved.
// Author: pmattis@google.com (Peter Mattis)

#include "gflags/gflags.h"

DEFINE_int32(test_values, 10000,
             "The number of values to use for tests.");
DEFINE_int32(benchmark_values, 1000000,
             "The number of values to use for benchmarks.");
