#!/bin/awk

BEGIN {FS=","}

{map[$1, $2, $3] = 1}

END{
  for(xyz_str in map){
    split(xyz_str, xyz, SUBSEP)
    for(dir=-1; dir<=1; dir+=2){
      for(i=1; i<=3; i++){
        x = xyz[1]
        y = xyz[2]
        z = xyz[3]
        if(i==1) x+= dir
        if(i==2) y+= dir
        if(i==3) z+= dir
        if(map[x, y, z] == "") ctr++
      }
    }
  }
  print ctr
}
