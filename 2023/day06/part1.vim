:%s/ \+/ /g						put each field into a separate line
?DjD2GP							delete all distances and put them in front of the times in the same lines
:v/\d/d							delete all lines without numbers in them
:g/./norm 							for each line:
"ade									delete the dist string into register a
wde									delete the time string into register "
ifloat2nr((-pa+sqrt(pa*pa-4*"apa))/-2)		write flaot2nr((-time+sqrt(time*time-4*dist))/-2)
0y$Pi-F+s-							copy that line with + changed to - and put a - inbetween the two terms
0C="							evaluate the expression
								end of "for each line"
:%s/\n/*							put each term in one line with * inbetween
$x								remove the last *
0C="							evaluate the expression
0D								delete the line containing the result
:!echo "							print what was just deleted
:q!								quit
