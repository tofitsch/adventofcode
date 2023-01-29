let map = []
let inf = 9999999

for line in readfile('input.txt')
  let row = []
  for i in range(len(line))
    call add(row, line[i:i])
  endfor
  call add(map, row)
endfor

let x_max = len(map)
let y_max = len(map[0])

let dijkstra = deepcopy(map)
let visited = deepcopy(map)

for x in range(x_max)
  for y in range(y_max)
    let dijkstra[y][x] = inf
    let visited[y][x] = 0
  endfor
endfor

let dijkstra[0][0] = 0

while dijkstra[y_max - 1][x_max - 1] == inf

  let min_dijkstra = inf

  for x in range(x_max)
    for y in range(y_max)
      if visited[y][x] == 1 | continue | endif
      if dijkstra[y][x] < min_dijkstra
        let min_dijkstra = dijkstra[y][x]
        let X = x
        let Y = y
      endif
    endfor
  endfor

  let visited[Y][X] = 1

  for dx in [-1, 0, 1]
    for dy in [-1, 0, 1]
      if X + dx >= x_max || X + dx < 0 || Y + dy >= y_max || Y + dy < 0 || (dx != 0 && dy != 0) | continue | endif
      let new_dijkstra = dijkstra[Y][X] + map[Y + dy][X + dx]
      if dijkstra[Y + dy][X + dx] > new_dijkstra | let dijkstra[Y + dy][X + dx] = new_dijkstra | endif
    endfor
  endfor

endwhile

echo dijkstra[y_max - 1][x_max - 1]
