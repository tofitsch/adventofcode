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
Oj				 add empty line above
@b					apply @b
				} done
	
:g/^$/norm 			for each empty line {
2j0dw				 remove first number which @b leaves behind
				} done
				
:%s/ $//			remove trailing spaces
:%s/\v (\d*)/-\1,\1/g		transform e.g. "7 6 4 2 1" to "7-6,6-4,4-2,2-1,1"
:%s/,\d*$/,/			remove trailing singular number (e.g. "1" above)
				
o				start of macro @a {
dt,					cut expression (e.g. "7-6") to "
i="				evaluate it with the expression register
2l					go to next expression
@a					tail recursion
"add				} end of macro @a
				
:g/./norm @a			apply @a to each line
:%s/^/,			add a , to the start of each line
:%s/\v,(\d)/,+\1/g		add a + for each number that does not have a -
				
:g/\(				for each unsafe line, i.e. with (
-.*+\|					either first a -, then a +
+.*-\|					or first a +, then a -
\d\d\|					or a more than 1 digit number
[4-9]\|					a digit > 3
0					or 0
\)				)
/d				delete the line
				
:let l=0			init counter
:g/^,\n../			for each line that's just a ',' but has a non-empty line afterwards {
let l+=1			count number of lines }
						
Gdgg				delete all content
i=l				insert value of l
