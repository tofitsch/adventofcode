#!/bin/awk

BEGIN {FS=",|-"}

($1 <= $3 && $2 >= $4) ||
($1 >= $3 && $2 <= $4) ||
($1 >= $3 && $1 <= $4) ||
($2 >= $3 && $2 <= $4) {ctr++}

END {print ctr}
