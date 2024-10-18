#!/bin/bash

input=$(<input.txt)

input=$input${input:0:1}

sum=0

for (( i=1; i<${#input}; i++ )); do

	this=${input:$i:1}
	prev=${input:$i-1:1}

	(( this == prev )) && (( sum += this ))

done

echo $sum
