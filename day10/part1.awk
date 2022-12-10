#!/bin/awk

BEGIN {X = 1}

func cycle() {

  ctr++;

  if((ctr + 20) % 40 == 0) sum += X * ctr;

}

$1 == "noop" {cycle()}
$1 == "addx" {cycle(); cycle(); X += $2}

END {print sum}
