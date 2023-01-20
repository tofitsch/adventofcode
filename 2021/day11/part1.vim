let mtx = []
let ctr = 0

function! Flash(x, y)
  if g:mtx[a:y][a:x] == 10
    let g:ctr += 1
    for l:X in range(a:x - 1, a:x + 1)
      for l:Y in range(a:y - 1, a:y + 1)
        if l:X < 0 || l:Y < 0 || l:X >= len(g:mtx[0]) || l:Y >= len(g:mtx)
          continue
        endif
        let g:mtx[l:Y][l:X] += 1 
        call Flash(l:X, l:Y)
      endfor
    endfor
  else
  endif
endfunction

for line in readfile('input.txt')
  let row = split(line, '\zs')
  call add(mtx, row)
endfor

for step in range(100)
  for y in range(len(mtx))
    for x in range(len(mtx[0]))
      let mtx[y][x] += 1
      call Flash(x, y)
    endfor
  endfor
  for y in range(len(mtx))
    for x in range(len(mtx[0]))
      if mtx[y][x] > 9 | let mtx[y][x] = 0 | endif
    endfor
  endfor
endfor

echo ctr
