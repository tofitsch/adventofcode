function UseMap(key)

  if has_key(g:map, a:key)
    if g:map[a:key] == 1 | let g:ctr += 1 | endif
    let g:map[a:key] += 1
  else
    let g:map[a:key] = 1
  endif

endfunction

let ctr = 0
let map = {}

for line in readfile('input.txt')
  
  let path = split(line, ',\| -> ')

  if path[0] != path[2] && path[1] != path[3]

    let dist = abs(path[0] - path[2])

    for i in range(dist + 1)
      
      let key  = (str2nr(path[0]) < str2nr(path[2]) ? path[0] + i : path[0] - i) . ','
      let key .= (str2nr(path[1]) < str2nr(path[3]) ? path[1] + i : path[1] - i)

      call UseMap(key)

    endfor

  else

    let x_range = sort([path[0], path[2]], 'N')
    let y_range = sort([path[1], path[3]], 'N')

    for x in range(x_range[0], x_range[1])
      for y in range(y_range[0], y_range[1])

        let key = x . ',' . y

        call UseMap(key)

      endfor
    endfor

  endif

endfor

echo ctr
