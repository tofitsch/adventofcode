#!/bin/awk

BEGIN {FS = ""}

func plot(){
  for(y=1; y<=NR; y++){
    for(x=1; x<=NF; x++) printf map[x, y]
    print ""
  }
  print ""
}

func neighbor_of_blizz(i, coord){

  split(coord, xy, SUBSEP)

  x = xy[1]
  y = xy[2]

  switch(i){
    case 0: return coord
    case 1: return ((x == NF-1) ? 2 : x+1) SUBSEP y
    case 2: return x SUBSEP ((y == NR-1) ? 2 : y+1)
    case 3: return ((x == 2) ? NF-1 : x-1) SUBSEP y
    case 4: return x SUBSEP ((y == 2) ? NR-1 : y-1)
  }

}

func neighbor_of_elve(i, coord){

  split(coord, xy, SUBSEP)

  x = xy[1]
  y = xy[2]

  switch(i){
    case 1: x++; break
    case 2: y++; break
    case 3: x--; break
    case 4: y--; break
  }

  return x SUBSEP y

}

func move(){
  
  for(b in blizz_pos) map[blizz_pos[b]] = "."

  for(b in blizz_pos){
    blizz_pos[b] = neighbor_of_blizz(blizz_dir[b], blizz_pos[b])
    map[blizz_pos[b]] = "X"
  }

  delete new_elves_pos
  n_elves = 0

  for(e in elves_pos){
    for(d=0; d<=4; d++){
      target = neighbor_of_elve(d, elves_pos[e])
      if(map[target] == "." || map[target] == "E"){
        if(map[target] == "." || d == 0){
          new_elves_pos[n_elves] = target
          n_elves++
        }
        map[target] = "E"
      }
    }
  }

  delete elves_pos

  for(e in new_elves_pos) elves_pos[e] = new_elves_pos[e]

}

{
  for(x=1; x<=NF; x++){

    if($x == ".") map[x, NR] = "."
    else if($x == "#") map[x, NR] = "#"
    else map[x, NR] = "X"

    if($x !~ "\\.|#"){
      ctr++
      blizz_pos[ctr] = x SUBSEP NR
    }

    if($x == ">") blizz_dir[ctr] = 1
    if($x == "v") blizz_dir[ctr] = 2
    if($x == "<") blizz_dir[ctr] = 3
    if($x == "^") blizz_dir[ctr] = 4

  }
}

END{

  elves_pos[0] = 2 SUBSEP 1
  map[elves_pos[0]] = "E"

  while(map[NF-1, NR] != "E"){
    plot()
    move()
    n_moves++
  }

  delete elves_pos
  elves_pos[0] = NF-1 SUBSEP NR
  map[2, 1] = "."

  while(map[2, 1] != "E"){
    plot()
    move()
    n_moves++
  }

  delete elves_pos
  elves_pos[0] = 2 SUBSEP 1
  map[NF-1, NR] = "."

  while(map[NF-1, NR] != "E"){
    plot()
    move()
    n_moves++
  }

  print n_moves

}
