#!/bin/awk

func abs(a) {return a < 0 ? -1 * a : a}

BEGIN{FS = "=|,|:" ; Y = 10}

{

  if($4 == Y && map[$2] == ""){print $2" " ; map[$2] = "S" ; ctr++}
  if($8 == Y && map[$6] == ""){print $6" " ; map[$6] = "B" ; ctr++}

  distance = abs($2 - $6) + abs($4 - $8) 

  x = $2
  while(abs($2 - x) + abs($4 - Y) <= distance){
    if(map[x] == ""){
      printf x" "
      map[x] = "#"
      ctr++
    }
    x++
  }

  print ""

  x = $2
  while(abs($2 - x) + abs($4 - Y) <= distance){
    if(map[x] == ""){
      printf x" "
      map[x] = "#"
      ctr++
    }
    x--
  }

}

END {
  for(x=-4; x<=26; x++) printf map[x] == "" ? "." : map[x]
  print ctr
}
