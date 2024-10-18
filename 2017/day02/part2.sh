#!/bin/bash

sum=0

while IFS= read -r line; do

        IFS=$'\t '

     	for a in $line; do

     		for b in $line; do

			(( a == b )) && continue

			(( a % b == 0 )) && (( sum +=  a / b ))

		done

	done

	unset IFS

done < "input.txt"

echo $sum
