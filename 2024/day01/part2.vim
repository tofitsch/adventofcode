:let s=0	init sum
O		start macro @a {
mb			set marker b
"cyiw			yank number into "c
:g/ c$/		for all lines with "c as last token {
let s+=c			add "c to s
			}
`bj			go to line below marker
@a			tail recursion
0"aD		}
@a		call macro
dgg		delete all content
i=s		insert value of s
