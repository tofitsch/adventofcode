	Idea: 
	Make a regex from each rule that matches two numbers if they are in the wrong order.
	Make a regex replacement for each of them that then swaps these numbers.
	Apply these replacements multiple times until no more swaps are done.

:%s/\v^(.*,.*)$/,\1,		place a comma at the start and end of each line with a comma
:%s/,/,,/g			double up every comma

:%s/\v(\d*)\|(\d*)/		replace all rules {
\\v,(\2X*)(,.*,)(\1X*),			with a regex for their inversion (X is transformed mark)
\/,\\3\\2\\1x,\/			that swaps match group 1 with 3 and marks it with an x
/				}

/^$				go to empty line
"ddgg				delete all regex lines into "d

qc				start of macro @c {
:%s/x/X/g				replace all x and transform it to X; break recursion if none found
gg					go to top
"dP					paste regex lines from "d
:g/v/norm 				for each line with a regex {
dd						delete the line into "
:%s/"				apply the regex replacement
					}
@c					tail recursion
q				} end of macro c
@c				apply @c

dd				delete the first (empty) line

:%s/,,/,/g			change double to single comma
:g!/X/d			remove all lines without X
:%s/X//g			remove all X

qb				start of macro @b {
$dF,					delete last number
0df,					delete first number
@b					tail recursion
q				} end of macro @b
	
:g/,/norm @b			apply macro @b to each line
:%s/,\n/+/g			replace newlines (and trailing ,) with +

$x				remove trailing +
0D				delete expression into "
i="			evaluate expression and insert result
