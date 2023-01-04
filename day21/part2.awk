#!/bin/awk

BEGIN {FS=":? "}

{for(i=2; i<5; i++) op[$1, i-2] = $i}

func sign(a) {return a < 0 ? -1 : 1}

func eval(str, val){
  if(str == "root") return eval(op[str, 0], val) - eval(op[str, 2], val)
  if(str == "humn") return val
  if(op[str, 1] == "") return op[str, 0]
  if(op[str, 1] == "+") return eval(op[str, 0], val) + eval(op[str, 2], val)
  if(op[str, 1] == "-") return eval(op[str, 0], val) - eval(op[str, 2], val)
  if(op[str, 1] == "*") return eval(op[str, 0], val) * eval(op[str, 2], val)
  if(op[str, 1] == "/") return eval(op[str, 0], val) / eval(op[str, 2], val)
}

END {
  
  bisect_a = 0
  bisect_b = 1e14

  while(1 == 1){
    
    bisect_c = int((bisect_a + bisect_b) / 2)

    result_a = eval("root", bisect_a)
    result_b = eval("root", bisect_b)
    result_c = eval("root", bisect_c)

    if(result_c == 0){
      print bisect_c
      exit
    }

    if(sign(result_c) == sign(result_a)) bisect_a = bisect_c
    if(sign(result_c) == sign(result_b)) bisect_b = bisect_c
    
  }

}

