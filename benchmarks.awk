#!/usr/bin/gawk -f

/^Run on/ {
  print $0;
  printf "%-25s %5s %-20s\n",
      "Benchmark", "STL(ns)", "B-Tree(ns) @    <size>"
  printf "--------------------------------------------------------\n";
}

/^BM_/ {
  split($1, name, "_");
  if (name[2] == "stl") {
    stl = $3;
    stl_bytes = $5
    printf "%-25s %5d    ", name[1] "_" name[3] "_" name[4] "_" name[5], stl;
    fflush();
  } else if (name[2] == "btree") {
    btree = $3
    btree_size = name[3]
    btree_bytes = $5
    printf "%5d %+7.2f%%  <%3d>", btree, 100.0 * (stl - btree) / stl, btree_size;
    printf "    [%4.1f, %4.1f]\n", stl_bytes, btree_bytes;
    fflush();
  } else {
    printf "ERROR: %s unrecognized\n", $1
  }
}
