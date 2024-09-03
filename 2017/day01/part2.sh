#!/bin/bash

input=$(<input.txt)

input_twice=$input$input

len_input=${#input}

offset=$(( len_input / 2 ))

sum=0

for (( i=0; i<${#input}; i++ )); do

	a=${input:$i:1}
	b=${input_twice:$i+$offset:1}

	(( a == b )) && (( sum += a ))

done

echo $sum
