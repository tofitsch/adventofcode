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
:g/./let l+=1
				
Gdgg				delete all content
i=l				insert value of l