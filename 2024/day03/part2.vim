:%s/\n//
				
:%s/don't().\{-}		delete everything between a "don't()"
\zedo()//g
				
:let s=0
				
:%s/mul(\(\d*\),\(\d*\))/	find valid mul() instructions

\1*\2
				
:g/_/				find all lines marked with '_'
norm lD				delete the product expression to "
:let s+="
				
Gdgg				delete all content
i=s				insert s