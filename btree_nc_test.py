#!/usr/bin/python2.4
#
# Copyright 2006 Google Inc. All Rights Reserved.

"""Negative compilation unit test for btree.h.
"""

__author__ = 'pmattis@google.com (Peter Mattis)'

import os
from google3.testing.pybase import googletest
from google3.testing.pybase import fake_target_util
from google3.pyglib import flags

_FLAGS = flags.FLAGS


class BtreeNegativeUnitTest(googletest.TestCase):
  """Negative compilation tests for btree.h"""

  def testCompilerErrors(self):
    """Runs a list of tests to verify that erroneous code leads to
    expected compiler messages."""

    # Defines a list of test specs, where each element is a tuple
    # (test name, list of regexes for matching the compiler errors).
    test_specs = [
        # Test that bool works as a return type for key comparison.
        ('bool', None),  # None means compilation should succeed.

        # Test that int does not work as a return type for key comparison.
        ('int',
         [r'key_comparison_function_must_return_bool']),

        # Test that float does not work as a return type for key comparison.
        ('float',
         [r'key_comparison_function_must_return_bool']),

        # Test that void* does not work as a return type for key comparison.
        ('pointer',
         [r'key_comparison_function_must_return_bool']),

        # Test that bool does not work as a return type for compare-to
        # comparison.
        ('compare_to_bool',
         [r'key_comparison_function_must_return_bool']),

        # Test that int works as a return type for compare-to comparison.
        ('compare_to_int', None),  # None means compilation should succeed.

        # Test that float does not work as a return type for compare-to
        # comparison.
        ('compare_to_float',
         [r'key_comparison_function_must_return_bool']),

        # Test that void* does not work as a return type for compare-to
        # comparison.
        ('compare_to_pointer',
         [r'key_comparison_function_must_return_bool']),

        # Test that large node sizes do not compile.
        ('large_nodesize',
         [r'target_node_size_too_large']),
      ]

    # Runs the list of tests.
    fake_target_util.AssertCcCompilerErrors(
      self,
      'google3/util/btree/btree_nc',  # path to the fake target file.
      'btree_nc.o',                   # name of the target to build.
      test_specs)


if __name__ == '__main__':
  googletest.main()
