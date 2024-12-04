:let c=0	init counter
qa		start recording @a {

:g/\v(			increment c for each line with a MAS/SAM cross...
^M.M.*\n^.A.*\n^S.S
|
^S.M.*\n^.A.*\n^S.M
|
^M.S.*\n^.A.*\n^M.S
|
^S.S.*\n^.A.*\n^M.M
)/let c+=1

:%s/^.//		delete the first column

@a			tail recursion

q		end of macro @a

@a		call @a

dgg		delete all content
i=c		insert c



