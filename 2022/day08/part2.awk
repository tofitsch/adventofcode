#!/bin/awk

BEGIN {FS=""}

{for(x=1; x<=NF; x++) val[x, NR] = $x}

END { 

  # XXX
  for(y=1; y<=NR; y++){
    for(x=1; x<=NF; x++){
      score[x, y] = 1
    }
  }

  # scan top -> bot
  for(x=1; x<=NF; x++){
    for(y=1; y<=NR; y++){
      score_for_this_dir = 0
      for(y_back=y-1; y_back>=1; y_back--){
        score_for_this_dir++
        if(val[x, y_back] >= val[x, y]) break
      }
      score[x, y] *= score_for_this_dir
    }
  }

  # scan bot -> top
  for(x=1; x<=NF; x++){
    for(y=NR; y>=1; y--){
      score_for_this_dir = 0
      for(y_back=y+1; y_back<=NR; y_back++){
        score_for_this_dir++
        if(val[x, y_back] >= val[x, y]) break
      }
      score[x, y] *= score_for_this_dir
    }
  }

  # scan left -> right
  for(y=1; y<=NR; y++){
    for(x=1; x<=NF; x++){
      score_for_this_dir = 0
      for(x_back=x-1; x_back>=1; x_back--){
        score_for_this_dir++
        if(val[x_back, y] >= val[x, y]) break
      }
      score[x, y] *= score_for_this_dir
    }
  }

  # scan right -> left
  for(y=1; y<=NR; y++){
    for(x=NF; x>=1; x--){
      score_for_this_dir = 0
      for(x_back=x+1; x_back<=NF; x_back++){
        score_for_this_dir++
        if(val[x_back, y] >= val[x, y]) break
      }
      score[x, y] *= score_for_this_dir
    }
  }
  
  # get max score
  max = 0
  for(x=1; x<=NF; x++){
    for(y=1; y<=NR; y++){
#      printf score[x, y]" "
      if(score[x, y] > max) max = score[x, y]
    }
#    print ""
  }

  print max

}
