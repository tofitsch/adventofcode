#!/bin/bash

echo "solutions: true | computed"

for day in day*; do

  for part in 1 2; do

    true_solution=""

    if test -f "$day/solution.txt"; then
      true_solution=$(sed -n "${part}p" < "$day/solution.txt")
    fi

    if [ "$true_solution" == "" ]; then
      echo "[WARNING]: No true solution provided for $day part$part"
      continue
    fi

    computed_solution=$(awk -f "$day/part$part.awk" "$day/input.txt")

    echo "$day part$part: $true_solution | $computed_solution" 

    if [ "$computed_solution" != "$true_solution" ]; then
      echo "[ERROR]: Mismatch of true and computed solution"
      return 1
    fi

  done

done


