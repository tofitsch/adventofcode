#!/bin/awk

BEGIN {

  FS = ""

  for(i=1; i<=26; i++){
    priority[sprintf("%c", i + 96)] = i
    priority[sprintf("%c", i + 64)] = i + 26
  }

}

{ 
 duplicate = ""

 for (i=1; i<=NF/2; i++) {
   for (j=NF/2+1; j<=NF; j++) {

     if ($i == $j) {
       duplicate = $i
       break
     }

     if (duplicate != "") break

   }
 }

 sum += priority[duplicate]

}

END {print sum}
