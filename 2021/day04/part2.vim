function Bingo(z, n)

  let sum = 0

  for y in range(5)
    for x in range(5)
      let val = g:boards[a:z][y][x]
      if val != 'X' | let sum += val | endif
    endfor
  endfor

  echo sum * a:n

  quit!

endfunction

let boards = []
let numbers = []

let z = -1

for line in readfile('input.txt')
  
  if line == ''
    let z += 1
    let y = 0
    call add(boards, [])
  else
    if z < 0
      let numbers = split(line, ',')
    else
      let row = split(line)
      call add(boards[z], [])
      for x in range(5) | call add(boards[z][y], row[x]) | endfor
      let y += 1
    endif
  endif

endfor

let n_boards = z + 1

for n in numbers

  for z in range(n_boards)
    for y in range(5)
      for x in range(5)
        if boards[z][y][x] == n | let boards[z][y][x] = 'X' | endif
      endfor
    endfor
  endfor

  for z in range(n_boards)
    
    if z >= n_boards | let z = n_boards - 1 | endif
    
    let skip = 0

    for y in range(5)
      if join(boards[z][y], '') == 'XXXXX'
        if n_boards > 1
          call remove(boards, z)
          let n_boards -= 1
          let skip = 1
          break
        else
          call Bingo(z, n)
        endif
      endif
    endfor

    if skip | continue | endif 

    for x in range(5)
      let column = []
      for y in range(5) | call add(column, boards[z][y][x]) | endfor
      if join(column, '') == 'XXXXX'
        if n_boards > 1
          call remove(boards, z)
          let n_boards -= 1
          break
        else
          call Bingo(z, n)
        endif
      endif
    endfor

  endfor

endfor
