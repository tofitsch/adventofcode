#!/bin/bash

in_file="input.txt"

declare -A registers

max=0

update_reg () {

	(( registers["$1"] += $2 )) 

	(( registers["$1"] > max ))  && max=${registers["$1"]}

}

while IFS= read -r line; do

	set -- $line

	val=$3

	[[ "$2" == "dec" ]] && (( val *= -1 ))

	case "$6" in
		">") (( registers["$5"] > $7 )) && update_reg $1 $val ;;
		"<") (( registers["$5"] < $7 )) && (( registers["$1"] += val )) ;;
		">=") (( registers["$5"] >= $7 )) && (( registers["$1"] += val )) ;;
		"<=") (( registers["$5"] <= $7 )) && (( registers["$1"] += val )) ;;
		"==") (( registers["$5"] == $7 )) && (( registers["$1"] += val )) ;;
		"!=") (( registers["$5"] != $7 )) && (( registers["$1"] += val )) ;;
	esac

done < $in_file

echo $max
