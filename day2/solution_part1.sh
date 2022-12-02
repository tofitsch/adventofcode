#!/bin/bash

sed -e 's/A/1/' -e 's/B/2/' -e 's/C/3/' \
    -e 's/X/1/' -e 's/Y/2/' -e 's/Z/3/' \
    input.txt \
| awk '$1-$2 == -1 || $1-$2 == 2 {sum += 6 + $2}
       $1-$2 == -2 || $1-$2 == 1 {sum += 0 + $2}
       $1-$2 == 0                {sum += 3 + $2}
       END {print sum}'
