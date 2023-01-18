let pos = sort(split(readfile('input.txt')[0], ','), 'N')
let n = len(pos)
let fuel = repeat([0], n)

for i in range(n)
  for j in range(n)
    let fuel[i] += abs(pos[i] - pos[j])
  endfor
endfor

echo sort(fuel, 'N')[0]
