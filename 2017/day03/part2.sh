#!/bin/bash

input=$(<input.txt)

abs(){

	x=$1

	(( x < 0 )) && (( x *= -1 ))

	echo $x

}

dir=0
len=1
ctr=0
x=0
y=0
i=1

declare -A map
map[0, 0]=1

while (( i<${input} )); do

	(( i++, ctr++))

	case $dir in
		0) (( x++ )) ;;
		1) (( y++ )) ;;
		2) (( x-- )) ;;
		3) (( y-- )) ;;
	esac

	(( ctr == 2 * len )) && (( len++, dir++, ctr=0 )) || (( ctr == len )) && (( dir++ ))

	(( dir %= 4 ))

	sum=0

	for X in $(seq $(( x - 1 )) $(( x + 1 )) ); do
		for Y in $(seq $(( y - 1 )) $(( y + 1 )) ); do

			(( sum += map[$X, $Y] ))

		done
	done

	map[$x, $y]=$sum

	if (( sum > $input )); then

		echo $sum

		break

	fi

done
