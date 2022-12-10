#!/bin/awk

BEGIN {X = 1}

function cycle() {ctr++; if((ctr + 20) % 40 == 0) sum += X * ctr;}

$1 == "addx" {cycle(); cycle(); X += $2}

$1 == "noop" {cycle()}

END {print sum}
