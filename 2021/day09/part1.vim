set nocp

function! IsLocalMinimum(x, y)
  return (a:x == 0                 || g:mtx[a:y][a:x - 1] > g:mtx[a:y][a:x]) &&
       \ (a:x == len(g:mtx[0]) - 1 || g:mtx[a:y][a:x + 1] > g:mtx[a:y][a:x]) &&
       \ (a:y == 0                 || g:mtx[a:y - 1][a:x] > g:mtx[a:y][a:x]) &&
       \ (a:y == len(g:mtx)    - 1 || g:mtx[a:y + 1][a:x] > g:mtx[a:y][a:x])
endfunction

let sum = 0
let mtx = []

for line in readfile('input.txt') | call add(mtx, split(line, '\zs')) | endfor

for x in range(len(mtx[0]))
  for y in range(len(mtx))
    if IsLocalMinimum(x, y) | let sum += mtx[y][x] + 1 | endif
  endfor
endfor

echo sum
