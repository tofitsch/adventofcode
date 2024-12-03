O				start of macro @b { # makes copies of line, each time with one nr removed
mc					set marker c
yyp					copy line
`cf l					go to next number after marker (f breaks recursion)
j					in line below
dw					delete that number
k					go back to original position
@b					tail recursion
"bdd				} end of macro @b
				
:g/./norm 			for each line {
Oj					add empty line above
@b					apply @b

				
:g/^$/norm 			for each empty line {
2j0dw					remove first number which @b leaves behind

				
:%s/ $//
:%s/\v (\d*)/-\1,\1/g
:%s/,\d*$/,/
				
o				start of macro @a {
dt,					cut expression (e.g. "7-6") to "
i="
2l					go to next expression
@a					tail recursion
"add				} end of macro @a
				
:g/./norm @a
:%s/^/,
:%s/\v,(\d)/,+\1/g
				
:g/\(				for each unsafe line, i.e. with (
-.*+\|					either first a -, then a +
+.*-\|					or first a +, then a -
\d\d\|					or a more than 1 digit number
[4-9]\|					a digit > 3
0					or 0
\)				)
/d
				
:let l=0
:g/^,\n../			for each line that's just a ',' but has a non-empty line afterwards {
let l+=1				increment l

				
Gdgg				delete all content
i=l				insert value of l