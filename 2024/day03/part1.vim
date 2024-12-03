/mul(\d*,\d*)		set search pattern
gg			go to start of file again
:set nowrapscan	disable continue search after end of file to break recursion
			
:let s=0		init sum
			
O			start of macro @a {
n				go to next match
f(l				go to 1st number
"byt,				yank it to "b
f,l				go to 2nd number
yt)				yank it to "
:let s+=b*"		add 1st number * 2nd number to sum
@a				tail recursion
"add			} end of macro @a
@a			call @a
			
Gdgg			delete all content
i=s			insert s
