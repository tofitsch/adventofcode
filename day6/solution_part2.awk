#!/bin/awk

BEGIN {window_size = 14}

{

  for(i=1; i<=length($0); i++){
   
    split(substr($0, i, window_size), window, "")

    delete counts;

    for(x in window){

      counts[window[x]]++

      for(y in window){
        
        if(counts[window[y]] > 1) break

        if(x == window_size && y == window_size){
          print i - 1 + window_size
          exit
        }

      }

    }

  }

}
