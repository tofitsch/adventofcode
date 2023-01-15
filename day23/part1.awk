#!/bin/awk

BEGIN {FS = ""}

func plot(){
  for(x=x_min; x<=x_max; x++){
    for(y=y_min; y<=y_max; y++) printf map[x, y] == 1 ? "#" : "."
    print ""
  }
  print ""
}

func neighbor(i, x, y){

  switch(i % 8){
    case 0: return x   SUBSEP y+1 ; break
    case 1: return x+1 SUBSEP y+1 ; break
    case 2: return x+1 SUBSEP y   ; break
    case 3: return x+1 SUBSEP y-1 ; break
    case 4: return x   SUBSEP y-1 ; break
    case 5: return x-1 SUBSEP y-1 ; break
    case 6: return x-1 SUBSEP y   ; break
    case 7: return x-1 SUBSEP y+1 ; break
  }

}

{for(x=1; x<=NF; x++) map[x, NR] = $x == "#" ? 1 : 0}

END {

  plot()

  x_max = NF
  y_max = NR

  for(r=0; r<10; r++){

    for(x=x_min; x<=x_max; x++){
      for(y=y_min; y<=y_max; y++){

        for(i=0; i<8; i++) neighbors += map[neighbor(i, x, y)]
        if(neighbors == 0) continue

        for(d=0; d<4; d++){
          target = neighbor(dir + 2*d, x, y)
          if( map[target]\
           + map[neighbor(dir + 2*d + 1, x, y)] \
           + map[neighbor(dir + 2*d - 1 , x, y)] == 0){
             proposed[x, y] = target
             targeted[target]++
             break
          }
        }

      }
    }

    for(x=x_min; x<=x_max; x++){
      for(y=y_min; y<=y_max; y++){
        if(map[x, y] == 1 && targeted[proposed[x, y]] == 1){
          map[x, y] = 0
          map[proposed[x, y]] = 1
        }
      }
    }

    dir = (dir + 2) % 8

    x_min--
    y_min--
    x_max++
    y_max++

    delete targeted
    delete proposed

    plot()

  }

  for(x=x_min; x<=x_max; x++){
    for(y=y_min; y<=y_max; y++){
      if(map[x, y] == 1){
        if(x > x_max_rect) x_max_rect = x
        if(y > y_max_rect) y_max_rect = y
        if(x < x_min_rect || x_min_rect == x_min) x_min_rect = x
        if(y < y_min_rect || y_min_rect == y_max) y_min_rect = y
      }
    }
  }

  for(x=x_min_rect; x<=x_max_rect; x++)
    for(y=y_min_rect; y<=y_max_rect; y++)
      if(map[x, y] == 0) empty ++

  print empty

}


