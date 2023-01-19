let id = {'(' : 0, ')': 1, '[': 2, ']': 3, '{': 4, '}': 5, '<': 6, '>': 7}
let value = {')': 3, ']': 57, '}': 1197, '>': 25137}

let sum = 0

for line in readfile('input.txt')
  
  let char  = split(line, '\zs')
  let state = repeat([0], len(char))
  let corrupt = 0

  for c in range(1, len(char) - 1)
    
    if corrupt | break | endif

    if id[char[c]] % 2 == 1
      
      let state[c] = 1

      let i = c - 1

      while 1
      
        if state[i] == 0
          if id[char[i]] == id[char[c]] - 1
            let state[i] = 1
            break
          else
            let corrupt = 1
            let sum += value[char[c]]
            break
          endif
        endif

        let i -= 1

        if i < 0
          quit
          let corrupt = 1
          let sum += value[char[c]]
          break
        endif

      endwhile

    endif

  endfor

endfor

echo sum
