#!/bin/awk

BEGIN {FS=""}

$1 == "[" {

  for(i=2; i<NF; i+=4){
    
    if($i == " ") continue

    col = (i-2)/4  +1

    beg[col] = 1

    end[col]++

    val[col, end[col]] = $i

  }

}

length($0) == 0 {FS=" "}

$1 == "move" {

  print "-> " $2 " " $4 " " $6

  for(i=0; i<$2; i++){

    beg[$6]--

    val[$6, beg[$6]] = val[$4, beg[$4]]

    beg[$4]++

  }

  for(x=1; x<=9; x++){
    printf x " " beg[x] "\t" val[x, beg[x]] "\t"
    for(y=beg[x]; y<=end[x]; y++){
      printf val[x, y]
    }
    print ""
  }

}

#$2 == "6" {exit}

END {for(i=1; i<=9; i++) printf val[i, beg[i]]; print ""}
