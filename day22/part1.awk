#!/bin/awk

BEGIN {FS=""}

$0 ~ "\\." {
  for(x=1; x<=NF; x++) map[x, NR] = $x
  if(NF > x_max) x_max = NF
  y_max = NR
}

func neighbor(dir, coord){

  split(coord, xy, SUBSEP)

  if(dir == 0) xy[1]++
  if(dir == 1) xy[2]++
  if(dir == 2) xy[1]--
  if(dir == 3) xy[2]--

  return xy[1] SUBSEP xy[2]

}

END {
  
  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      for(i=0; i<=3; i++){

        connection[i, x, y] = neighbor(i, x SUBSEP y)

        if(map[connection[i, x, y]] !~ "\\.|#"){

          coord = x SUBSEP y
          while(map[coord] ~ "\\.|#") coord = neighbor((i + 2) % 4, coord)
          coord = neighbor(i, coord)

          connection[i, x, y] = coord
  
        }

        if(map[connection[i, x, y]] == "#") connection[i, x, y] = x SUBSEP y

      }
    }
  }

  split($0, turns, "[0-9]*")
  split($0, dists, "L|R")

  x = 1
  
  while(map[x, 1] != ".") x++

  coord = x SUBSEP 1
  facing = 0

  for(i in dists){
    
    for(j=0; j<dists[i]; j++) coord = connection[facing, coord]

    if(turns[i+1] == "R") facing++
    if(turns[i+1] == "L") facing--

    if(facing > 3) facing = 0
    if(facing < 0) facing = 3

  }

  split(coord, xy, SUBSEP)

  print 1e3 * xy[2] + 4 * xy[1] + facing

}
