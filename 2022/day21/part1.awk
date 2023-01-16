#!/bin/awk

BEGIN {FS=":? "}

{for(i=2; i<5; i++) op[$1, i-2] = $i}

func eval(str){
  if(op[str, 1] == "") return op[str, 0]
  if(op[str, 1] == "+") return eval(op[str, 0]) + eval(op[str, 2])
  if(op[str, 1] == "-") return eval(op[str, 0]) - eval(op[str, 2])
  if(op[str, 1] == "*") return eval(op[str, 0]) * eval(op[str, 2])
  if(op[str, 1] == "/") return eval(op[str, 0]) / eval(op[str, 2])
}

END {print eval("root")}
