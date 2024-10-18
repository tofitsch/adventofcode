#!/bin/bash

input=$(<input.txt)

n=256

pos=0
skp=0

IFS=','
set -- $input
unset IFS

eval arr=({0..$((n-1))})

for len in $@; do

	span=()

	for (( i=pos; i<pos+len; i++ )); do

		span[$(( i - pos ))]=${arr[$(( i % n ))]}

	done

	for (( i=0; i<$len; i++ )); do

		arr[$(( (pos + len - i - 1) % n ))]=${span[$i]}

	done

	(( pos += len + skp))
	(( skp++ ))

done

echo $(( arr[0] * arr[1] ))
