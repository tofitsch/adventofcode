let pos = sort(split(readfile('input.txt')[0], ','), 'N')
let n = len(pos)
let fuel = repeat([0], n)

let bisect_a = pos[0]
let bisect_b = pos[-1]

while bisect_a != bisect_b
  let bisect_c = (bisect_a + bisect_b) / 2
  let fuel_a = 0
  let fuel_b = 0
  let fuel_c = 0
  for p in pos
    let fuel_a += abs(p - bisect_a)
    let fuel_b += abs(p - bisect_b)
    let fuel_c += abs(p - bisect_c)
  endfor
  if fuel_a > fuel_b
    let bisect_a = bisect_c
  else
    let bisect_b = bisect_c
  endif
  echo bisect_a bisect_b
endwhile

echo fuel_a
