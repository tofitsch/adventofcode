#!/bin/awk

$0 ~ "^\\$ cd" {
  if($3 == "..") cursor = substr(cursor, 0, match(cursor, "\\/[a-z]*$") - 1)
  else cursor = ($3 == "/") ? "/" : cursor"/"$3
#  print "", cursor
}

$0 ~ "^[0-9]" {
  cur = cursor
  while(cur != ""){
    dir_size[cur] += $1
#    print $1, cur, dir_size[cur]
    cur = substr(cur, 0, match(cur, "\\/[a-z]*$") - 1)
  }
}

#$1 == "232123" {exit}

END {
  for(dir in dir_size){
    unused_space = 70000000 - dir_size["/"]
    if(dir_size[dir] > 30000000 - unused_space){
      print dir_size[dir], dir
    }
  }
}
