#!/bin/awk

BEGIN {RS=""}

{
  sum = 0
  for(i=1; i<=NF; i++) sum += $i
  arr[NR] = sum
}

END {
  asort(arr)
  for(i=NR-2; i<=NR; i++) solution += arr[i]
  print solution
}
