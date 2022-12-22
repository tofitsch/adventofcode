#!/bin/awk

func recursive_move(move, history, ctr,  position, c){
  
  history[ctr] = move 

#  print move, ctr
  
  position = move == "op" ? history[ctr-1] : history[ctr]

  if(ctr == n_moves) evaluate_history(history, ctr)
  else{
    if(move == "xx" || n_opened(history, ctr) == n_valves_with_rate) recursive_move("xx", history, ctr+1)
    else{
      for(c=-1; c<n_connections[position]; c++){
        if(c == -1 && can_open(history, ctr) != 1) continue
        if(c > -1 && is_redundant_loop(history, ctr, connections[position, c]) == 1) continue
        recursive_move(connections[position, c], history, ctr+1)
      }
    }
  }

}

func n_opened(history, ctr,  n, h){
  n=0
  for(h=1; h<=ctr; h++){
    if(history[h] == "op") n++
  }
  return n
}

func is_redundant_loop(history, ctr, next_move,  h){
  for(h=ctr; h>=0; h--){
    if(history[h] == "op") return 2
    if(history[h] == next_move) return 1
  }
}

func can_open(history, ctr,  h){

  if(history[ctr] == "op" || rate[history[ctr]] == 0) return 2

  for(h=1; h<ctr; h++){
    if(history[h-1] == history[ctr] && history[h] == "op") return 3
  }

  return 1

}

func evaluate_history(history, ctr,  inst_rate, is_open, output){
  
  inst_rate = 0
  output = 0

  for(h=0; h<=ctr; h++){
   
    printf history[h]" "

    if(h==0) continue #XXX

    output += inst_rate
    
    if(history[h] == "op" && is_open[history[h-1]] != 1){

      inst_rate += rate[history[h-1]]
      is_open[history[h-1]] = 1

    }
    
  }

  if(output > max_output){
    max_output = output
    for(h=0; h<=ctr; h++) best_history[h] = history[h]
  }

  print output

}


BEGIN{FS = "Valve | has.*=|; tunnel.*valves? |, "; n_moves = 30}

{
  rate[$2] = $3
  if($3 > 0) n_valves_with_rate++
  n_connections[$2] = NF-3
  for(i=4; i<=NF; i++) connections[$2, i-4] = $i
  connections[$2, -1] = "op"
}

END{

  history[0] = "AA"
  recursive_move("AA", history, 0)

  print "best:"
  for(h=0; h<=n_moves; h++) printf best_history[h]" "
  print ""
  print max_output

}
