#!/bin/bash

arr=($(<input.txt))

n=${#arr[@]}

mem=""

n_steps=0

while true; do

	[[ $mem =~ "${arr[@]};" ]] && break

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

echo $n_steps
