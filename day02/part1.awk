#!/bin/awk

{sub("A", 1) sub("B", 2) sub("C", 3)}
{sub("X", 1) sub("Y", 2) sub("Z", 3)}

{sum += $2}

$1 == $2 {sum += 3}

($1 == 1 && $2 == 2) ||
($1 == 2 && $2 == 3) ||
($1 == 3 && $2 == 1) {sum += 6}

END {print sum}
