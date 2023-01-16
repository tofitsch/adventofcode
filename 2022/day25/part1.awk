#!/bin/awk

BEGIN {FS = ""}

func abs(a) {return a < 0 ? -1 * a : a}

{
  for(x=NF; x>0; x--){
    if($x == "-") digit = -1
    else if($x == "=") digit = -2
    else digit = $x
    sum += digit * 5**(NF - x)
  }
}

END {

  while(2*5**p_max < sum) p_max++

  for(p=p_max; p>=0; p--){
    closest = "X"
    for(i=-2; i<=2; i++){
      dist = abs(result + i*5**p - sum)
      if(closest == "X" || dist < closest){
        best_i = i
        closest = dist
      }
    }
    result += best_i*5**p
    if(best_i == -1) result_str = result_str "-"
    else if(best_i == -2) result_str = result_str "="
    else result_str = result_str best_i
  }

  print result_str

}

