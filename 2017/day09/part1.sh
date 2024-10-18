input=$(<input.txt)

nest=0
sum=0
garbage=0
prev=""

for (( i=0; i<${#input}; i++ )); do

	[ "$prev" == "!" ] && continue

	c=${input:$i:1}

	prev=$c

	case $c in 
		"{") (( garbage == 0 )) && (( nest++, sum += nest )) ;;
		"}") (( garbage == 0 )) && (( nest-- )) ;;
		"<") garbage=1 ;;
		">") garbage=0 ;;
	esac

done

echo $sum
