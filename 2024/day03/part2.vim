:%s/\n//			remove newline chars
				
:%s/don't().\{-}		delete everything between a "don't()"
\ze\(do()\|\n\)//g		and the next "do()" or endline
				
:let s=0			init sum
				
:%s/mul(\(\d\+\),\(\d\+\))/	find valid mul() instructions
_				set it onto a new line marked with '_' which doesn't exist in the input
\1*\2/g			extract the numbers and construct a product expression from them
				
:g/_/				find all lines marked with '_'
norm lD				delete the product expression to "
:let s+="		add it to the sum
				
Gdgg				delete all content
i=s				insert s
