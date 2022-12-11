#!/bin/awk

BEGIN {ctr = 0}

$0 ~ "items" {for(i=3; i<=NF; i++) items[ctr] = items[ctr] $i}
$0 ~ "new"   {operation[ctr] = $5; operand[ctr] = $6}
$0 ~ "divi"  {divisor[ctr] = $4}
$0 ~ "true"  {cond_true[ctr] = $6}
$0 ~ "false" {cond_false[ctr] = $6; ctr++}

END {
  
#  for(monkey in items) printf "Monkey "monkey": "items[monkey]"\n"
#  print " "

  for(monkey in items){

   split(items[monkey], stack, ",")

   items[monkey] = ","

   for(i in stack){
     for(d in divisor) items[monkey] = items[monkey] ";" stack[i] % divisor[d]
     if(i < length(stack)) items[monkey] = items[monkey] ","
   }

  }

  for(monkey in items) printf "Monkey "monkey": "items[monkey]"\n"
  print " "

  for(round=0; round<1e4; round++){

    for(monkey in items){

      split(items[monkey], stack, ",")

      items[monkey] = ""

      for(i in stack){
        
        if(stack[i] == "") continue

        throws[monkey]++

        split(stack[i], mods, ";")

#        print stack[i]

        stack[i] = ""

        for(d in mods){

          if(mods[d] == "") continue

          if(operand[monkey] == "old") mods[d] *= mods[d]
          else{
            if(operation[monkey] == "*") mods[d] *= operand[monkey]
            else mods[d] += operand[monkey]
          }

          mods[d] %= divisor[d - 2]

#          print d, mods[d]

          stack[i] = stack[i] ";" mods[d]

        }
        
        target = (mods[monkey + 2] / divisor[monkey] ~ "\\.") ? cond_false[monkey] : cond_true[monkey]

        items[target] = items[target] "," stack[i]

      }

      for(monkey in items) printf "Monkey "monkey": "items[monkey]"\n"
      print ""

    }

    print "ROUND"

  }

  for(monkey in throws) printf "Monkey "monkey": "throws[monkey]"\n"
  print " "

  asort(throws)

  print throws[ctr] * throws[ctr - 1]

}
