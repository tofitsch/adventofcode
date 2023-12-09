#!/bin/bash

macro=""

while IFS= read -r line; do
  macro+=$(echo "$line" | cut -f1 -d$'\t') # read each line up til tab and concatenate
done < $1

echo $macro > $1c

vim -c "set cmdheight=2 | norm $macro" $2 2>/dev/null
