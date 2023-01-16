#!/bin/awk

func plot(){

  for(y=min[2]; y<=max[2]; y++){
    for(x=min[1]; x<=max[1]; x++){
      printf map[y, x] == "" ? "." : map[y,x]
    }
    print ""
  }

}

BEGIN {FS=" -> "}

{
  for(i=1; i<=NF; i++){
    
    for(j=1; j<=2; j++) prev_node[j] = node[j]

    split($i, node, ",")

    for(j in node){

      if(max[j] == "" || max[j] < node[j]) max[j] = node[j]
      if(min[j] == "" || min[j] > node[j]) min[j] = node[j]

      beg[j] = node[j] > prev_node[j] ? prev_node[j] : node[j];
      end[j] = node[j] < prev_node[j] ? prev_node[j] : node[j];

    }

    if(i == 1) continue

    for(x=beg[1]; x<=end[1]; x++){
      for(y=beg[2]; y<=end[2]; y++){
        map[y, x] = "#"
      }
    }

  }
}

END {

  min[2] = 0

  source_x = 500
  source_y = min[y]

  map[source_y, source_x] = "+"

  stop = 0

  while(stop != 1){
    
    ctr++

    grain_x = source_x
    grain_y = source_y

    at_rest = 0

    while(at_rest != 1){
      
      map[grain_y, grain_x] = ""

      if(map[grain_y + 1, grain_x] == "") grain_y++
      else if(map[grain_y + 1, grain_x - 1] == "") {grain_y++ ; grain_x--}
      else if(map[grain_y + 1, grain_x + 1] == "") {grain_y++ ; grain_x++}
      else at_rest = 1

      map[grain_y, grain_x] = "o"

      if(grain_y > max[2]) {stop = 1 ; break}

    }

#    plot()
    
  }

  print ctr - 1

}
