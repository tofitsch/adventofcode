let rules = []

for line in readfile('input.txt')
  let tokens = split(line, ' -> ')
  if len(tokens) == 1
    let str = tokens[0]
  elseif len(tokens) == 2
    let c = [tokens[0][:0], substitute(tokens[1], '.', '\L&', ''), tokens[0][1:]]
    cal add(rules, [c[0].'\zs\ze'.c[2], c[1]])
  endif
endfor

for step in range(10)
  
  for rule in rules
    let str = substitute(str, rule[0], rule[1], 'g')
  endfor

  let str = substitute(str, '.*', '\U&', 'g')

endfor

let abundance = []

for char in uniq(sort(split(str, '\zs')))
  call add(abundance, count(str, char))
endfor

call sort(abundance, 'N')

echo abundance[-1] - abundance[0]
