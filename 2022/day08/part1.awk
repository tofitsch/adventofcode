#!/bin/awk

BEGIN {FS=""}

func scan(mirrored, transposed){
  for(x=1; x<=NF; x++){
    max = -1
    for(y=1; y<=NR; y++){
      y_rev = mirrored ? NR + 1 - y : y;
      Y = transposed ? x : y_rev;
      X = transposed ? y_rev : x;
      if(height[X, Y] > max){
        is_visible[X, Y] = 1
        max = height[X, Y]
      }
    }
  }
}

{for(x=1; x<=NF; x++) height[x, NR] = $x}

END { 

  scan(0, 0)
  scan(0, 1)
  scan(1, 0)
  scan(1, 1)

  for(x=1; x<=NF; x++) for(y=1; y<=NR; y++) if(is_visible[x, y]) n_visible++

  print n_visible

}
