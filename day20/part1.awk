#!/bin/awk

{
  val[NR] = $1
  prv[NR] = NR - 1
  nxt[NR] = NR + 1
  if($1 == 0) zero_id = NR
}

func debug() {
  pos = 1
  for(i=1; i<=NR; i++){
    printf val[pos]" "
#    printf pos" "
    pos = nxt[pos]
  }
  print ""
}

func abs(a) {return a < 0 ? -1 * a : a}

func move(id, by){
  
  if(val[id] == 0) return 0
 
  nxt[prv[id]] = nxt[id]
  prv[nxt[id]] = prv[id]

  pos = id

  for(i=0; i<abs(by); i++)
    pos = by > 0 ? nxt[pos] : prv[pos]

  if(by < 0) pos = prv[pos]

  #print val[id], id, pos

  prv[id] = pos
  nxt[id] = nxt[pos]

  prv[nxt[pos]] = id
  nxt[pos] = id

}

END {

  nxt[NR] = 1 
  prv[1] = NR 

  for(n=1; n<=NR; n++){
    move(n, val[n])
#    debug()
  }

  pos = zero_id

  for(i=1; i<=3000; i++){
    pos = nxt[pos]
    if(i == 1000 || i == 2000 || i == 3000) sum += val[pos]
  }

  debug()
  print sum

}
