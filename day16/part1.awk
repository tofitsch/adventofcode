#!/bin/awk

func recursive_move(node, history, ctr,  c){
  
  if(ctr == 30) evaluate_history(history, ctr)
  else{
  
    history[ctr] = node

    for(c=0; c<n_connections[node]; c++) recursive_move(connection[node, c], history, ctr+1)

    recursive_move("open", history, ctr+1)

  }

}

func evaluate_history(history, ctr,  inst_rate, is_open, output){
  
  inst_rate = 0
  output = 0

  for(h=1; h<ctr; h++){
   
    printf history[h]" "

    output += inst_rate
    
    if(history[h] == "open" && is_open[history[h-1]] != 1){

      inst_rate += rate[history[h-1]]
      is_open[history[h-1]] = 1

    }
    
  }

  print output

}


BEGIN{FS="Valve | has.*=|; tunnel.*valves? |, "}

{
  rate[$2] = $3
  n_connections[$2] = NF-3
  for(i=4; i<=NF; i++) connection[$2, i-4] = $i
}

END{

  history[0] = "AA"
  for(node in rate) recursive_move("AA", history, 0)

}
