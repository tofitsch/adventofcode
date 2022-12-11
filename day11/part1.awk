#!/bin/awk

BEGIN {ctr = 0}

$0 ~ "items" {for(i=3; i<=NF; i++) items[ctr] = items[ctr] $i}
$0 ~ "new"   {operation[ctr] = $5; operand[ctr] = $6}
$0 ~ "divi"  {divisor[ctr] = $4}
$0 ~ "true"  {cond_true[ctr] = $6}
$0 ~ "false" {cond_false[ctr] = $6; ctr++}

END {
  
  for(round=0; round<20; round++){

    for(monkey in items){
      
      split(items[monkey], stack, ",")

      items[monkey] = ""

      for(i in stack){
        
        if(stack[i] == "") continue
        
        throws[monkey]++

        if(operand[monkey] == "old") stack[i] *= stack[i]
        else{
          if(operation[monkey] == "*") stack[i] *= operand[monkey]
          else stack[i] += operand[monkey]
        }

        stack[i] = sprintf("%d", stack[i] /= 3)

        target = (stack[i] / divisor[monkey] ~ "\\.") ? cond_false[monkey] : cond_true[monkey]

        items[target] = items[target] "," stack[i]

      }

    }

  }

  asort(throws)

  print throws[ctr] * throws[ctr - 1]

}
