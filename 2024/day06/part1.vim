	macro to rotate the grid (swap rows with columns)
qa			start of macro @a {
gg				go to start of file
mb				set mark b
:g/^/norm 			for each line {
`b					go to mark b
Gx					visual block select the first column and delete it to "
:pu!				paste it linewise above
o 					insert space to new line
jmb					go one line down and set mark b
				}
:%s/\n//			remove all newline chars
:%s/ //g			replace all spaces with newlines
:g/^/m0			so far this is transpose. This reversion of line order makes it rotation
ggdd				remove empty line at top
q			} end of macro @a

qc			start of macro @c {
:silent!/#\^/norm @a/		rotate the grid if there's a # left of ^
:%s/\v(.|x)\^/^x/		move ^ one leftx mark its previous position with a x
@c
q			} end of macro @c
@c			call @c

:%s/x/x/g		put ech x on a new line
:let c=1		init counter (1 for ^ which is not counted when counting x)
:g/x/let c+=1		increment c for each x
ggcG			delete all conent
=c		insert c
