#!/bin/awk

BEGIN {FS=""}

function scan(x_max, y_max, revert_direction, swap_loops){

  for(x=1; x<=NF; x++){
    max = -1
    for(y=1; y<=NR; y++){
      y_s = revert_direction == 1 ? y_max + 1 - y : y;
      Y = swap_loops == 1 ? x : y_s;
      X = swap_loops == 1 ? y_s : x;
      if(val[X, Y] > max){
        vis[X, Y] = 1
        max = val[X, Y]
      }
    }
  }

}

{for(x=1; x<=NF; x++) val[x, NR] = $x}

END { 

  scan(NF, NR, 0, 0)
  scan(NF, NR, 0, 1)
  scan(NF, NR, 1, 0)
  scan(NF, NR, 1, 1)

  for(x=1; x<=NF; x++){
    for(y=1; y<=NR; y++){
      if(vis[x, y] == 1) n_visible++
    }
  }

  print n_visible

}
