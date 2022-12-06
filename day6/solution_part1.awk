#!/bin/awk

BEGIN {FS=""}

{ 
  
  for(i=1; i<=NF; i++){
    
    if(i>3 && \
       $i != $(i-1) && $i != $(i-2) && $i != $(i-3) && \
       $(i-1) != $(i-2) && $(i-1) != $(i-3) && \
       $(i-2) != $(i-3) \
      ){

      print i, $i
      break

    }

  }

}
