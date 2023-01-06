#!/bin/awk

# all 11 possible cube nets (modulo rotations and reflections):
#
#                                                     X
#  XXX   XX   XX   XX   X    X     X    X   XX    X   X
#   X   XX    X    X    XX  XXX  XXX   XX   X    XX  XX
#   X    X   XX    X   XX    X    X   XX   XX   XX   X
#   X    X    X   XX    X    X    X    X   X    X    X
#
#  3x4                                               2x5
#
# all 8 possible folds (modulo rotations and reflections):
#
#    |    |    |    |     |     |     |   <
#  v |    |    |  > |   < |     |   v |
#    |    |  > |    |     |   v |     |
#    |  ^ |    |    |     |     |     |
#  v | >  | <  | v  | v   | <   | v   | <

BEGIN {FS=""}

$0 ~ "\\." {
  for(x=1; x<=NF; x++) map[x, NR] = $x
  for(x=1; x<=NF; x++) Map[x, NR] = $x #TODO
  if(NF > x_max) x_max = NF
  y_max = NR
}

func move(dir, coord){

  split(coord, xy, SUBSEP)

  if(dir == 0) xy[1]++
  if(dir == 1) xy[2]++
  if(dir == 2) xy[1]--
  if(dir == 3) xy[2]--

  return xy[1] SUBSEP xy[2]

}

END {

  if(3 / x_max == 4 / y_max) side_length = x_max / 3
  if(4 / x_max == 3 / y_max) side_length = y_max / 3
  if(2 / x_max == 5 / y_max) side_length = x_max / 2
  if(5 / x_max == 2 / y_max) side_length = y_max / 2
  
  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      for(i=0; i<=3; i++){

        connection[i, x, y] = move(i, x SUBSEP y)

        if(map[connection[i, x, y]] !~ "\\.|#"){

          coord = x SUBSEP y
          while(map[coord] ~ "\\.|#") coord = move((i + 2) % 4, coord)
          coord = move(i, coord)

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

    if(facing == 0) Map[coord] = ">"
    if(facing == 1) Map[coord] = "v"
    if(facing == 2) Map[coord] = "<"
    if(facing == 3) Map[coord] = "^"

  }

  split(coord, xy, SUBSEP)
#  print xy[1], xy[2], facing
  print 1e3 * xy[2] + 4 * xy[1] + facing

#  for(y=1; y<=y_max; y++){
#    for(x=1; x<=x_max; x++){
#      printf Map[x, y]
#    }
#    print ""
#  }

}
