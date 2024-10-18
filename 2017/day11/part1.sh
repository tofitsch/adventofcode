#!/bin/bash

input=$(<input.txt)

IFS=','

arr=(0 0 0 0 0 0)

for dir in $input; do

	case $dir in
		"n")  (( arr[0]++ )) ;;
		"ne") (( arr[1]++ )) ;;
		"se") (( arr[2]++ )) ;;
		"s")  (( arr[3]++ )) ;;
		"sw") (( arr[4]++ )) ;;
		"nw") (( arr[5]++ )) ;;
	esac

done

unset IFS

changes=1

while (( changes != 0 )) ; do
	
	changes=0

	for i in {0..6}; do
	
		while (( arr[i] > 0 &&  arr[(i + 3) % 6] > 0 )); do
	
			(( arr[i]-- ))
			(( arr[(i + 3) % 6]-- ))
			(( changes++ ))
	
		done
	
		while (( arr[i] > 0 &&  arr[(i + 2) % 6] > 0 )); do
	
			(( arr[i]-- ))
			(( arr[(i + 2) % 6]-- ))
			(( arr[(i + 1) % 6]++ ))
			(( changes++ ))
	
		done
	
	done
	
done

sum=0

for a in ${arr[@]}; do

	(( sum += a ))

done

echo $sum
