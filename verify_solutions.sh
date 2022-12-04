#!/bin/bash

echo "solutions: true | computed"

for day in day*; do

  for part in 1 2; do

    computed_solution=$(awk -f "$day/solution_part$part.awk" "$day/input.txt")
    true_solution=$(sed -n "${part}p" < "$day/solution.txt")

    echo "$day part$part: $true_solution | $computed_solution" 

    if [ "$computed_solution" != "$true_solution" ]; then
      echo "[ERROR]: Mismatch of true and computed solution"
      return 1
    fi

  done

done


