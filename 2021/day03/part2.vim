let lines = readfile('input.txt')

let result = 1

for run in [0, 1]

  let arr = []
  for line in lines | let arr += [split(line, '\zs')] | endfor
  
  let p = 0
  
  while len(arr) > 1
  
    let n_lines = 0
    let counts = []
  
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

    for i in counts | let gamma   .=   2 * i / n_lines | endfor
  
    let gamma   = split(gamma,   '\zs')
    
    let j = 0
  
    for line in arr
      if (run == 0 && line[p] != gamma[p]) || (run == 1 && line[p] == gamma[p])
        call remove(arr, j)
      else
        let j += 1
      endif
    endfor
  
    let p += 1
  
  endwhile

  let result *= str2nr(join(arr[0], ''), 2)
  
endfor

echo result
