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

    {
      IFS=$'\n' read -r -d '' time_for_solution;
      IFS=$'\n' read -r -d '' computed_solution;
    } < <((printf '\0%s\0' "$(time (awk -f "$day/part$part.awk" "$day/input.txt"))" 1>&2) 2>&1)

    timing=$(echo $time_for_solution | awk '{print $4" + "$6}')

    if [ "$day part$part" == "day10 part2" ]; then

      md5=$(echo $computed_solution| md5sum)

      if [ "$md5" == "6fffc8e4a2a7b1b31cb7a9b6de5f7db0  -" ]; then
        computed_solution="EHZFZHCZ"
      else
        computed_solution="wrong md5 sum"
      fi

    fi

    echo "$day part$part : $timing : $computed_solution" 

    if [ "$computed_solution" != "$true_solution" ]; then
      echo "[ERROR]: Mismatch of true and computed solution:"
      echo "true: $true_solution"
      echo "computed: $computed_solution"
      return 1
    fi

  done

done


