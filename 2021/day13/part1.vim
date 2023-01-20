let mtx = []

let x_max = 0
let y_max = 0

for line in readfile('input.txt')
  let xy = split(line, ',') 
  if len(xy) == 2
    if x_max < str2nr(xy[0]) | let x_max = str2nr(xy[0]) | endif 
    if y_max < str2nr(xy[1]) | let y_max = str2nr(xy[1]) | endif 
  endif
endfor

let row = range(x_max + 1)
let mtx = map(row, 'repeat(y_max + 1, 0)')

let mtx = []
for x in range(y_max + 1)
  let row = []
  for y in range(x_max + 1) | call add(row, 0) | endfor
  call add(mtx, row)
endfor

for line in readfile('input.txt')
  let xy = split(line, ',') 
  if len(xy) == 2
    let mtx[xy[1]][xy[0]] = 1
  else
    let fold = split(line, ' \|=') 
    if len(fold) == 4
      if fold[2] == 'x'
        for x in range(fold[3], x_max)
          for y in range(y_max + 1)
            if mtx[y][x] == 1
              let mtx[y][x] = 0
              let mtx[y][fold[3] - (x - fold[3])] = 1
            endif
          endfor
        endfor
        let x_max = fold[3]
      else
        for y in range(fold[3], y_max)
          for x in range(x_max + 1)
            if mtx[y][x] == 1
              let mtx[y][x] = 0
              let mtx[fold[3] - (y - fold[3])][x] = 1
            endif
          endfor
        endfor
        let y_max = fold[3]
      endif
      break
    endif
  endif
endfor

let ctr = 0

for x in range(x_max + 1)
  for y in range(y_max + 1)
    let ctr += mtx[y][x]
  endfor
endfor

echo ctr
