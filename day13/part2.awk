#!/bin/awk

func type(x){
  if(substr(x, 1, 1) == "[") return "list"
  return "int"
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

func recursive_compare(str_a, str_b,  arr_a, arr_b, return_val, i){
  
  if(type(str_a) == "int" && type(str_b) == "int"){
    if(str_a < str_b) return "ordered"
    if(str_a > str_b) return "unordered"
    return "undecided"
  }

  if(type(str_a) == "int" && type(str_b) == "list") return recursive_compare(to_list(str_a), str_b)
  if(type(str_b) == "int" && type(str_a) == "list") return recursive_compare(str_a, to_list(str_b)) 

  nested_split(str_a, arr_a)
  nested_split(str_b, arr_b)

  return_val = "undecided"

  for(i=1; i<=length(arr_a) && i<=length(arr_b); i++){
    return_val = recursive_compare(arr_a[i], arr_b[i])
    if(return_val != "undecided") break
  }

  if(return_val == "undecided"){
    if(arr_a[i] == "" && arr_b[i] != "") return "ordered"
    if(arr_a[i] != "" && arr_b[i] == "") return "unordered"
  }

  return return_val

}

BEGIN{
  ctr = 0
  packets[ctr] = "[[2]]"
  ctr++
  packets[ctr] = "[[6]]"
}

{
  if($0 == "") next
  ctr++
  packets[ctr] = $0
}

END {
  
  n_swaps = -1

  while(n_swaps != 0){
    n_swaps = 0
    for(i in packets){
      if(i == 0) continue
      if(recursive_compare(packets[i], packets[i-1]) == "ordered"){
        packet = packets[i-1]
        packets[i-1] = packets[i]
        packets[i] = packet
        n_swaps++
      }
    }
  }

  result = 1
  for(i in packets){
    if(packets[i] == "[[2]]" || packets[i] == "[[6]]") result *= i+1
  }

  print result

}
