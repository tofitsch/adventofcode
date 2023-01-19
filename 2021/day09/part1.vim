set nocp

let sum = 0
let mtx = []

for line in readfile('input.txt') |  call add(mtx, split(line, '\zs')) | endfor

for x in range(len(mtx[0]))
  for y in range(len(mtx))
    if (x == 0               || mtx[y][x - 1] > mtx[y][x]) &&
     \ (x == len(mtx[0]) - 1 || mtx[y][x + 1] > mtx[y][x]) &&
     \ (y == 0               || mtx[y - 1][x] > mtx[y][x]) &&
     \ (y == len(mtx)    - 1 || mtx[y + 1][x] > mtx[y][x])
      let sum += mtx[y][x] + 1
    endif
  endfor
endfor

echo sum
