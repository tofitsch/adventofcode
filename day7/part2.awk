#!/bin/awk

$0 ~ "^\\$ cd" {
  if($3 == "..") cursor = substr(cursor, 0, match(cursor, "\\/[a-z]*$") - 1)
  else cursor = ($3 == "/") ? "/" : cursor"/"$3
}

$0 ~ "^[0-9]" {
  sub_cursor = cursor
  while(sub_cursor != ""){
    dir_size[sub_cursor] += $1
    sub_cursor = substr(sub_cursor, 0, match(sub_cursor, "\\/[a-z]*$") - 1)
  }
}

END {
  for(dir in dir_size){
    unused_space = 7e7 - dir_size["/"]
    if(dir_size[dir] > 3e7 - unused_space) sufficiently_large_dirs[dir] = dir_size[dir]
  }
  asort(sufficiently_large_dirs)
  print sufficiently_large_dirs[1]
}
