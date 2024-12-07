#!/bin/bash

# usage:
# ./run_vim_macro.sh part1.vim input.txt
#
# or
#
# ./run_vim_macro.sh part1.vim input.txt -q

# copy target file (input.txt) to tmp.txt
cp $2 tmp.txt

macro=""

while IFS= read -r line; do
  # read each line up til tab and concatenate
  macro+=$(echo "$line" | cut -f1 -d$'\t')
done < $1

# add '-q' at the end of the command to save and quit
if [[ "$3" == "-q" ]]; then
  macro+="ZZ:qa!"
fi

# copy macro to .vimc file
echo $macro > $1c

# execute macro on tmp.txt
vim.basic -u NONE tmp.txt -s $1c 2>/dev/null

cat tmp.txt

rm tmp.txt
