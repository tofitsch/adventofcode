#!/bin/bash

arr=($(<input.txt))

n=${#arr[@]}

mem=""

n_steps=0
in_loop=0

while true; do

	if [[ $mem =~ "${arr[@]};" ]]; then

		if (( in_loop == 0 )); then

			in_loop=1
			offset=$n_steps
			mem=""

		else
			break
		fi

	fi

	mem+="${arr[@]};"
	
	i_max=0
	
	for (( i=1; i<$n; i++ )); do

		(( arr[i] > arr[i_max] )) && i_max=$i

	done
	
	val=${arr[i_max]}
	
	arr[i_max]=0
	
	i=$i_max
	
	while (( val > 0 )); do
	
		(( i++ ))
		(( i %= n ))
		(( val-- ))
		(( arr[i]++ ))
	
	done

	(( n_steps++ ))

done

(( n_steps -= offset ))

echo $n_steps
