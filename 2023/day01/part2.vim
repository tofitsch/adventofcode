:%s/\(one\|two\|three\|four\|five\|six\|seven\|eight\|nine\)/X\1X\1
:%s/.*\zs\(one\|two\|three\|four\|five\|six\|seven\|eight\|nine\)/\1X\1X
:%s/XoneX/1/g
:%s/XtwoX/2/g
:%s/XthreeX/3/g
:%s/XfourX/4/g
:%s/XfiveX/5/g
:%s/XsixX/6/g
:%s/XsevenX/7/g
:%s/XeightX/8/g
:%s/XnineX/9/g
:%s/[a-z]//g
:g/./norm $ma0ld`a
:g/^.$/norm ylp
:%s/\n/+
$x										remove the last +
0D										delete the line, putting it into register "
i="
kD										delete the line containing the result
:!echo "
:q!