#!/bin/awk

BEGIN{FS = "=|,|:" ; max = 4e6}

func abs(a) {return a < 0 ? -1 * a : a}

func encircle(X, Y, R, s){

  x = X + R-1
  y = Y
  
  for(i=0; i<4*(R-1); i++){
    
    is_reached = 0

    for(j in sig_x){
      
      if(j == s) continue

      if(abs(sig_x[j] - x) + abs(sig_y[j] - y) <= sig_reach[j]){
        is_reached = 1
        break
      }

    }

    if(is_reached == 0 && x >= 0 && y >= 0 && x <= max && y <= max){
      print x*max + y
      exit
    }

    if(i <= (R-1)-1){x--; y--}
    else if(i <= 2*(R-1)-1){x--; y++}
    else if(i <= 3*(R-1)-1){x++; y++}
    else if(i <= 4*(R-1)-1){x++; y--}
    
  }

}

{
  sig_x[NR] = $2
  sig_y[NR] = $4
  sig_reach[NR] = abs($2 - $6) + abs($4 - $8) 
}

END {for(s in sig_x) encircle(sig_x[s], sig_y[s], sig_reach[s] + 2, s)}
