#!/bin/awk

func type(x){
  if(substr(x, 1, 1) == "[") return "list"
  else return "int"
}

func to_list(x){return "[" x "]"}

func content(x){
  if(type(x) == "list") return substr(x, 2, length(x) - 2)
  else return x
}

func nested_split(str, arr,  ctr_opening, ctr_closing, chars, c){
  str = content(str) 
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

func recursive_compare(str_a, str_b,  arr_a, arr_b, return_val){
  
  print str_a, str_b
  
  if(type(str_a) == "int" && type(str_b) == "int"){
    if(str_a < str_b) return "ordered"
    if(str_a > str_b) return "unordered"
  }

  if(type(str_a) == "int" && type(str_b) == "list") str_a = to_list(str_a)
  if(type(str_b) == "int" && type(str_a) == "list") str_b = to_list(str_b)

  nested_split(str_a, arr_a)
  nested_split(str_b, arr_b)

  if(length(arr_a) < length(arr_b)) return "ordered"
  if(length(arr_a) > length(arr_b)) return "unordered"

  return_val = "undecided"

  while(return_val == "undecided") return_val = recursive_compare(arr_a[i], arr_b[i])

  return return_val

}

BEGIN{RS=""}

{if(recursive_compare($1, $2) == "ordered") sum += NR}

END{print sum}
