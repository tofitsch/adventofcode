#!/bin/awk

BEGIN {FS=""}

function scan(revert_direction, swap_loops){
  for(x=1; x<=NF; x++){
    max = -1
    for(y=1; y<=NR; y++){
      y_rev = revert_direction ? NR + 1 - y : y;
      Y = swap_loops ? x : y_rev;
      X = swap_loops ? y_rev : x;
      if(val[X, Y] > max){
        vis[X, Y] = 1
        max = val[X, Y]
      }
    }
  }
}

{for(x=1; x<=NF; x++) val[x, NR] = $x}

END { 

  scan(0, 0)
  scan(0, 1)
  scan(1, 0)
  scan(1, 1)

  for(x=1; x<=NF; x++) for(y=1; y<=NR; y++) if(vis[x, y] == 1) n_visible++

  print n_visible

}
