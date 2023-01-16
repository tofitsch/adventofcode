#!/bin/awk

func recursive_move(move, ctr, path,  c, path_length, i, duplicate){

  path[ctr] = move

  path_length = 0
  for(i=0; i<=ctr; i++) 

  path_length = evaluate(path, ctr)

  if(path_length < n_moves){
    for(c in non_zero_valves){
      duplicate = 0
      for(i=0; i<=ctr; i++) if(path[i] == non_zero_valves[c]) duplicate = 1
      if(duplicate == 0) recursive_move(non_zero_valves[c], ctr+1, path)
      
    }
  }

}

func evaluate(path, ctr,  path_length, inst_rate, sum, dt, i){
  path_length = 0
  inst_rate = 0
  sum = 0
  for(i=1 ; i<=ctr; i++){
    dt = distance[path[i], path[i-1]] + 1
    path_length += dt
    sum += inst_rate * dt
    inst_rate += rates[path[i]]
    #printf path[i] ":" path_length ":" inst_rate " "
  }
  sum += inst_rate * (n_moves - path_length)
  #print sum
  if(sum > max_sum){
    delete best_path
    for(i=0 ; i<=ctr; i++) best_path[i] = path[i]
    max_sum = sum
    best_path_inst_rate = inst_rate
    best_path_path_length = path_length
  }
  return path_length
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


BEGIN{FS = "Valve | has.*=|; tunnel.*valves? |, "; n_moves = 30; inf = 1e5}

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

  path[0] = "AA"
  recursive_move("AA", 0, path)

#  for(i in best_path) printf best_path[i] " "
#  print best_path_inst_rate" : " best_path_path_length

  print max_sum

}
