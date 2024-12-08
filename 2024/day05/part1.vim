:%s/\v^(.*,.*)$/,\1,

:%s/\v(\d*)\|(\d*)/		replace all rules {
,\2\\D*\1,				with a regex for their inversion
/

qa				start of macro @a {
gg					go to top
lh					check for empty line to break recursion
dd					delete the line containting the regex
:g/"/d
@a					tail recursion
q				end of macro @a
@a				call @a

dd				delete the first (empty) line

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