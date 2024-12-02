wGwD					delete column 2 in vis block
np					paste column 2 to a new split
:sort n				sort it numerically
GD					delete content of current buffer in vis block
j					go to initial split
:sort n				sort it numerically
$p					pase column 2 again
:%s/\v(\d+)\s+(\d+)\n/abs(\1-\2)+/g 	regex to add abs - and + to get one formula to sum abs diffs
0i=				evaluate the line in the expression register
faD					remove formula, only leaving result
