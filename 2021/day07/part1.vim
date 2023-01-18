let pos = sort(split(readfile('example.txt')[0], ','), 'N')

let fuel = [0, 0, 0]
let bisect = [pos[0], '', pos[-1]]

while abs(bisect[0] - bisect[2]) > 1

  let bisect[1] = (bisect[0] + bisect[2]) / 2

  for i in range(3)
    let fuel[i] = 0
    for p in pos | let fuel[i] += abs(p - bisect[i]) | endfor
  endfor

  let b = fuel[0] > fuel[2] ? 0 : 2
  let bisect[b] = bisect[1]

  echo bisect[0] bisect[1] bisect[2]

endwhile

echo fuel[0] > fuel[1] ? fuel[1] : fuel[0]
