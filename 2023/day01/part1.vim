:%s/[a-z]//g			remove all letters, only leaving the digits
:g/./norm $ma0ld`a	delete all but the first and last char in a line
:g/^.$/norm ylp		in each line with just 1 char 'c', copy it to make it 'cc'
:%s/\n/+				replace each newline with a +, yielding one line with all numbers added
$x						remove the last +
0D						"delete the line, putting it into register "
i="				evaluate the content of register " with the expression register =
