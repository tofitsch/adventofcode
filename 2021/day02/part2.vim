let x = 0
let y = 0
let aim = 0

for line in readfile('input.txt')

  let field = split(line)  

  if field[0] == 'up'      | let aim -= field[1] | endif
  if field[0] == 'down'    | let aim += field[1] | endif
  if field[0] == 'forward' | let x   += field[1] | let y += field[1] * aim | endif

endfor

echo x*y
