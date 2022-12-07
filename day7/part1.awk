#!/bin/awk

$0 ~ "^\\$ cd" {
  if($3 == "..") cursor = substr(cursor, 0, match(cursor, "\\/[a-z]*$") - 1)
  else cursor = ($3 == "/") ? "/" : cursor"/"$3
}

$0 ~ "^[0-9]" {
  cur = cursor
  while(cur != ""){
    dir_size[cur] += $1
    cur = substr(cur, 0, match(cur, "\\/[a-z]*$") - 1)
  }
}

END {
  for(dir in dir_size){
    if(dir_size[dir] < 1e5){
      sum += dir_size[dir]
    }
  }
  print sum
}
