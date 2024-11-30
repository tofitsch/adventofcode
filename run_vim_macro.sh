#!/bin/bash

# copy target file (input.txt) to tmp.txt
cp $2 tmp.txt

macro=""

while IFS= read -r line; do
  # read each line up til tab and concatenate
  macro+=$(echo "$line" | cut -f1 -d$'\t')
done < $1

macro+="ZZ" > $1c #write and quit

# copy macro to .vimc file
echo $macro > $1c

# execute macro on tmp.txt
vim.basic -u NONE tmp.txt -s $1c 2>/dev/null

cat tmp.txt

rm tmp.txt
