wGwD					delete column 2 in vis block
np					paste column 2 to a new split
:sort n
GD					delete content of current buffer in vis block
j					go to initial split
:sort n
$p					pase column 2 again
:%s/\v(\d+)\s+(\d+)\n/abs(\1-\2)+/g
0i=
faD					remove formula, only leaving result