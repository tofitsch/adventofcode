#!/bin/awk

func abs(a) {return a < 0 ? -1 * a : a}

BEGIN{FS = "=|,|:" ; Y = 2e6}

{

  if($4 == Y && map[$2] == ""){map[$2] = "S" ; ctr++}
  if($8 == Y && map[$6] == ""){map[$6] = "B"}

  distance = abs($2 - $6) + abs($4 - $8) 

  x = $2
  while(abs($2 - x) + abs($4 - Y) <= distance){
    if(map[x] == ""){
      map[x] = "#"
      ctr++
    }
    x++
  }

  x = $2
  while(abs($2 - x) + abs($4 - Y) <= distance){
    if(map[x] == ""){
      map[x] = "#"
      ctr++
    }
    x--
  }

}

END {print ctr}
