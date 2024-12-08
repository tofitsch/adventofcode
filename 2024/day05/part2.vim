	Idea: 
	Make a regex from each rule that matches two numbers if they are in the wrong order.
	Make a regex replacement for each of them that then swaps these numbers.
	Apply these replacements multiple times until no more swaps are done.

:%s/\v^(.*,.*)$/,\1,
:%s/,/,,/g

:%s/\v(\d*)\|(\d*)/		replace all rules {
\\v,(\2X*)(,.*,)(\1X*),			with a regex for their inversion (X is transformed mark)
\/,\\3\\2\\1x,\/			that swaps match group 1 with 3 and marks it with an x
/

/^$
"ddgg				delete all regex lines into "d

qc				start of macro @c {
:%s/x/X/g
gg					go to top
"dP					paste regex lines from "d
:g/v/norm 				for each line with a regex {
dd						delete the line into "
:%s/"

@c					tail recursion
q				} end of macro c
@c				apply @c

dd				delete the first (empty) line

:%s/,,/,/g
:g!/X/d
:%s/X//g

qb				start of macro @b {
$dF,					delete last number
0df,					delete first number
@b					tail recursion
q				} end of macro @b
	
:g/,/norm @b
:%s/,\n/+/g

$x				remove trailing +
0D				delete expression into "
i="