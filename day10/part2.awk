
#!/bin/awk

BEGIN {X = 1; width = 40}

func abs(a) {return a < 0 ? -1 * a : a}

function cycle() {
  if(abs(X - ctr % width) < 2) printf "#"
  else printf "."
  if(ctr % width == 1) print ""
  ctr++;
}

$1 == "noop" {cycle()}
$1 == "addx" {cycle(); cycle(); X += $2}

END {print sum}
