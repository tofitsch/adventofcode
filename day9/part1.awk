#!/begin/awk

func abs(x) {return x < 0 ? x* - 1 : x}

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
