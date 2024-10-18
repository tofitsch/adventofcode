#!/bin/bash

in_file="input.txt"

declare -A registers

while IFS= read -r line; do

	set -- $line

	val=$3

	[[ "$2" == "dec" ]] && (( val *= -1 ))

	case "$6" in
		">") (( registers["$5"] > $7 )) && (( registers["$1"] += val )) ;;
		"<") (( registers["$5"] < $7 )) && (( registers["$1"] += val )) ;;
		">=") (( registers["$5"] >= $7 )) && (( registers["$1"] += val )) ;;
		"<=") (( registers["$5"] <= $7 )) && (( registers["$1"] += val )) ;;
		"==") (( registers["$5"] == $7 )) && (( registers["$1"] += val )) ;;
		"!=") (( registers["$5"] != $7 )) && (( registers["$1"] += val )) ;;
	esac

done < $in_file

max=0

for key in ${!registers[@]}; do

	reg=${registers["$key"]}

	((  reg > max )) && max=$reg

done

echo $max
