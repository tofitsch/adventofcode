#!/bin/awk

BEGIN {FS=""; goal = 1e12}

func add_row(){
  n_rows++
  map[1, n_rows] = "#"
  map[9, n_rows] = "#"
  for(i=2; i<9; i++) map[i, n_rows] = "."
}

func plot(){
  print ""
  for(y=n_rows; y>=min_y; y--){
    for(x=1; x<=9; x++) printf map[x, y]
    print " "y
  }
}

func spawn(){
  
  for(y=min_y; y<=n_rows; y++){
    blocked_row = 1
    for(x=2; x<9; x++){
      if(map[x, y] == "@") map[x, y] = "#"
      if(map[x, y] == "#") max_y = y
      if(map[x, y] != "#" && map[x, y+1] != "#") blocked_row = 0
    }
    if(blocked_row == 1) min_y = y
  }

  n_occupied_at_max_y = 0
  for(x=2; x<9; x++)
    if(map[x, max_y] == "#")
      n_occupied_at_max_y++

  if(periodicity == "" && ctr % 5 == 0 && n_occupied_at_max_y > 1){ 
    if(same_state[time % NF] != ""){

      offset = same_state[time % NF]
      periodicity = n_blocks - same_state[time % NF]
      delta_y = max_y - max_y_at[time % NF]

      n_periods_to_skip = int((goal - n_blocks) / periodicity)

      n_blocks += n_periods_to_skip

    }
    same_state[time % NF] = n_blocks
    max_y_at[time % NF] = max_y
  }

  if(ctr % 5 == 0){
    y = max_y + 4
    while(n_rows < y) add_row()
    for(x=4; x<8; x++) map[x, y] = "@"
  }
  else if(ctr % 5 == 1){
    y = max_y + 4
    while(n_rows < y + 2) add_row()
    map[5, y] = "@"
    for(x=4; x<=6; x++) map[x, y+1] = "@"
    map[5, y+2] = "@"
  }
  else if(ctr % 5 == 2){
    y = max_y + 4
    while(n_rows < y + 2) add_row()
    for(x=4; x<=6; x++) map[x, y] = "@"
    map[6, y+1] = "@"
    map[6, y+2] = "@"
  }
  else if(ctr % 5 == 3){
    y = max_y + 4
    while(n_rows < y + 3) add_row()
    for(Y=y; Y<=y+3; Y++) map[4, Y] = "@"
  }
  else if(ctr % 5 == 4){
    y = max_y + 4
    while(n_rows < y + 1) add_row()
    for(x=4; x<=5; x++)
      for(Y=y; Y<=y+1; Y++)
        map[x, Y] = "@"
  }

  ctr++
  n_blocks++

  print n_blocks, min_y, max_y

  #plot()

}

func tick(){

  time++

  direction = $(int(time / 2) % NF + 1) == "<" ? -1 : 1

  if(time % 2 == 0){
    for(y=min_y; y<=n_rows; y++){
      for(x=2; x<=8; x++){
        if(map[x, y] == "@" && map[x, y-1] == "#") return spawn()
      }
    }
  }
  else{
    for(y=min_y; y<=n_rows; y++){
      for(x=0; x<=6; x++){
        X = direction == -1 ? 2 + x : 8 - x
        if(map[X, y] == "@" && map[X+direction, y] == "#") return ""
      }
    }
  }

  for(y=min_y; y<=n_rows; y++){
    for(x=0; x<=6; x++){
      X = direction == -1 ? 2 + x : 8 - x
      if(map[X, y] == "@"){
        if(time % 2 == 0){
          map[X, y-1] = "@"
          map[X, y] = "."
        }
        else{
          map[X+direction, y] = "@"
          map[X, y] = "."
        }
      }
    }
  }

  #plot()

}

{

  for(i=1; i<=9; i++) map[i, 1] = "#"

  ctr = 0
  n_rows = 1

  add_row()
  spawn()

#  plot()

  while(n_blocks < goal) tick()

  #plot()

  max_y += delta_y * n_periods_to_skip
  print max_y - 1
  
}
