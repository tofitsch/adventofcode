#!/bin/awk

BEGIN {FS = ""}

{
  val = 0
  for(x=NF; x>0; x--){
    if($x == "-") digit = -1
    else if($x == "=") digit = -2
    else digit = $x
    val += digit * 5**(NF - x)
  }
  sum += val
}

END {print sum}

