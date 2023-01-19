set nocp

let sum = 0 "XXX

let mtx = []
let basinslices = []

for line in readfile('example.txt')

  call add(mtx, split(line, '\zs'))
  call add(basinslices, [])

  let end = -1

  while 1 == 1

    let beg = match(line, '[0-8]\+', end + 1)
    let end = beg + len(matchstr(line, '[0-8]\+', end + 1)) - 1
    if end < 0 | break | endif

    call add(basinslices[len(basinslices) - 1], [beg, end])

  endwhile
endfor

echo basinslices

for x in range(len(mtx[0]))
  for y in range(len(mtx))
    if (x == 0               || mtx[y][x - 1] > mtx[y][x]) &&
     \ (x == len(mtx[0]) - 1 || mtx[y][x + 1] > mtx[y][x]) &&
     \ (y == 0               || mtx[y - 1][x] > mtx[y][x]) &&
     \ (y == len(mtx)    - 1 || mtx[y + 1][x] > mtx[y][x])
      let sum += mtx[y][x] + 1
      for slice in basinslices[y]
        if slice[0] <= x && slice[1] >= x
          echo slice
        endif
      endfor
    endif
  endfor
endfor

echo sum
