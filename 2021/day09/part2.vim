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
let basinareas = []
let basinslices = []

for line in readfile('input.txt')

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

for y in range(len(mtx))
  for x in range(len(mtx[0]))
    
    if IsLocalMinimum(x, y)
      
      call add(basinareas, 0)

      let basin = []

      for slice in basinslices[y]
        if slice[0] <= x && slice[1] >= x

          call add(basin, [slice])
          let basinareas[-1] += slice[1] - slice[0] + 1

          let go_on = 1
          let dir_y = 1
          let Y = y

          while go_on == 1
            
            let go_on = 0

            call add(basin, [])

            for s in basin[-2]
              if Y + dir_y > len(basinslices) - 1 || Y + dir_y < 0 | break | endif
              for S in basinslices[Y + dir_y]
               if IntervalsOverlap(s, S)
                 call add(basin[-1], S)
                 let basinareas[-1] += S[1] - S[0] + 1
                 let go_on = 1
               endif
              endfor
            endfor

            let Y += dir_y

            if dir_y == 1
              if go_on == 0 || Y == len(basinslices) - 1 || Y == 0
                let go_on = 1
                let dir_y = -1
                let Y = y
                call filter(basin, 'len(v:val) > 0')
                call reverse(basin)
              endif
            endif

          endwhile

        endif
      endfor

    endif

  endfor
endfor

call sort(basinareas, 'N')

echo  basinareas[-3] * basinareas[-2] * basinareas[-1]
