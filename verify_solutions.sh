#!/bin/bash

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

    if [ "$day part$part" == "day10 part2" ]; then

      md5=$(awk -f "$day/part$part.awk" "$day/input.txt" | md5sum)

      if [ "$md5" == "93a99521d352462fbc3a857fed6f4c94  -" ]; then
        computed_solution="EHZFZHCZ"
      else
        computed_solution="wrong md5 sum"
      fi

    else
      computed_solution=$(awk -f "$day/part$part.awk" "$day/input.txt")
    fi

    echo "$day part$part: $computed_solution" 

    if [ "$computed_solution" != "$true_solution" ]; then
      echo "[ERROR]: Mismatch of true and computed solution:"
      echo "true: $true_solution"
      echo "computed: $computed_solution"
      return 1
    fi

  done

done


