:g/\v(1[3-9]|[2-9]\d) red/d
:g/\v(1[4-9]|[2-9]\d) green/d
:g/\v(1[5-9]|[2-9]\d) blue/d
:%s/Game /
:%s/:.*\n/+
$x					remove the last +
0D					delete the line, putting it into register "
i="
kD					delete the line containing the result
:!echo "
:q!