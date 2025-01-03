O			start of macro @x {// applies + to first 2 numbers
0f 				go to first space
"ddf 				delete first number into "d
"edf 				delete second number into "e 
i =d+e 		add both numbers and insert the result
				normal mode
k				1 up
"xdd			} end of macro @x

O			start of macro @y {// applies * to first 2 numbers
0f 				go to first space
"ddf 				delete first number into "d
"edf 				delete second number into "e 
i =d*e 		mult both numbers and insert the result
				normal mode
k				1 up
"ydd			} end of macro @y

O			start of macro @z {// concatenates first 2 numbers
02f x				delete 2nd space
k				1 up
"zdd			} end of macro @z

O			start of macro @a { //copy line with binary number and increment it by one
0lf0				check if the number contains a 0, break if not
yyp				copy number
				increment by 1
@a				tail recursion
"add			} end of macro @a

:g/^/norm 		for each line {
yyp				copy it
:s/\d//g 			remove all numbers in the copy
:s/: /0b			add the binary number prefix
:s/ /00/g			replace all remaining spaces with 00 (two bits to represent a trit)
@a				call @a
			}

:%s/\v(\d\d)/		for each pair of bits {
,\1/g			comma-separate it }

:g/^,/norm 		for each line starting with comma {
:s/,//g		remove all commata }

:%s/,00/@x/g		turn all ',00 ' into '@x'
:%s/,01/@y/g		turn all ',01 ' into '@y'
:%s/,10/@z/g		turn all ',10 ' into '@z'

:g/^0b.*11/d		remove all lines with 11 (the unused 2-bit not mapping onto a trit)
:%s/^0b//		remove binary prefix 0b

Go:			add a new line with : to the end of the file
:%s/^/ /g		add space as padding to start of each line

:g/:/norm 		for each line with : {
$a 				add space at end
0y$				yank line into "
0j				start of line 1 down
				block select
/:				until next line with :
0k				but only 1st column until line above
p				paste the line
			}

:g!/[xyz]/norm lD	delete content (except first space) of all lines without xyz

:%s/@/ @/		add one more space as padding before macros

:g/:/norm 		for each line with a : {
f@				go to the macros @
D				delete them into "
:norm "			execute them
			}

:%s/: /:/		remove all spaces after :
:%s/\s\s//		remove all double spaces
:%s/\n//		remove newlines
:%s/\s\s/  /g	turn double spaces into new lines

:g!/\v (\d*):\1 /d	delete all lines where no num:num pair matches

:%s/:.*\n/		get all results (before:) in the remaining lines
+			and make a sum expression
$x			delete trailing +
0D			delete expression into "
i="		insert result of expression
