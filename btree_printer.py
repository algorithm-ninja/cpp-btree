#!/usr/bin/python2.4
# Copyright 2011 Google Inc. All Rights Reserved.
# GDB support for pretty printing StringPiece.

"""GDB pretty-printer for btrees."""

# This is a module provided by GDB.
# Ref: http://wiki/Main/Google3GDBScripts
import gdb
from google3.devtools.gdb.component import printing


class BaseBtreePrinter(object):
  """btree pretty-printer, for util/btree."""

  def __init__(self, typename, val):
    self.typename = typename
    self.val = val

  def display_hint(self):
    return 'array'

  def _my_iter(self, node):
    count = node['fields_']['count']
    if node['fields_']['leaf']:
      for i in range(count):
        key = node['fields_']['values'][i]
        yield ('[item]', key)
    else:
      # recursive generators are annoying: we can't just recurse, we need
      # to expand and yield the values.
      for i in range(count+1):
        child = node['fields_']['children'][i]
        for v in self._my_iter(child.dereference()):
          yield v

  def children(self):
    if self.nelements() != 0:
      return self._my_iter(self.val['root_']['data'].dereference())
    else:
      return iter([])

  def nelements(self):
    if self.val['root_']['data'] != 0:
      root_fields = self.val['root_']['data'].dereference()['fields_']
      if root_fields['leaf']:
        return root_fields['count']
      else:
        return root_fields['size']
    else:
      return 0

  def to_string(self):  # pylint: disable-msg=C6409
    """GDB calls this to compute the pretty-printed form."""
    return '%s with %d elements' % (self.typename, self.nelements())


class BtreePrinter(BaseBtreePrinter):
  """btree<> pretty-printer, for util/btree."""

  def __init__(self, val):
    BaseBtreePrinter.__init__(self, 'btree', val)


class BtreeSetPrinter(BaseBtreePrinter):
  """btree_set<> pretty-printer."""

  def __init__(self, val):
    BaseBtreePrinter.__init__(self, 'btree_set', val['tree_'])


class BtreeMultisetPrinter(BaseBtreePrinter):
  """btree_multiset<> pretty-printer."""

  def __init__(self, val):
    BaseBtreePrinter.__init__(self, 'btree_multiset', val['tree_'])


class BaseBtreeMapPrinter(BaseBtreePrinter):
  """btree maps pretty-printer."""

  def __init__(self, typename, val):
    BaseBtreePrinter.__init__(self, typename, val['tree_'])

  def display_hint(self):
    return 'map'

  def _my_map_iter(self, g):
    for (_, pair) in g:
      yield ('[key]', pair['first'])
      yield ('[value]', pair['second'])

  def children(self):
    # we need to break apart the pairs and yield them separately
    if self.nelements() != 0:
      return self._my_map_iter(BaseBtreePrinter.children(self))
    else:
      return iter([])


class BtreeMapPrinter(BaseBtreeMapPrinter):
  """btree_map<> pretty-printer."""

  def __init__(self, val):
    BaseBtreeMapPrinter.__init__(self, 'btree_map', val)


class BtreeMultimapPrinter(BaseBtreeMapPrinter):
  """btree_multimap<> pretty-printer."""

  def __init__(self, val):
    BaseBtreeMapPrinter.__init__(self, 'btree_multimap', val)


if __name__ == '__main__':
  printing.RegisterGoogle3ClassPrettyPrinter('util::btree::btree<.*>',
                                             BtreePrinter)
  printing.RegisterGoogle3ClassPrettyPrinter('util::btree::btree_set<.*>',
                                             BtreeSetPrinter)
  printing.RegisterGoogle3ClassPrettyPrinter('util::btree::btree_multiset<.*>',
                                             BtreeMultisetPrinter)
  printing.RegisterGoogle3ClassPrettyPrinter('util::btree::btree_map<.*>',
                                             BtreeMapPrinter)
  printing.RegisterGoogle3ClassPrettyPrinter('util::btree::btree_multimap<.*>',
                                             BtreeMultimapPrinter)
