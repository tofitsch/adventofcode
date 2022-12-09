#!/begin/awk

func abs(a) {return a < 0 ? -1 * a : a}

{
  for (i=$2; i>0; i--) {

    previous_xH = xH
    previous_yH = yH

    if ($1 == "R") xH++
    if ($1 == "L") xH--
    if ($1 == "U") yH++
    if ($1 == "D") yH--

    if (abs(xT - xH) > 1 || abs(yT - yH) > 1) {
      xT = previous_xH
      yT = previous_yH
    }

    trail[xT, yT]++

  }
}

END {
  for(pos in trail) ctr++
  print ctr
}
