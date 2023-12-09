:g/\v(1[3-9]|[2-9]\d) red/d		delete all lines with > 12 red
:g/\v(1[4-9]|[2-9]\d) green/d		delete all lines with > 13 green
:g/\v(1[5-9]|[2-9]\d) blue/d		delete all lines with > 14 blue
:%s/Game /				remove text before game id
:%s/:.*\n/+				remove text after game id and replace it with +
$x					remove the last +
0D					delete the line, putting it into register "
i="				evaluate the content of register " with the expression register =
kD					delete the line containing the result
:!echo "				print what was just deleted
:q!					quit
