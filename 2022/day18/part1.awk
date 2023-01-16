#!/bin/awk

BEGIN {FS=","}

{occupied[$1, $2, $3] = 1}

END{
  for(c_str in occupied)
    for(dir=-1; dir<=1; dir+=2)
      for(i=1; i<=3; i++){
        split(c_str, c, SUBSEP)
        c[i] += dir
        if(occupied[c[1], c[2], c[3]] == "") ctr++
      }
  print ctr
}
