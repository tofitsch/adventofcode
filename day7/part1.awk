#!/bin/awk

$0 ~ "^\\$ cd" {
  if($3 == "..") cursor = substr(cursor, 0, match(cursor, "\\/[a-z]*$") - 1)
  else cursor = cursor"/"$3
}

$0 ~ "^[0-9]" {
  sub_cursor = cursor
  while(sub_cursor != ""){
    dir_size[sub_cursor] += $1
    sub_cursor = substr(sub_cursor, 0, match(sub_cursor, "\\/[a-z]*$") - 1)
  }
}

END {
  for(dir in dir_size) if(dir_size[dir] < 1e5) sum += dir_size[dir]
  print sum
}
