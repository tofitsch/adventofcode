#!/bin/awk

BEGIN {FS=""}

{for(x=1; x<=NF; x++) val[x, NR] = $x}

END { 

  # XXX
  for(y=1; y<=NR; y++){
    for(x=1; x<=NF; x++){
      vis[x, y] = 0
    }
  }

  # scan top -> bot
  for(x=1; x<=NF; x++){
    max = -1
    for(y=1; y<=NR; y++){
      if(val[x, y] > max){
        vis[x, y] = 1
        max = val[x, y]
      }
    }
  }

  # scan bot -> top
  for(x=1; x<=NF; x++){
    max = -1
    for(y=NR; y>=1; y--){
      if(val[x, y] > max){
        vis[x, y] = 1
        max = val[x, y]
      }
    }
  }

  # scan left -> right
  for(y=1; y<=NR; y++){
    max = -1
    for(x=1; x<=NF; x++){
      if(val[x, y] > max){
        vis[x, y] = 1
        max = val[x, y]
      }
    }
  }

  # scan right -> left
  for(y=1; y<=NR; y++){
    max = -1
    for(x=NF; x>=1; x--){
      if(val[x, y] > max){
        vis[x, y] = 1
        max = val[x, y]
      }
    }
  }
  
  # count visible
  for(x=1; x<=NF; x++){
    for(y=1; y<=NR; y++){
      #printf vis[x, y]
      if(vis[x, y] == 1) n_visible++
    }
    #print ""
  }

  print n_visible

}
