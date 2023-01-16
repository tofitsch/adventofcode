#!/bin/awk

BEGIN {

 FS=""

 neighbors[-1] = 0
 neighbors[0] = 0
 neighbors[1] = 0

 infinity = 1e5

 for (i=1; i<=26; i++) char_to_height[sprintf("%c", i + 96)] = i

 char_to_height["S"] = 1
 char_to_height["E"] = 26

}

{

  for(x=1; x<=NF; x++){

    height[x-1, NR-1] = char_to_height[$x]

    dijkstra[x-1, NR-1] = infinity

    if($x == "E"){end[0] = x-1 ; end[1] = NR-1}

  }

}

END {
  
  dijkstra[end[0], end[1]] = 0

  while(1){
    
    min[0] = -1
    min[1] = -1
    min["val"] = infinity
    
    for(x=0; x<NF; x++){
      for(y=0; y<NR; y++){
        if(visited[x, y] == 1) continue
        if(dijkstra[x, y] < min["val"]){
          min[0] = x
          min[1] = y
          min["val"] = dijkstra[x, y]
        }
      }
    }

    if(min[0] < 0) break

    visited[min[0], min[1]] = 1

    if(height[min[0], min[1]] == 1) distance[min[0], min[1]] = dijkstra[min[0], min[1]]

    for(x in neighbors){
      for(y in neighbors){
        if(x == y || x == -y) continue
        if(min[0] + x < 0 || min[0] + x > NF-1 || min[1] + y < 0 || min[1] + y > NR-1) continue
        if(visited[min[0] + x, min[1] + y] == 1) continue
        if(height[min[0] + x, min[1] + y] - height[min[0], min[1]] < -1) continue
        new_dijkstra = dijkstra[min[0], min[1]] + 1
        if(new_dijkstra < dijkstra[min[0] + x, min[1] + y]) dijkstra[min[0] + x, min[1] + y] = new_dijkstra
      }
    }

  }

  asort(distance)

  print distance[1] 

}
