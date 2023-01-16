let counts = []
let n_lines = 0

for line in readfile('input.txt')
  
  let pos = 0

  for i in split(line, '\zs')  
    
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
