#!/bin/bash
#
# RPS = 1 2 3
#     1 d w l
#     2 l d w
#     3 w l d

sed -e 's/A/1/' -e 's/B/2/' -e 's/C/3/' \
    -e 's/X/1/' -e 's/Y/2/' -e 's/Z/3/' \
    input.txt \
| awk '{sum += $2}
       $1 == $2 {sum += 3}
       ($1 == 1 && $2 == 2) ||
       ($1 == 2 && $2 == 3) ||
       ($1 == 3 && $2 == 1) {sum += 6}
       END {print sum}'
