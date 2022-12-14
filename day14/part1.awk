#!/bin/awk

func plot(){

  for(y=min[2]; y<=max[2]; y++){
    for(x=min[1]; x<=max[1]; x++){
      if(map[y, x] != "#") map[y, x] = "."
      printf map[y, x]
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

  plot()

}
