:%s/[a-z]//g
:g/./norm $ma0ld`a
:g/^.$/norm ylp
:%s/\n/+
$x			remove the last +
0D			delete the line, putting it into register "
i="
kD			delete the line containing the result
:!echo "
:q!