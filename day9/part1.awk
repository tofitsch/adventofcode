#!/begin/awk

func abs(a) {return a < 0 ? -1 * a : a}

{
  for (i=$2; i>0; i--) {

    if ($1 == "R") xH++
    if ($1 == "L") xH--
    if ($1 == "U") yH++
    if ($1 == "D") yH--

    if (abs(xT - xH) > 1 || abs(yT - yH) > 1) {
      if (xH - xT > 0) xT++
      if (xH - xT < 0) xT--
      if (yH - yT > 0) yT++
      if (yH - yT < 0) yT--
    }

    trail[xT, yT]++

  }
}

END {
  for(pos in trail) ctr++
  print ctr
}
