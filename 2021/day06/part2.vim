let fish = split(readfile('input.txt')[0], ',')

let aged = repeat([0], 9)
for f in fish | let aged[f] += 1 | endfor

for t in range(256 + 1)

  let new_fish = aged[0]
  let aged[0] = 0

  for i in range(1, 8)
    let aged[i-1] += aged[i]
    let aged[i] = 0
  endfor

  let aged[6] += new_fish
  let aged[8] += new_fish

endfor

let sum = 0
for i in range(8) | let sum += aged[i] | endfor
echo sum

