#!/bin/bash

n_valid=0

while IFS= read -r line; do
	
	(( n_valid++ ))

	words=($line)

	for (( i=0; i<${#words[@]}; i++ )); do
		
		other_words=($line)
		unset other_words[$i]

		[[ " ${other_words[@]} " =~ " ${words[$i]} " ]] && (( n_valid--)) &&  break

	done

done < "input.txt"

echo $n_valid
