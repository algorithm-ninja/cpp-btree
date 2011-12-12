# -*- mode: python; -*-

# This should be a Makefile, but it's not.

# cc_library(name = "btree",
#            srcs = [ "btree.h",
#                     "btree_container.h",
#                     "btree_map.h",
#                     "btree_set.h",
#                     "safe_btree.h",
#                     "safe_btree_map.h",
#                     "safe_btree_set.h" ],
#            deps = [ "//strings",
#                     "//strings:cord" ])

# cc_library(name = "btree_test_flags",
#            srcs = [ "btree_test_flags.cc" ],
#            deps = [ "//base" ])

# cc_binary(name = "btree_bench",
#           srcs = [ "btree_bench.cc" ],
#           deps = [ ":btree",
#                    ":btree_test_flags",
#                    "//testing/base",
#                    "//util/random" ])

# cc_test(name = "btree_test",
#         srcs = [ "btree_test.cc", ],
#         deps = [ ":btree",
#                  ":btree_test_flags",
#                  "//base:heapcheck",
#                  "//testing/base",
#                  "//util/random",
#                  ],
#         size = "large")

# cc_test(name = "safe_btree_test",
#         srcs = [ "safe_btree_test.cc", ],
#         deps = [ ":btree",
#                  ":btree_test_flags",
#                  "//base:heapcheck",
#                  "//testing/base",
#                  "//util/random",
#                  ],
#         size = "large")

# cc_fake_binary(name = "btree_nc",
#                srcs = [ "btree_nc.cc" ],
#                deps = [ ":btree" ],
#                legacy = 0)

# py_test(name = "btree_nc_test",
#         srcs = [ "btree_nc_test.py" ],
#         deps = [ "//pyglib",
#                  "//testing/pybase" ],
#         data = [ "btree_nc" ],
#         size = "large")

# cc_binary(name = "btree_test_program",
#           srcs = [ "btree_test_program.cc" ],
#           deps = [ ":btree",
#                    "//devtools/gdb/component:gdb_test_utils" ],
#           testonly = 1)

# # This test will only actually test the pretty-printing code if it's
# # compiled with debug information (blaze build -c dbg). The default
# # mode, fastbuild, will pass but will not catch any regressions!
# py_test(name = "btree_printer_test",
#         size = "large",
#         srcs = [ "btree_printer_test.py",
#                  "btree_printer.py" ],
#         deps = [ "//devtools/gdb/component:gdbpy",
#                  "//testing/pybase",
#                  "//testing/gdb:gdb_script_test_util",
#                  ":btree_test_program" ])
