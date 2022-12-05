#!/bin/awk

BEGIN {FS=""}

$1 == "[" {

  for(i=2; i<NF; i+=4){
    
    if($i == " ") continue

    col = (i-2)/4 + 1

    beg[col] = 1

    end[col]++

    val[col, end[col]] = $i

  }

}

length($0) == 0 {FS=" "}

$1 == "move" {

  for(i=0; i<$2; i++){

    stack[i] = val[$4, beg[$4]]

    beg[$4]++

  }

  for(i=$2-1; i>=0; i--){

    beg[$6]--

    val[$6, beg[$6]] = stack[i]

  }

}

END {for(i in beg) printf val[i, beg[i]]; print ""}
