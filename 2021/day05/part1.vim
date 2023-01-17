let ctr = 0
let map = {}

for line in readfile('input.txt')

  let path = split(line, ',\| -> ')

  if path[0] != path[2] && path[1] != path[3] | continue | endif

  let x_range = sort([path[0], path[2]], 'N')
  let y_range = sort([path[1], path[3]], 'N')

  for x in range(x_range[0], x_range[1])
    for y in range(y_range[0], y_range[1])
      let key = x . ',' . y
      if has_key(map, key) | let ctr += 1 | endif
      let map[key] = 1
    endfor
  endfor

endfor

echo ctr

"echo ''
"for x in range(10)
"  for y in range(10)
"    let key = y . ',' . x
"    if has_key(map, key) | echon 1 | else | echon 0 | endif
"  endfor
"  echo ''
"endfor
