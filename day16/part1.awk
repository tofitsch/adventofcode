#!/bin/awk

func calc_distance(a, b){
  
  for(i in rates){
    dijkstra[i] = inf
    visited[i] = 0
  }

  dijkstra[a] = 0

  while(dijkstra[b] == inf){
    
    min_dijkstra = inf

    for(i in visited){
      if(visited[i] == 1) continue
      if(dijkstra[i] < min_dijkstra){
        min_dijkstra = dijkstra[i]
        position = i
      }
    }
    
    visited[position] = 1
    
    for(c=0; c<n_connections[position]; c++){
      node = connections[position, c]
      new_dijkstra = dijkstra[position] + 1
      if(dijkstra[node] > new_dijkstra) dijkstra[node] = new_dijkstra
    }

  }

  distance[a, b] = dijkstra[b]

#  print a, b, distance[a, b]

}

func next_permutation(arr, n){
  # Narayana Pandita algo

  for(k=n-1; k>1; k--) if(arr[k] < arr[k+1]) break
  if(!(arr[k] < arr[k+1])) return 0

  for(l=n; l>k; l--) if(arr[k] < arr[l]) break

  swap = arr[k]
  arr[k] = arr[l]
  arr[l] = swap

  for(l=n; l>k; l--) buffer[l] = arr[l]
  for(m=n; m>k; m--) arr[m] = buffer[k+1+n-m]

  return 1
}

BEGIN{FS = "Valve | has.*=|; tunnel.*valves? |, "; n_moves = 30; inf = 1e5}

{
  rates[$2] = $3
  if($3 > 0){
    n_non_zero_valves++
    non_zero_valves[n_non_zero_valves] = $2
  }
  n_connections[$2] = NF-3
  for(i=4; i<=NF; i++) connections[$2, i-4] = $i
  connections[$2, -1] = "op"
}

END{
  
  for(x in rates){
    for(y in rates){
      calc_distance(x, y)
    }
  }

  asort(non_zero_valves)

  print n_non_zero_valves

  do{
    ctr++
    if(ctr % 1e6 == 0) print ctr
    for(i=1; i<=n_non_zero_valves; i++) printf non_zero_valves[i]" "
    print ""
  }
  while(next_permutation(non_zero_valves, n_non_zero_valves) != 0)

  print ctr

}
