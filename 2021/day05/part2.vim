let ctr = 0
let map = {}

for line in readfile('example.txt')
  
  let path = split(line, ',\| -> ')

  let x_range = sort([path[0], path[2]], 'N')
  let y_range = sort([path[1], path[3]], 'N')

  if path[0] != path[2] && path[1] != path[3]

    let dist = x_range[1] - x_range[0]

    for i in range(dist)

      let key = (x_range[0] + i) . ',' . (y_range[0] + i)
"      echo key

      if has_key(map, key)
        if map[key] == 1 | let ctr += 1 | endif
        let map[key] += 1
      else
        let map[key] = 1
      endif

    endfor

  else

    for x in range(x_range[0], x_range[1])
      for y in range(y_range[0], y_range[1])

        let key = x . ',' . y

        if has_key(map, key)
          if map[key] == 1 | let ctr += 1 | endif
          let map[key] += 1
        else
          let map[key] = 1
        endif

      endfor
    endfor

  endif

endfor

echo ctr

echo ''
for x in range(10)
  for y in range(10)
    let key = y . ',' . x
    if has_key(map, key) | echon 'X' | else | echon ' ' | endif
  endfor
  echo ''
endfor
