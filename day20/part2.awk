#!/bin/awk

{
  val[NR] = $1 * 811589153
  prv[NR] = NR - 1
  nxt[NR] = NR + 1
  if($1 == 0) zero_id = NR
}

func abs(a) {return a < 0 ? -1 * a : a}

func move(id, by){
  
  if(val[id] == 0) return 0
 
  nxt[prv[id]] = nxt[id]
  prv[nxt[id]] = prv[id]

  pos = id

  end = by > 0 ? by: abs(by) + 1

  for(i=0; i<end % (NR - 1); i++) pos = by > 0 ? nxt[pos] : prv[pos]

  prv[id] = pos
  nxt[id] = nxt[pos]

  prv[nxt[pos]] = id
  nxt[pos] = id

}

END {

  nxt[NR] = 1 
  prv[1] = NR 

  for(j=0; j<10; j++)
    for(n=1; n<=NR; n++)
      move(n, val[n])

  pos = zero_id

  for(i=1; i<=3000; i++){
    pos = nxt[pos]
    if(i == 1000 || i == 2000 || i == 3000) sum += val[pos]
  }

  print sum

}
