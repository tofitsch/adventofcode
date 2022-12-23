#!/bin/awk

func recursive_move(move, ctr_A, ctr_B, path_A, path_B,  c, path_length, i, duplicate, move_arr){

  if(move != ""){
    split(move, move_arr, ":")

    if(move_arr[1] == "A") path_A[ctr_A] = move_arr[2]
    if(move_arr[1] == "B") path_B[ctr_B] = move_arr[2]
  }

  path_length_A = evaluate(path_A, ctr_A, length_and_sum_A)
  path_length_B = evaluate(path_B, ctr_B, length_and_sum_B)

  path_length_A = length_and_sum_A[0]
  path_length_B = length_and_sum_B[0]

  sum_A = length_and_sum_A[1]
  sum_B = length_and_sum_B[1]

  if(sum_A + sum_B > max_sum) max_sum = sum_A + sum_B

  if(path_length_A < n_moves){
    for(c in non_zero_valves){
      duplicate = 0
      for(i=0; i<=ctr_A; i++) if(path_A[i] == non_zero_valves[c]) duplicate = 1
      for(i=0; i<=ctr_B; i++) if(path_B[i] == non_zero_valves[c]) duplicate = 1
      if(duplicate == 0) recursive_move("A:"non_zero_valves[c], ctr_A+1, ctr_B, path_A, path_B)
    }
  }

  if(path_length_B < n_moves){
    for(c in non_zero_valves){
      duplicate = 0
      for(i=0; i<=ctr_A; i++) if(path_A[i] == non_zero_valves[c]) duplicate = 1
      for(i=0; i<=ctr_B; i++) if(path_B[i] == non_zero_valves[c]) duplicate = 1
      if(duplicate == 0) recursive_move("B:"non_zero_valves[c], ctr_A, ctr_B+1, path_A, path_B)
    }
  }

}

func evaluate(path, ctr, length_and_sum,  inst_rate, dt, i){
  length_and_sum[0] = 0
  length_and_sum[1] = 0
  inst_rate = 0
  for(i=1 ; i<=ctr; i++){
    dt = distance[path[i], path[i-1]] + 1
    length_and_sum[0] += dt
    length_and_sum[1] += inst_rate * dt
    inst_rate += rates[path[i]]
    #printf path[i] ":" length_and_sum[0] ":" inst_rate " "
  }
  length_and_sum[1] += inst_rate * (n_moves - length_and_sum[0])
  #print length_and_sum[1]
  return length_and_sum[0]
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

func get_path_length(path){
  sum = 0
  for(i=1; i<n_non_zero_valves; i++) sum += distance[path[i], path[i+1]]
  return sum
}


BEGIN{FS = "Valve | has.*=|; tunnel.*valves? |, "; n_moves = 26; inf = 1e5}

{
  rates[$2] = $3
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

 # path[0] = "AA"
 # path[1] = "DD"
 # path[2] = "BB"
 # path[3] = "JJ"
 # path[4] = "HH"
 # path[5] = "EE"
 # path[6] = "CC"
 # evaluate(path, 6)
 # exit

  path_A[0] = "AA"
  path_B[0] = "AA"
  recursive_move("", 0, 0, path_A, path_B)

  print max_sum

}
