qa			start of macro @a { // rotates the grid
gg				go to start of file
mb				set mark b
:g/^/norm 			for each line {
`b					go to mark b
Gx					visual block select the first column and delete it to "
:pu!
o 					insert space to new line
jmb					go one line down and set mark b

:%s/\n//
:%s/ /
:g/^/m0
ggdd				remove empty line at top
q			} end of macro @a

qc			start of macro @c {
:silent!/#\^/norm @a/
:%s/\v(.|x)\^/^x/
@c				tail recursion
q			} end of macro @c
@c			call @c

:%s/x/x
:let c=1
:g/x/let c+=1
ggcG			delete all conent
=c