#!/bin/awk

BEGIN {FS=""}

$0 ~ "\\." {
  for(x=1; x<=NF; x++) map[x, NR] = $x
  for(x=1; x<=NF; x++) Map[x, NR] = $x #XXX
  if(NF > x_max) x_max = NF
  y_max = NR
}

END {

  facing = 0
  
  split($0, turns, "[0-9]*")
  split($0, dists, "L|R")
  
  x = 1
  y = 1

  while(map[x, y] != ".") x++

  for(i in dists){

    #print dists[i], turns[i+1]

    if(facing == 0){
      for(j=0; j<dists[i]; j++){
        x++
        if(map[x, y] == "#"){
          x--
          break
        }
        if(map[x, y] == "" || map[x, y] == " "){
          X = x-1
          while(map[X, y] ~ "\\.|#") X--
          if(map[X+1, y] == ".") x = X + 1
          if(map[X+1, y] == "#"){
            x--
            break
          }
        }
      }
    }

    else if(facing == 1){
      for(j=0; j<dists[i]; j++){
        y++
        if(map[x, y] == "#"){
          y--
          break
        }
        if(map[x, y] == "" || map[x, y] == " "){
          Y = y-1
          while(map[x, Y] ~ "\\.|#") Y--
          if(map[x, Y+1] == ".") y = Y + 1
          if(map[x, Y+1] == "#"){
            y--
            break
          }
        }
      }
    }

    else if(facing == 2){
      for(j=0; j<dists[i]; j++){
        x--
        if(map[x, y] == "#"){
          x++
          break
        }
        if(map[x, y] == "" || map[x, y] == " "){
          X = x+1
          while(map[X, y] ~ "\\.|#") X++
          if(map[X-1, y] == ".") x = X - 1
          if(map[X-1, y] == "#"){
            x++
            break
          }
        }
      }
    }

    else if(facing == 3){
      for(j=0; j<dists[i]; j++){
        y--
        if(map[x, y] == "#"){
          y++
          break
        }
        if(map[x, y] == "" || map[x, y] == " "){
          Y = y+1
          while(map[x, Y] ~ "\\.|#") Y++
          if(map[x, Y-1] == ".") y = Y - 1
          if(map[x, Y-1] == "#"){
            y++
            break
          }
        }
      }
    }

    if(turns[i+1] == "R") facing++
    if(turns[i+1] == "L") facing--

    if(facing > 3) facing = 0
    if(facing < 0) facing = 3

    if(facing == 0) Map[x, y] = ">"
    if(facing == 1) Map[x, y] = "v"
    if(facing == 2) Map[x, y] = "<"
    if(facing == 3) Map[x, y] = "^"

    #print "", x, y, facing

  }

#  print x, y, facing

  print 1e3 * y + 4 * x + facing

#  for(y=1; y<=y_max; y++){
#    for(x=1; x<=x_max; x++){
#      printf Map[x, y]
#    }
#    print ""
#  }

}
