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
:g/./let l+=1			count number of lines
				
Gdgg				delete all content
i=l				insert value of l
