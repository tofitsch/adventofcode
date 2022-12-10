#!/bin/awk

func parent_dir(dir){return substr(dir, 0, match(dir, "\\/[a-z]*$") - 1)}

$0 ~ "^\\$ cd" {
  if($3 == "..") cursor = parent_dir(cursor)
  else cursor = cursor"/"$3
}

$0 ~ "^[0-9]" {
  sub_cursor = cursor
  while(sub_cursor != ""){
    dir_size[sub_cursor] += $1
    sub_cursor = parent_dir(sub_cursor)
  }
}

END {
  for(dir in dir_size) if(dir_size[dir] < 1e5) sum += dir_size[dir]
  print sum
}
