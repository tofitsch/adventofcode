#!/bin/awk

BEGIN {FS=","}

{map[$1, $2, $3] = 1}

END{
  for(c_str in map)
    for(dir=-1; dir<=1; dir+=2)
      for(i=1; i<=3; i++){
        split(c_str, c, SUBSEP)
        c[i] += dir
        if(map[c[1], c[2], c[3]] == "") ctr++
      }
  print ctr
}
