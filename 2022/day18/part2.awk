#!/bin/awk

BEGIN {
  FS = ",";
  inf = 1e5
  for(i=1; i<=3; i++) min[i] = inf
}

func do_dijkstra(){

  for(x=min[1]-1; x<=max[1]+1; x++){
    for(y=min[2]-1; y<=max[2]+1; y++){
      for(z=min[3]-1; z<=max[3]+1; z++){
        if(dijkstra[x, y, z] < inf) dijkstra[x, y, z] = inf
        visited[x, y, z] = 0
      }
    }
  }

  dijkstra[min[1]-1, min[2]-1, min[3]-1] = 0

  while(1 == 1){

    min_dijkstra = inf

    for(c_str in visited){
      split(c_str, c, SUBSEP)
      if(visited[c[1], c[2], c[3]] == 1) continue
      if(dijkstra[c[1], c[2], c[3]] < min_dijkstra){
        min_dijkstra = dijkstra[c[1], c[2], c[3]]
        position = c_str
      }
    }

    split(position, C, SUBSEP)
    if(visited[C[1], C[2], C[3]]) break
    visited[C[1], C[2], C[3]] = 1

    for(dir=-1; dir<=1; dir+=2){
      for(i=1; i<=3; i++){
        split(position, c, SUBSEP)
        c[i] += dir
        if(dijkstra[c[1], c[2], c[3]] > inf) continue
        new_dijkstra = dijkstra[C[1], C[2], C[3]] + 1
        if(dijkstra[c[1], c[2], c[3]] > new_dijkstra) dijkstra[c[1], c[2], c[3]] = new_dijkstra
      }
    }

  }

}

{
  dijkstra[$1, $2, $3] = inf + 1
  for(i=1; i<=3; i++){
    if($i < min[i]) min[i] = $i
    if($i > max[i]) max[i] = $i
  }
}

END{
  do_dijkstra()
  for(c_str in dijkstra){
    split(c_str, c, SUBSEP)
    if(dijkstra[c[1], c[2], c[3]] < inf) continue
    for(dir=-1; dir<=1; dir+=2){
      for(i=1; i<=3; i++){
        split(c_str, c, SUBSEP)
        c[i] += dir
        if(dijkstra[c[1], c[2], c[3]] < inf) ctr++
      }
    }
  }
  print ctr
}
