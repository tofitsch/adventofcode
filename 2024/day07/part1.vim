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
:s/ /0/g
@a				call @a


:g/b/norm 		for each line with a binary number {
:s/0/+/g
:s/1/*/g
xx


Go:			add a new line with : to the end of the file

:%s/^/ /g

:g/:/norm 		for each line with : {
y$				yank it into "
0j				start of line 1 down
				block select
/:
0k				but only 1st column until line above
p				paste the line


:g!/\v(\+|\*)/norm lD

o			start of macro @b { constructs formula from numbers and operators in line
f x				find and delete next space (breaks recursion if not found)
mc				set mark c
$x				delete + or * from end of line to "
`c				go to mark c
P				paste the yanked + or *
i)				add a ) after the number
F:a(			add a ( after :
@b				tail recursion
"bdd			} end of macro @b

:g/^/norm 		for each line {
f x				delete first space
@b				call @b


:g/^/norm 		for each line {
f:				go to :
lD				delete formula to "
a="


:%s/\n//
:%s/\s\s/ 

:g!/\v (\d*):\1 /d

:%s/:.*\n/+
$x			delete trailing +
0D			delete expression into "
i="