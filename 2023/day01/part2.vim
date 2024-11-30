:%s/\(one\|two\|three\|four\|five\|six\|seven\|eight\|nine\)/X\1X\1		mark the first occurance of any of the digits with X before and after it
:%s/.*\zs\(one\|two\|three\|four\|five\|six\|seven\|eight\|nine\)/\1X\1X	mark the last occurance of any of the digits with X before and after
:%s/XoneX/1/g									replace marked number strings with digits
:%s/XtwoX/2/g
:%s/XthreeX/3/g
:%s/XfourX/4/g
:%s/XfiveX/5/g
:%s/XsixX/6/g
:%s/XsevenX/7/g
:%s/XeightX/8/g
:%s/XnineX/9/g								all lines from the next one on are identical to part1
:%s/[a-z]//g									remove all letters, only leaving the digits
:g/./norm $ma0ld`a								delete all but the first and last char in a line
:g/^.$/norm ylp								in each line with just 1 char 'c', copy it to make it 'cc'
:%s/\n/+									replace each newline with a +, yielding one line with all numbers added
$x										remove the last +
0D										delete the line, putting it into register "
i="									evaluate the content of register " with the expression register =
