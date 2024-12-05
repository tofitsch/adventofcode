:%s/\v^(.*,.*)$/,\1,		place a comma at the start and end of each line with a comma
:%s/,/,,/g			double up every comma

:%s/\v(\d*)\|(\d*)/		replace all rules {
\\v,(\2x*)(,.*,)(\1x*),			with a regex for their inversion
\/,\\3\\2\\1x,\/			that swaps match group 1 with 3 and marks it with an x
/				}

/^$				go to empty line
"ddgg				delete all regex lines into "d

qc				start of macro @c {
gg					go to top
"dP					paste regex lines from "d
:g/v/norm 				for each line with a regex {
dd						delete the line into "
:%s/"				apply the regex replacement
					}
q				} end of macro c

25@c				apply @c 25 times

dd				delete the first (empty) line

:%s/,,/,/g			change double to single comma
:g!/x/d			remove all lines without x
:%s/x//g			remove all x

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
