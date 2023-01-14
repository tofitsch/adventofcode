#!/bin/awk

# all 11 valid cube nets (modulo rotations and reflections):
#
#                                                     X
#  XXX   XX   XX   XX   X    X     X    X   XX    X   X
#   X   XX    X    X    XX  XXX  XXX   XX   X    XX  XX
#   X    X   XX    X   XX    X    X   XX   XX   XX   X
#   X    X    X   XX    X    X    X    X   X    X    X
#
#  3x4                                               2x5
#
# all 9 valid folds (modulo rotations and reflections):
#
#  1   2    3    4    5     6     7     8     9
#    |    |    |    |     |     |     |   < |
#  v |    |    |  > |   < |     |   v |     |    <
#    |    |  > |    |     |   v |     |     |
#    |  ^ |    |    |     |     |     |     |
#  v | >  | <  | v  | v   | <   | v   | <   | <

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
    
      if(edge[coord] != 1 || x < 1 || y < 1) continue

      if(fold_type == 1){
        target = neighbor(i, -4*side_length + 1, x SUBSEP y)
        if(edge[(i + 2) % 4, target] == 1 && map[target] ~ "\\.|#" && map[neighbor(i, -1, target)] !~ "\\.|#"){
          edge[coord] = target
          edge[(i + 2) % 4, target] = x SUBSEP y
#          print "fold A", x, y, target, turn[coord] #XXX
          Map[x, y] = "A" #XXX
          Map[target] = "A" #XXX
        }
      }

      else if(fold_type == 2){
        target = x SUBSEP y
        for(j=0; j<side_length; j++){
          target = neighbor(i, 1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, 1, target)
          if(edge[(i + (mirror ? 1 : 3)) % 4, target] == 1 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? 3 : 1 #TODO
            edge[(i + (mirror ? 1 : 3)) % 4, target] = x SUBSEP y
            turn[(i + (mirror ? 1 : 3)) % 4, target] = mirror ? 1 : 3 #TODO
#            print "fold B"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "B" #XXX
            Map[target] = "B" #XXX
            break
          }
        }
      }

      else if(fold_type == 3){
        offset = ((i % 2 ? x : y) - 1) % side_length
        target = neighbor(i, -side_length, x SUBSEP y)
        target = neighbor((i + (mirror ? 3 : 1)) % 4, ((i + (mirror ? 3 : 1)) % 4 > 1 ? -2*(side_length-offset) + 1 : -2*offset - 1) + 3*side_length, target)
#        if(x==1 && y==12) print i, x, y, target, (i + (mirror ? 3 : 1)) % 4, testA, testB, y - (testA + testB)
        if(edge[i, target] == 1 && map[target] ~ "\\.|#" && map[neighbor(i, 1, target)] !~ "\\.|#"){
          edge[coord] = target
          turn[coord] = 2
          edge[i, target] = x SUBSEP y
          turn[i, target] = 2
#          print "fold C"mirror, x, y, target, turn[coord] #XXX
          Map[x, y] = "C" #XXX
          Map[target] = "C" #XXX
        }
      }

      else if(fold_type == 4){
        target = neighbor(i, -4*side_length, x SUBSEP y)
        for(j=0; j<side_length; j++){
          target = neighbor(i, 1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, 1, target)
          if(edge[(i + (mirror ? 1 : 3)) % 4, target] == 1 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? 3 : 1 #TODO
            edge[(i + (mirror ? 1 : 3)) % 4, target] = x SUBSEP y
            turn[(i + (mirror ? 1 : 3)) % 4, target] = mirror ? 1 : 3 #TODO
#            print "fold D"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "D" #XXX
            Map[target] = "D" #XXX
            break
          }
        }
      }

      else if(fold_type == 5){
        target = neighbor((i + (mirror ? 3 : 1)) % 4, -2*side_length, x SUBSEP y)
        target = neighbor(i, -4*side_length, target)
        for(j=0; j<side_length; j++){
          target = neighbor(i, 1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, 1, target)
          if(edge[(i + (mirror ? 1 : 3)) % 4, target] == 1 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? 3 : 1 #TODO
            edge[(i + (mirror ? 1 : 3)) % 4, target] = x SUBSEP y
            turn[(i + (mirror ? 1 : 3)) % 4, target] = mirror ? 1 : 3 #TODO
#            print "fold E"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "E" #XXX
            Map[target] = "E" #XXX
            break
          }
        }
      }

      else if(fold_type == 6){
        target = neighbor((i + (mirror ? 3 : 1)) % 4, -2*side_length + 1, x SUBSEP y)
        target = neighbor(i, -2*side_length + 1, target)
        for(j=0; j<side_length; j++){
          target = neighbor(i, -1, target)
          target = neighbor((i + (mirror ? 3 : 1)) % 4, -1, target)
          if(edge[(i + (mirror ? 1 : 3)) % 4, target] == 1 && map[target] ~ "\\.|#"){
            edge[coord] = target
            turn[coord] = mirror ? 3 : 1 #TODO
            edge[(i + (mirror ? 1 : 3)) % 4, target] = x SUBSEP y
            turn[(i + (mirror ? 1 : 3)) % 4, target] = mirror ? 1 : 3 #TODO
#            print "fold F"mirror, x, y, target, turn[coord] #XXX
            Map[x, y] = "F" #XXX
            Map[target] = "F" #XXX
            break
          }
        }
      }

      else if(fold_type == 7){
        target = neighbor(i, -4*side_length + 1, x SUBSEP y)
        target = neighbor((i + (mirror ? 3 : 1)) % 4, 2*side_length, target)
        if(edge[(i + 2) % 4, target] == 1 && map[target] ~ "\\.|#" && map[neighbor(i, -1, target)] !~ "\\.|#"){
          edge[coord] = target
          edge[(i + 2) % 4, target] = x SUBSEP y
#          print "fold G", x, y, target, turn[coord] #XXX
          Map[x, y] = "G" #XXX
          Map[target] = "G" #XXX
        }
      }

      else if(fold_type == 8){
        #TODO
      }

      else if(fold_type == 9){
        #TODO
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

        if(map[connection[i, x, y]] !~ "\\.|#"){
          edge_const[i, x, y] = 1
          edge[i, x, y] = 1
        }

      }
    }
  }

  for(f=1; f<=9; f++) fold(f)

  for(coord in edge_const) connection[coord] = edge[coord]

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
    
#    if(i == 3) break #XXX
    
    for(j=0; j<dists[i]; j++){

      prev_coord = coord

      coord = connection[facing, coord]

      if(coord != prev_coord) facing += turn[facing, prev_coord]

      facing %= 4

#      if(facing == 0) Map[coord] = ">"
#      if(facing == 1) Map[coord] = "v"
#      if(facing == 2) Map[coord] = "<"
#      if(facing == 3) Map[coord] = "^"

      #split(coord, xy, SUBSEP)
      #print facing, xy[1], xy[2]

    }

    if(turns[i+1] == "R") facing += 1
    if(turns[i+1] == "L") facing += 3

    facing %= 4

  }

  for(y=1; y<=y_max; y++){
    for(x=1; x<=x_max; x++){
      printf Map[x, y]
    }
    print ""
  }

  split(coord, xy, SUBSEP)
#  print xy[1], xy[2], facing
  print 1e3 * xy[2] + 4 * xy[1] + facing


}
