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
  unused_space = 7e7 - dir_size["/"]
  for(dir in dir_size){
    if(dir_size[dir] > 3e7 - unused_space) sufficiently_large_dirs[dir] = dir_size[dir]
  }
  asort(sufficiently_large_dirs)
  print sufficiently_large_dirs[1]
}
