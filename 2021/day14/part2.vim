let rules = {}
let pairs = {}
let updates = {}

let alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

for x in alphabet
  for y in alphabet
    let pairs[x.y] = 0
    let updates[x.y] = 0
  endfor
endfor

for line in readfile('input.txt')
  let tokens = split(line, ' -> ')
  if len(tokens) == 1
    let str = tokens[0]
    for i in range(len(str) - 1)
      let pairs[str[i:i+1]] += 1
    endfor
  elseif len(tokens) == 2
    let c = [tokens[0][:0], tokens[1], tokens[0][1:]]
    let rules[c[0].c[2]] = [c[0].c[1], c[1].c[2]]
  endif
endfor

for step in range(40)

  for key in keys(rules)
    let updates[key] -= pairs[key]
    let updates[rules[key][0]] += pairs[key]
    let updates[rules[key][1]] += pairs[key]
  endfor

  for x in alphabet
    for y in alphabet
      let pairs[x.y] += updates[x.y]
      let updates[x.y] = 0
    endfor
  endfor

endfor

let abundance = {}
for x in alphabet | let abundance[x] = 0 | endfor

let abundance[str[:0]] += 1
let abundance[str[-1:]] += 1

for x in alphabet
  for y in alphabet
    let abundance[x] += pairs[x.y]
    let abundance[y] += pairs[x.y]
  endfor
endfor

let abundance_lst = []
for x in alphabet
  if abundance[x] != 0
    call add(abundance_lst, abundance[x] / 2)
  endif
endfor

call sort(abundance_lst, 'N')

echo abundance_lst[-1] - abundance_lst[0]
