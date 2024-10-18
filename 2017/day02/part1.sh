#!/bin/bash

sum=0

while IFS= read -r line; do

	min="100000"
	max=-100000

        IFS=$'\t '

     	for num in $line; do

		(( num < min )) && min=$num
		(( num > max )) && max=$num

	done

	unset IFS

	(( sum += max - min ))

done < "input.txt"

echo $sum
