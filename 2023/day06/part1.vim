:%s/ \+/ 
?D
:v/\d/d
:g/./norm 							for each line:
"ade									delete the dist string into register a
wde									delete the time string into register "
ifloat2nr((-pa+sqrt(pa*pa-4*"apa))/-2)		write flaot2nr((-time+sqrt(time*time-4*dist))/-2)
0y$Pi-F+s-							copy that line with + changed to - and put a - inbetween the two terms
0C="

:%s/\n/*
$x								remove the last *
0C="
0D								delete the line containing the result
:!echo "
:q!