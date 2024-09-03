#!/bin/bash

in_file="input.txt"

names=" "

while IFS= read -r line; do

	words=""

	for (( i=0; i<${#line}; i++ )); do

		[[ ${line:$i:1} =~ ([a-z]| ) ]] && words+=${line:$i:1}

	done

	words=($words)

	for word in $words; do

		[[ $names =~ " $word " ]] && continue || names+="$word "

	done

done < $in_file

names=($names)

get_index_by_name(){

	index=0

	while [[ "$1" != "${names[$index]}" ]]; do
		(( index++ ))
	done

	echo $index
}

while IFS= read -r line; do

	tokens=($line)

	name=${tokens[0]}
	weight=${tokens[1]:1:-1}

	for (( i=0; i<${#line}; i++ )); do

		[[ ${line:$i:1} == ">" ]] && break

	done

	this_children=""

	for token in ${line:$i+2}; do 

		[[ "${token:${#token} - 1:1}" == "," ]] && token=${token:0:${#token} - 1}

		this_children+="$(get_index_by_name $token) "

	done

	index=$(get_index_by_name $name)

	weights[$index]=$weight
	children[$index]=$this_children

done < $in_file

parents=()

for (( i=0; i<${#names[@]}; i++ )); do

	for child in ${children[$i]}; do

		parents[$child]+="$i "

	done

done

for (( i=0; i<${#names[@]}; i++ )); do

	[[ ${parents[$i]} == "" ]] && echo ${names[$i]} && break

done
