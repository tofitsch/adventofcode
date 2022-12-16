#!/bin/awk

func abs(a) {return a < 0 ? -1 * a : a}

BEGIN{FS="=|,|:" ; Y = 2e6}

{

  for(j=2; j<=8; j+=2){
    dim = (j/2+1)%2
    if(min[dim] == "" || $j < min[dim]) min[dim] = $j
    if(max[dim] == "" || $j > max[dim]) max[dim] = $j
  }
  
  map[$2, $4] = "S"
  map[$6, $8] = "B"

  signal_x[NR] = $2
  signal_y[NR] = $4

  distance[$2, $4] = abs($2 - $6) + abs($4 - $8) + 1

}

END {

  for(i in signal_x){
    for(X=min[0]; X<=max[0]; X++){
      if(abs(signal_x[i] - X) + abs(signal_y[i] - Y) < distance[signal_x[i], signal_y[i]] && map[X, Y] == "") map[X, Y] = "#"
    }
  }

  for(x=min[0]; x<=max[0]; x++){
    if(map[x, Y] != "") ctr++
  }

  print ctr

}
