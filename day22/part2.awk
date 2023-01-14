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
#  1   2    3    4    5     6     7     8
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

func neighbor(dir, dist, coord){

  split(coord, xy, SUBSEP)

  if(dir == 0) xy[1] += dist
  if(dir == 1) xy[2] += dist
  if(dir == 2) xy[1] -= dist
  if(dir == 3) xy[2] -= dist

  return xy[1] SUBSEP xy[2]

}

func fold(fold_type){

  for(coord in edge){

    split(coord, ixy, SUBSEP)

    i = ixy[1]
    x = ixy[2]
    y = ixy[3]

    if(x == "" || y == "") continue

    for(mirror=0; mirror<=1; mirror++){
    
      if(edge[coord] != 0) continue

      if(fold_type == 1){
        target = neighbor(i, -4 * side_length + 1, x SUBSEP y)
        if(map[target] ~ "\\.|#" && map[neighbor(i, -1, target)] !~ "\\.|#"){
          edge[coord] = target
          turn[coord] = 2
          print "fold A", x, y, target, turn[coord] #XXX
          Map[x, y] = "A" #XXX
        }
      }

      else if(fold_type == 2){
        target = x SUBSEP y
        for(j=0; j<side_length; j++){
          target = neighbor(i, 1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, 1, target)
          if(edge[target] == 0 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? -1 : 1 #TODO
            edge[target] = coord
            turn[target] = mirror ? -1 : 1 #TODO
            print "fold B"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "B" #XXX
            Map[target] = "B" #XXX
            break
          }
        }
      }

      else if(fold_type == 3){
        offset = ((i % 2 ? x : y) - 1) % side_length
        target = neighbor(i, -side_length, x SUBSEP y)
        target = neighbor((i + (mirror ? 3 : 1)) % 4, (i + (mirror ? 3 : 1)) % 4 > 1 ? -(2*(1-offset) + 1) + 2*side_length : -(2*offset + 1) + 3*side_length, target)
        if(edge[target] == 0 && map[target] ~ "\\.|#" && map[neighbor(i, 1, target)] !~ "\\.|#"){
          edge[coord] = target
          turn[coord] = 2
          edge[target] = x SUBSEP y
          turn[target] = 2
          print "fold C"mirror, x, y, target, turn[coord] #XXX
          Map[x, y] = "C" #XXX
          Map[target] = "C" #XXX
        }
      }

      else if(fold_type == 4){
        #TODO
      }

      else if(fold_type == 5){
        target = neighbor((i + (mirror ? 3 : 1)) % 4, -2*side_length, x SUBSEP y)
        target = neighbor(i, -4*side_length, target)
        for(j=0; j<side_length; j++){
          target = neighbor(i, 1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, 1, target)
          if(edge[target] == 0 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? -1 : 1 #TODO
            edge[target] = x SUBSEP y
            turn[target] = mirror ? -1 : 1 #TODO
            print "fold E"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "E" #XXX
            Map[target] = "E" #XXX
            break
          }
        }
      }

    }

  }

}

END {

  if(3 / x_max == 4 / y_max) side_length = x_max / 3
  if(4 / x_max == 3 / y_max) side_length = y_max / 3
  if(2 / x_max == 5 / y_max) side_length = x_max / 2
  if(5 / x_max == 2 / y_max) side_length = y_max / 2
  
  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      for(i=0; i<=3; i++){

        if(map[x, y] !~ "\\.|#") continue

        connection[i, x, y] = neighbor(i, 1, x SUBSEP y)

        if(map[connection[i, x, y]] !~ "\\.|#") edge[i, x, y] = 0

      }
    }
  }

  for(f=1; f<=9; f++) fold(f)

  for(coord in edge) connection[coord] = edge[coord]

  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      for(i=0; i<=3; i++){

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
    
    for(j=0; j<dists[i]; j++){

      prev_coord = coord

      coord = connection[facing, coord]

      if(coord != prev_coord) facing += turn[facing, prev_coord]

      if(facing > 3) facing = 0
      if(facing < 0) facing = 3

#      if(facing == 0) Map[coord] = ">"
#      if(facing == 1) Map[coord] = "v"
#      if(facing == 2) Map[coord] = "<"
#      if(facing == 3) Map[coord] = "^"
#
#      split(coord, xy, SUBSEP)
#      print facing, do_turn, xy[1], xy[2]

    }

    if(turns[i+1] == "R") facing++
    if(turns[i+1] == "L") facing--

    if(facing > 3) facing = 0
    if(facing < 0) facing = 3

  }

  split(coord, xy, SUBSEP)
#  print xy[1], xy[2], facing
  print 1e3 * xy[2] + 4 * xy[1] + facing

  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      printf Map[x, y]
    }
    print ""
  }

}
