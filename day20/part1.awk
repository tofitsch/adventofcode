#!/bin/awk

{
  val[NR - 1] = $1
  id[NR - 1] = NR - 1
}

func swap(pos_a, pos_b){
 buff = val[pos_b]
 val[pos_b] = val[pos_a]
 val[pos_a] = buff
 buff = id[pos_b]
 id[pos_b] = id[pos_a]
 id[pos_a] = buff
}

END {
  for(i=0; i<NR; i++){
    pos = 0
    while(id[pos] != i) pos++
    if(val[pos] > 0){
      for(j=val[pos]; j>0; j--){
        if(pos+1 >= NR-1){
          swap(pos, pos+1)
          for(p=NR-1; p>0; p--) swap(p, p-1)
          pos = -1
        }
        else
          swap(pos, pos+1)
        pos++
        pos = pos % NR
        if(pos < 0) pos += NR
      }
    }
    else{
      for(j=val[pos]; j<0; j++){
        if(pos-1 <= 0){
          swap(pos, pos-1)
          for(p=0; p<NR-1; p++) swap(p, p+1)
          pos = NR
        }
        else
          swap(pos, pos-1)
        pos--
        pos = pos % NR
        if(pos < 0) pos += NR
      }
    }
  }

#  for(v=0; v<NR; v++) printf val[v]" "
#  print ""

  pos = 0
  while(val[pos] != 0) pos++

  sum += val[(pos + 1000) % NR]
  sum += val[(pos + 2000) % NR]
  sum += val[(pos + 3000) % NR]

  print sum

}
