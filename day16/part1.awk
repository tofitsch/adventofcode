#!/bin/awk

func recursive_move(node, history, ctr,  c){
  
#  print node, ctr
  
  if(ctr == 5) evaluate_history(history, ctr)
  else{
  
    history[ctr] = node

    for(c=-1; c<n_connections[node]; c++){
      if(c == -1 && can_open(history, ctr) != 1) continue
      connection = node == "open" ? connections[history[ctr-1], c] : connections[node, c]
      recursive_move(connection, history, ctr+1)
    }

    #recursive_move("open", history, ctr+1)
    #if(can_open(history, ctr) == 1) recursive_move("open", history, ctr+1)

    #recursive_move(connections[node, 0], history, ctr+1)

  }

  return

}

func can_open(history, ctr,  h){

  if(history[ctr] == "open") return 2

  for(h=1; h<ctr; h++){
    if(history[h-1] == history[ctr] && history[h] == "open") return 3
  }

  return 1

}

func evaluate_history(history, ctr,  inst_rate, is_open, output){
  
  inst_rate = 0
  output = 0

  for(h=0; h<ctr; h++){
   
    printf history[h]" "

    if(h==0) continue #XXX

    output += inst_rate
    
    if(history[h] == "open" && is_open[history[h-1]] != 1){

      inst_rate += rate[history[h-1]]
      is_open[history[h-1]] = 1

    }
    
  }

  if(output > max_output) max_output = output

  print output

}


BEGIN{FS="Valve | has.*=|; tunnel.*valves? |, "}

{
  rate[$2] = $3
  n_connections[$2] = NF-3
  n_connections["open"] = 1
  for(i=4; i<=NF; i++) connections[$2, i-4] = $i
  connections[$2, -1] = "open"
}

END{

  history[0] = "AA"
  recursive_move("AA", history, 0)

  print max_output

}
