function UseMap()

  if has_key(g:map, g:key)
    if g:map[g:key] == 1 | let g:ctr += 1 | endif
    let g:map[g:key] += 1
  else
    let g:map[g:key] = 1
  endif

endfunction

let ctr = 0
let map = {}

for line in readfile('example.txt')
  
  let path = split(line, ',\| -> ')

  if path[0] != path[2] && path[1] != path[3]

    let dist = abs(path[0] - path[2])

    for i in range(dist + 1)
      
      let key  = (path[0] < path[2] ? path[0] + i : path[0] - i) . ','
      let key .= (path[1] < path[3] ? path[1] + i : path[1] - i)

      call UseMap()

    endfor

  else

    let x_range = sort([path[0], path[2]], 'N')
    let y_range = sort([path[1], path[3]], 'N')

    for x in range(x_range[0], x_range[1])
      for y in range(y_range[0], y_range[1])

        let key = x . ',' . y

        call UseMap()

      endfor
    endfor

  endif

endfor

echo ctr

"XXX
echo ''
for x in range(10)
  for y in range(10)
    let key = y . ',' . x
    if has_key(map, key) | echon 'X' | else | echon '.' | endif
  endfor
  echo ''
endfor
