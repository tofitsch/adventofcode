set nocp

function! IsLocalMinimum(x, y)
  return (a:x == 0                 || g:mtx[a:y][a:x - 1] > g:mtx[a:y][a:x]) &&
       \ (a:x == len(g:mtx[0]) - 1 || g:mtx[a:y][a:x + 1] > g:mtx[a:y][a:x]) &&
       \ (a:y == 0                 || g:mtx[a:y - 1][a:x] > g:mtx[a:y][a:x]) &&
       \ (a:y == len(g:mtx)    - 1 || g:mtx[a:y + 1][a:x] > g:mtx[a:y][a:x])
endfunction

function! IntervalsOverlap(a, b)
  return (a:a[0] <= a:b[0] && a:a[1] >= a:b[1]) ||
       \ (a:a[0] >= a:b[0] && a:a[1] <= a:b[1]) ||
       \ (a:a[0] >= a:b[0] && a:a[0] <= a:b[1]) ||
       \ (a:a[1] >= a:b[0] && a:a[1] <= a:b[1])
endfunction

let mtx = []
let basinslices = []

for line in readfile('example.txt')

  call add(mtx, split(line, '\zs'))
  call add(basinslices, [])

  let end = -1

  while 1

    let beg = match(line, '[0-8]\+', end + 1)
    let end = beg + len(matchstr(line, '[0-8]\+', end + 1)) - 1

    if end < 0 | break | endif

    call add(basinslices[len(basinslices) - 1], [beg, end])

  endwhile

endfor

echo basinslices

for x in range(len(mtx[0]))
  for y in range(len(mtx))

    if IsLocalMinimum(x, y)

      let basin = []

      for slice in basinslices[y]
        if slice[0] <= x && slice[1] >= x

          call add(basin, [slice])

          let added_slice = 1
          let Y = y

          while added_slice > 0
            
            call add(basin, [])

            if Y >= len(basinslices) - 1 | break | endif

            let added_slice = 0

            for s in basin[-2]
              for S in basinslices[Y + 1]
               if IntervalsOverlap(s, S)
                 call add(basin[-1], S)
                 let added_slice = 1
               endif
              endfor
            endfor

            let Y += 1

          endwhile

        endif
      endfor

      echo y basin

    endif

  endfor
endfor
