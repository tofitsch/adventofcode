#!/bin/bash

echo "year  day  part  : usertime + systime  : solution"
echo "-------------------------------------------------"

#for year in 2021 2022; do # 2022 disabled for now because some solutions are very slow
for year in 2021; do
  for day in $year/day*; do
  
    for part in 1 2; do
  
      true_solution=""
  
      if test -f "$day/solution.txt"; then
        true_solution=$(sed -n "${part}p" < "$day/solution.txt")
      fi
  
      if [ "$true_solution" == "" ]; then
        echo "[WARNING]: No true solution provided for $day part$part"
        continue
      fi

      if [ "$year" == "2022" ]; then
        {
          ifs=$'\n' read -r -d '' time_for_solution;
          ifs=$'\n' read -r -d '' computed_solution;
        } < <((printf '\0%s\0' "$(time (awk -f "$day/part$part.awk" "$day/input.txt"))" 1>&2) 2>&1)
        timing=$(echo $time_for_solution | awk '{print $4" + "$6}')
      else
        # there must be a better way of doing this...
        # but getting both timing and output for a vimscript is not easy...
        cd $day

        output=$(((echo "X" ; time (vim --cmd ":so part$part.vim | quit")) 1>&2) 2>&1)

        # horribly contrived way of stripping escape sequences:
        # a wonder that this worked consistently so far
        echo $output > tmp
        if [ "$USER" == "runner" ]; then #because of different warnings on git CI than locally...
          computed_solution="$(awk 'BEGIN{FS=""}; {for(i=NF-43; i>94; i--) printf $i}' tmp | rev)"
          t_u=$(echo $output | cut -d' ' -f20)
          t_s=$(echo $output | cut -d' ' -f22)
        else
          computed_solution=$(awk 'BEGIN{FS=""}; {for(i=NF-79; i>44; i--) printf $i}' tmp | rev)
          t_u=$(echo $output | cut -d' ' -f15)
          t_s=$(echo $output | cut -d' ' -f17)
        fi
        rm tmp

        timing=$(echo $t_u $t_s | awk '{print $1" + "$2}')

        cd ../..
      fi
  
  
      if [ "$day part$part" == "2022/day10 part2" ]; then
  
        md5=$(echo $computed_solution| md5sum)
  
        if [ "$md5" == "6fffc8e4a2a7b1b31cb7a9b6de5f7db0  -" ]; then
          computed_solution="EHZFZHCZ"
        else
          computed_solution="wrong md5 sum"
        fi
  
      fi
  
      echo $year `basename $day` "part$part : $timing : $computed_solution" 
  
      if [ "$computed_solution" != "$true_solution" ]; then
        echo "[ERROR]: Mismatch of true and computed solution:"
        echo "true: $true_solution"
        echo "computed: $computed_solution"
        return 1
      fi
  
    done
  
  done
done
