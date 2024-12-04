:let c=0	init counter
qa		start recording @a {

			increment c for each line with XMAS (or SAMX) at the start of the line...

			...horizontally
:g/\v^(XMAS|SAMX)/
let c+=1

			...vertically
:g/\v^(X.*\n^M.*\n^A.*\n^S|S.*\n^A.*\n^M.*\n^X)/
let c+=1

			...diagonally down
:g/\v^(X.*\n^.M.*\n^..A.*\n^...S|S.*\n^.A.*\n^..M.*\n^...X)/
let c+=1

			...diagonally up
:g/\v^...(X.*\n^..M.*\n^.A.*\n^S|S.*\n^..A.*\n^.M.*\n^X)/
let c+=1

:%s/^.//		delete the first column

@a			tail recursion

q		end of macro @a

@a		call @a

dgg		delete all content
i=c		insert c



