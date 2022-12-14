#!/bin/awk

{sub("A", 1) sub("B", 2) sub("C", 3)}
{sub("X", 1) sub("Y", 2) sub("Z", 3)}

($2 == 1 && $1 == 1) {sum += 3}
($2 == 1 && $1 == 2) {sum += 1}
($2 == 1 && $1 == 3) {sum += 2}

$2 == 2 {sum += $1 + 3}

($2 == 3 && $1 == 1) {sum += 2 + 6}
($2 == 3 && $1 == 2) {sum += 3 + 6}
($2 == 3 && $1 == 3) {sum += 1 + 6}

END {print sum}
