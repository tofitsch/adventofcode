:%s/[^0-9]//g						remove all chars that are not digits
"ade							delete the dist string into register a
kde							delete the time string into register "
ifloat2nr((-pa+sqrt(pa*pa-4*"apa))/-2)	write flaot2nr((-time+sqrt(time*time-4*dist))/-2)
yyp:s/+/-						copy that line with + changed to -
DkPa-							put the line with - infront of that with + and add a - inbetween
0C="						evaluate the expression
0D							delete the line containing the result
:!echo "						print what was just deleted
:q!							quit
