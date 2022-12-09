#!/begin/awk

BEGIN {n_segments = 10}

func abs(a) {return a < 0 ? -1 * a : a}

{
#  print "\n"$0
  for (i=$2; i>0; i--) {

    for (j=0; j<n_segments; j++) {
      previous_x[j] = x[j]
      previous_y[j] = y[j]
    }

    if ($1 == "R") x[0]++
    if ($1 == "L") x[0]--
    if ($1 == "U") y[0]++
    if ($1 == "D") y[0]--

    for (j=1; j<n_segments; j++) {
      if (abs(x[j] - x[j-1]) > 1 || abs(y[j] - y[j-1]) > 1) {
        if (x[j-1] - x[j] > 0) x[j]++
        if (x[j-1] - x[j] < 0) x[j]--
        if (y[j-1] - y[j] > 0) y[j]++
        if (y[j-1] - y[j] < 0) y[j]--
      }
    }

    trail[x[n_segments-1], y[n_segments-1]]++

#    print x[n_segments-1], y[n_segments-1]

  }
}

#$0 == "U 8" {for (j=0; j<n_segments; j++) print j, x[j], y[j]}

END {
  for(pos in trail) ctr++
  print ctr
}
