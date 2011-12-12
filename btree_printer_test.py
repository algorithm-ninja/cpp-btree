#!/usr/bin/python2.4
#
# Copyright 2011 Google Inc. All Rights Reserved.

"""Tests for btree_printer.py gdb pretty printer."""

__author__ = "leg@google.com (Lawrence Greenfield)"

from google3.pyglib import flags
from google3.testing.gdb import gdb_script_test_util
from google3.testing.pybase import googletest

FLAGS = flags.FLAGS


class BtreePrinterTest(gdb_script_test_util.TestCase):
  def testBtreeSet(self):
    self.InitSession("btree_set",
                     "util/btree/btree_test_program")
    self.RunTo("StopHereForDebugger")

    self.SetOption("print elements", 20)
    self.TestPrintOutputMatches("*empty_set",
                                """btree_set with 0 elements""")
    self.TestPrintOutputMatches("*small_set",
                                """btree_set with 10 elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}""")
    self.TestPrintOutputMatches("*small_multiset",
                                """btree_multiset with 10 elements = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4}""")
    self.TestPrintOutputMatches("*big_set",
                                """btree_set with 80 elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19...}""")

    self.RunSession()

  def testBtreeMap(self):
    self.InitSession("btree_set",
                     "util/btree/btree_test_program")
    self.RunTo("StopHereForDebugger")

    self.SetOption("print elements", 30)
    self.TestPrintOutputMatches("*empty_map",
                                """btree_map with 0 elements""")
    self.TestPrintOutputMatches("*small_map",
                                """btree_map with 10 elements = {
  \\[0\\] = 0,
  \\[1\\] = 13,
  \\[2\\] = 26,
  \\[3\\] = 39,
  \\[4\\] = 52,
  \\[5\\] = 65,
  \\[6\\] = 78,
  \\[7\\] = 91,
  \\[8\\] = 104,
  \\[9\\] = 117
}""")
    self.TestPrintOutputMatches("*small_multimap",
                                """btree_multimap with 10 elements = {
  \\[0\\] = 0,
  \\[0\\] = 1,
  \\[1\\] = 2,
  \\[1\\] = 3,
  \\[2\\] = 4,
  \\[2\\] = 5,
  \\[3\\] = 6,
  \\[3\\] = 7,
  \\[4\\] = 8,
  \\[4\\] = 9
}""")
    self.TestPrintOutputMatches("*big_map",
                                """btree_map with 80 elements = {
  \\[0\\] = 0,
  \\[1\\] = 7,
  \\[2\\] = 14,
  \\[3\\] = 21,
  \\[4\\] = 28,
  \\[5\\] = 35,
  \\[6\\] = 42,
  \\[7\\] = 49,
  \\[8\\] = 56,
  \\[9\\] = 63,
  \\[10\\] = 70,
  \\[11\\] = 77,
  \\[12\\] = 84,
  \\[13\\] = 91,
  \\[14\\] = 98
  ...
}""")

    self.RunSession()


if __name__ == "__main__":
  googletest.main()
