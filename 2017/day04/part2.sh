#!/bin/bash

n_valid=0

is_anagram() {


	(( ${#1} != ${#2} )) && return 0

	b=$2

	for (( k=0; k<${#1}; k++ )); do

		for (( j=0; j<${#b}; j++ )); do

			[[ ${1:$k:1} == ${b:$j:1} ]] && break

		done

		(( j == ${#b} )) && return 0 || b=${b:0:j}${b:j+1}

	done

	(( ${#b} == 0 )) && echo 1 || echo 0

}

while IFS= read -r line; do
	
	is_valid=1

	words=($line)

	for (( i=0; i<${#words[@]}; i++ )); do
		
		other_words=($line)
		unset other_words[$i]

		word=${words[$i]}

		for other in ${other_words[@]}; do

			[[ $(is_anagram $word $other) ]] && is_valid=0 && break

		done

		(( $is_valid == 0 )) && break

	done

	(( n_valid += is_valid ))

done < "input.txt"

echo $n_valid
