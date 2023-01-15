#!/bin/awk

BEGIN {FS = ""}

func neighbor(i, j, x, y){
  
  switch(1 + 3*(i % 4) + j){

    case  0: return x-1 SUBSEP y-1 ; break
    case  1: return x   SUBSEP y-1 ; break
    case  2: return x+1 SUBSEP y-1 ; break

    case  3: return x+1 SUBSEP y+1 ; break
    case  4: return x   SUBSEP y+1 ; break
    case  5: return x-1 SUBSEP y+1 ; break

    case  6: return x-1 SUBSEP y+1 ; break
    case  7: return x-1 SUBSEP y   ; break
    case  8: return x-1 SUBSEP y-1 ; break

    case  9: return x+1 SUBSEP y-1 ; break
    case 10: return x+1 SUBSEP y   ; break
    case 11: return x+1 SUBSEP y+1 ; break

  }

}

{for(x=1; x<=NF; x++) map[x, NR] = $x == "#" ? 1 : 0}

END {

  x_min = 1
  y_min = 1
  x_max = NF
  y_max = NR

  do{
    
    n_moves = 0

    for(x=x_min; x<=x_max; x++){
      for(y=y_min; y<=y_max; y++){
        
        if(map[x, y] != 1) continue

        neighbors = 0

        for(i=0; i<4; i++)
          for(j=0; j<=1; j++)
            neighbors += map[neighbor(i, j, x, y)]

        if(neighbors < 1) continue

        for(d=0; d<4; d++){
          target = neighbor(dir + d, 0, x, y)
          if(map[target] \
           + map[neighbor(dir + d, +1, x, y)] \
           + map[neighbor(dir + d, -1, x, y)] == 0){
             proposed[x, y] = target
             targeted[target]++
             n_moves++
             split(target, xy, SUBSEP)
             if(xy[1] > x_max) x_max = xy[1]
             if(xy[2] > y_max) y_max = xy[2]
             if(xy[1] < x_min) x_min = xy[1]
             if(xy[2] < y_min) y_min = xy[2]
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

    dir = (dir + 1) % 4

    delete targeted
    delete proposed

    ctr++

  }while(n_moves > 0)

  print ctr

}
