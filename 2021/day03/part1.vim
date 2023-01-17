let lines = readfile('input.txt')

let arr = []
for line in lines | let arr += [split(line, '\zs')] | endfor

let counts = []
let n_lines = 0

for line in arr
  
  let pos = 0

  for i in line
    
    if n_lines == 0 | call add(counts, 0) | endif

    let counts[pos] += i

    let pos += 1

  endfor

  let n_lines += 1

endfor

let gamma   = ''
let epsilon = ''

for i in counts
  let gamma   .=   2 * i / n_lines 
  let epsilon .= -(2 * i / n_lines - 1)
endfor

echo str2nr(gamma, 2) * str2nr(epsilon, 2)
