#!/bin/awk

BEGIN {RS=""}
{sum = 0; for(i=1; i<=NF; i++) sum += $i; arr[NR] = sum}
END {asort(arr); printf arr[NR] "\n"}
