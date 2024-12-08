O			start of macro @x {// applies + to first 2 numbers
0f 				go to first space
"ddf 				delete first number into "d
"edf 				delete second number into "e 
i =d+e
				normal mode
k				1 up
"xdd			} end of macro @x

O			start of macro @y {// applies * to first 2 numbers
0f 				go to first space
"ddf 				delete first number into "d
"edf 				delete second number into "e 
i =d*e
				normal mode
k				1 up
"ydd			} end of macro @y

O			start of macro @z {// concatenates first 2 numbers
02f x				delete 2nd space
k				1 up
"zdd			} end of macro @z

O			start of macro @a { //copy line with binary number and increment it by one
0lf0				check if the number contains a 0, break if not
yyp				copy number
				increment by 1
@a				tail recursion
"add			} end of macro @a

:g/^/norm 		for each line {
yyp				copy it
:s/\d//g
:s/: /0b
:s/ /00/g
@a				call @a


:%s/\v(\d\d)/		for each pair of bits {
,\1/g

:g/^,/norm 		for each line starting with comma {
:s/,//g

:%s/,00/@x/g
:%s/,01/@y/g
:%s/,10/@z/g

:g/^0b.*11/d
:%s/^0b//

Go:			add a new line with : to the end of the file
:%s/^/ /g

:g/:/norm 		for each line with : {
$a 				add space at end
0y$				yank line into "
0j				start of line 1 down
				block select
/:
0k				but only 1st column until line above
p				paste the line


:g!/[xyz]/norm lD

:%s/@/ @/

:g/:/norm 		for each line with a : {
f@				go to the macros @
D				delete them into "
:norm "


:%s/: /:/
:%s/\s\s//
:%s/\n//
:%s/\s\s/ 

:g!/\v (\d*):\1 /d

:%s/:.*\n/		get all results (before:) in the remaining lines
+
$x			delete trailing +
0D			delete expression into "
i="