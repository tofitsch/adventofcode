#!/bin/awk

func recursive_move(move, ctr_A, ctr_B, path_A, path_B, path_length_A, path_length_B, inst_rate_A, inst_rate_B, sum_A, sum_B,  c, i, skip, move_arr){
  
  if(move != ""){

    split(move, move_arr, ":")

    if(move_arr[1] == "A"){
      path_A[ctr_A] = move_arr[2]
      dt = distance[path_A[ctr_A - 1], path_A[ctr_A]] + 1
      path_length_A += dt
      sum_A += inst_rate_A * dt
      inst_rate_A += rates[path_A[ctr_A]]
    }

    if(move_arr[1] == "B"){
      path_B[ctr_B] = move_arr[2]
      dt = distance[path_B[ctr_B - 1], path_B[ctr_B]] + 1
      path_length_B += dt
      sum_B += inst_rate_B * dt
      inst_rate_B += rates[path_B[ctr_B]]
    }

  }

#  CTR++
#  if(CTR % 1e4 == 0){
#    for(i=0 ; i<=15; i++) printf (i<=ctr_A ? path_A[i] : "  ")":"(i<=ctr_B ? path_B[i] : "  ") "|"
#    print sum_A + sum_B
#  }

  unused_rate = max_rate - (inst_rate_A + inst_rate_B)
  k
  attainable_sum = sum_A + sum_B + inst_rate_A * (n_moves - path_length_A) + inst_rate_B * (n_moves - path_length_B)
  attainable_sum += unused_rate * (n_moves - (path_length_A > path_length_B ? path_length_B : path_length_A) - (n_non_zero_valves - (ctr_A + ctr_B)))

  if(attainable_sum > max_sum){

    if(path_length_A < n_moves){
      for(c in non_zero_valves){
        skip = 0
        for(i=0; i<=ctr_A; i++) if(path_A[i] == non_zero_valves[c]) {skip = 1; break}
        if(skip == 0) for(i=0; i<=ctr_B; i++) if(path_B[i] == non_zero_valves[c]) {skip = 1; break}
        if(skip == 0) recursive_move("A:"non_zero_valves[c], ctr_A+1, ctr_B, path_A, path_B, path_length_A, path_length_B, inst_rate_A, inst_rate_B, sum_A, sum_B)
      }
    }

    if(path_length_B < n_moves){
      for(c in non_zero_valves){
        skip = 0
        for(i=0; i<=ctr_A; i++) if(path_A[i] == non_zero_valves[c]) {skip = 1; break}
        if(skip == 0) for(i=0; i<=ctr_B; i++) if(path_B[i] == non_zero_valves[c]) {skip = 1; break}
        if(skip == 0) recursive_move("B:"non_zero_valves[c], ctr_A, ctr_B+1, path_A, path_B, path_length_A, path_length_B, inst_rate_A, inst_rate_B, sum_A, sum_B)
      }
    }

  }

  sum_A += inst_rate_A * (n_moves - path_length_A)
  sum_B += inst_rate_B * (n_moves - path_length_B)

  if(sum_A + sum_B > max_sum) max_sum = sum_A + sum_B

}

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

BEGIN{FS = "Valve | has.*=|; tunnel.*valves? |, "; n_moves = 26; inf = 1e5}

{
  rates[$2] = $3
  max_rate += $3
  if($3 > 0){
    nodes[$2] = ""
    n_non_zero_valves++
    non_zero_valves[n_non_zero_valves] = $2
  }
  n_connections[$2] = NF-3
  for(i=4; i<=NF; i++) connections[$2, i-4] = $i
  connections[$2, -1] = "op"
}

END{
  
  nodes["AA"] = ""
  
  for(x in nodes){
    for(y in nodes){
      calc_distance(x, y)
    }
  }

  path_A[0] = "AA"
  path_B[0] = "AA"
  recursive_move("", 0, 0, path_A, path_B, 0, 0, 0, 0, 0, 0)

  print max_sum

}
