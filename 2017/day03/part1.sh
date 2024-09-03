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

done

x_abs=$(abs $x)
y_abs=$(abs $y)

echo $(( x_abs + y_abs ))
