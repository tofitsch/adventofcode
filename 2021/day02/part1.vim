let x = 0
let y = 0

for line in readfile('input.txt')

  let field = split(line)  

  if field[0] == 'up'      | let y -= field[1] | endif
  if field[0] == 'down'    | let y += field[1] | endif
  if field[0] == 'forward' | let x += field[1] | endif

endfor

echo x*y
