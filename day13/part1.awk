#!/bin/awk

func type(x){
  if(substr(x, 1, 1) == "[") return "list"
  else return "int"
}

func to_list(x){return "[" x "]"}

func content(x){return substr(x, 2, length(x) - 2)}

func nested_split(str, arr){
  if(type(str) == "list") str = content(str) 
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

func recursive_compare(str_a, str_b){
  
  nested_split(str_a, arr_a)
  nested_split(str_b, arr_b)

  print str_a, str_b
  print length(arr_a), length(arr_b)

  return "ordered"

}

BEGIN{RS=""}

{if(recursive_compare($1, $2) == "ordered") sum += NR}

END{print sum}
