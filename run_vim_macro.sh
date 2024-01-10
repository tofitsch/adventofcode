#!/bin/bash

macro=""

while IFS= read -r line; do
  # read each line up til tab and concatenate
  macro+=$(echo "$line" | cut -f1 -d$'\t')
done < $1

echo $macro > $1c

vim $2 -s $1c 2>/dev/null
