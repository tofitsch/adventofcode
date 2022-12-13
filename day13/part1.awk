#!/bin/awk

func nested_split(str, arr){
  if(substr(str, 1, 1) == "[") str = substr(str, 2, length(str) - 2)
  split(str, chars, "")
  ctr_opening = 0
  ctr_closing = 0
  for(c in chars){
    if(chars[c] == "[") ctr_opening++
    if(chars[c] == "]") ctr_closing++
    if(chars[c] == "," && ctr_opening > ctr_closing)
      str = substr(str, 1, c-1) ";" substr(str, c+1, length(str))
  }
  split(str, arr, ",")
  for(a in arr) gsub(/;/, ",", arr[a])
}

func compare(str_a, str_b){
  
  nested_split(str_a, arr_a)
  nested_split(str_b, arr_b)

  print str_a, str_b
  print length(arr_a), length(arr_b)

  return "ordered"

}

BEGIN{RS=""}

{if(compare($1, $2) == "ordered") sum += NR}

END{print sum}
