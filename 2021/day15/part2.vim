let map = []
let inf = 9999999

for line in readfile('input.txt')
  let row = []
  for i in range(len(line))
    call add(row, line[i:i])
  endfor
  call add(map, row)
endfor

let y_max = len(map)
let x_max = len(map[0])

for i in range(4)
  for y in range(y_max)
    let row = []
    for x in range(x_max)
      let val = map[y][x] + i + 1
      call add(row, (val > 9 ? val % 10 + 1 : val))
    endfor
    let map[y] += row
  endfor
endfor

let x_max = len(map[0])

let sector = []

for i in range(4)
  call add(sector, deepcopy(map))
  for x in range(x_max)
    for y in range(y_max)
      let val = map[y][x] + i + 1
      let sector[i][y][x] = (val > 9 ? val % 10 + 1 : val)
    endfor
  endfor
endfor

for i in range(4)
  let map += sector[i]
endfor

let y_max = len(map)

let dijkstra = deepcopy(map)
let frontier = [[0, 0]]

for x in range(x_max)
  for y in range(y_max)
    let dijkstra[y][x] = inf
  endfor
endfor

let dijkstra[0][0] = 0

while dijkstra[y_max - 1][x_max - 1] == inf

  let min_dijkstra = inf

  for coord in frontier
    if dijkstra[coord[0]][coord[1]] < min_dijkstra
      let min_dijkstra = dijkstra[coord[0]][coord[1]]
      let Y = coord[0]
      let X = coord[1]
    endif
  endfor

  unlet frontier[index(frontier, [Y, X])]

  for dx in [-1, 0, 1]
    for dy in [-1, 0, 1]
      if X + dx >= x_max || X + dx < 0 || Y + dy >= y_max || Y + dy < 0 || (dx != 0 && dy != 0) | continue | endif
      let new_dijkstra = dijkstra[Y][X] + map[Y + dy][X + dx]
      if dijkstra[Y + dy][X + dx] > new_dijkstra
        if dijkstra[Y + dy][X + dx] == inf | call add(frontier, [Y + dy, X + dx]) | endif
        let dijkstra[Y + dy][X + dx] = new_dijkstra
      endif
    endfor
  endfor

endwhile

echo dijkstra[y_max - 1][x_max - 1]
