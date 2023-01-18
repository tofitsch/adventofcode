let ctr = 0

for line in readfile('input.txt')

  let words = split(line, ' | \| ')

  for w in range(10, 13)
    if index([2, 3, 7, 4], len(words[w])) >= 0 | let ctr += 1 |  endif
  endfor

endfor

echo ctr
