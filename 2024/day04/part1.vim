:%s/^/ /		add a space to the start of each line

O		start of macro @a {
"Bx			del char and append it to "b
jll			go diagonally down right
@a			tail recursion
"add		} end of macro @a

:g/./norm 	for each line {
gg0/\S$		go to end of first line with anything but space
a "Bx		append space to "b
@a			call @a
		} done

@:		redo last : command

"bp		paste from "b

:%s/\n//	remove newlines
