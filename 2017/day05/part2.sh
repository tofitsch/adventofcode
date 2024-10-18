#!/bin/bash

arr=($(<input.txt))

pos=0
n_steps=0

while (( pos >= 0 && pos < ${#arr[@]} )); do

	jump=${arr[pos]}

	(( arr[pos] > 2 )) && (( arr[pos]-- )) || (( arr[pos]++ ))
	(( pos += jump ))
	(( n_steps++ ))

done

echo $n_steps
