#!/bin/awk

BEGIN {

  RS = "[^\n]*\n[^\n]*\n[^\n]*\n"
  FS = "\n"

  for (i=1; i<=26; i++) {
    priority[sprintf("%c", i + 96)] = i
    priority[sprintf("%c", i + 64)] = i + 26
  }

}

{ 
  $0 = RT

  triplicate = ""
 
  for (i1=0; i1<=length($1); i1++) {
    c1 = substr($1, i1, 1)
    for (i2=0; i2<=length($2); i2++) {
      c2 = substr($2, i2, 1)
      if (c1 == c2) {
        for (i3=0; i3<=length($3); i3++) {
          c3 = substr($3, i3, 1)
          if (c2 == c3) triplicate = c3
          if (triplicate != "") break
        }
        if (triplicate != "") break
      }
      if (triplicate != "") break
    }
  }

  sum += priority[triplicate]

}

END {print sum}
