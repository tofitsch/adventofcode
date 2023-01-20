let rules = []

function! ByFirst(a, b)
  return str2nr(a:a[0]) > str2nr(a:b[0])
endfunction

for line in readfile('input.txt')
  let tokens = split(line, ' -> ')
  if len(tokens) == 1
    let str = tokens[0]
  elseif len(tokens) == 2
    cal add(rules, tokens)
  endif
endfor

for step in range(10)

  let insertions = []
  for rule in rules
    let matched = -1
    while 1
      let matched = match(str, rule[0], matched + 1)
      if matched < 0 | break | endif
      call add(insertions, [matched + 1, rule[1]])
    endwhile
  endfor
  
  let ctr = 0
  for insertion in  sort(insertions, 'ByFirst')
    let str = str[:insertion[0] + ctr - 1] . insertion[1] . str[insertion[0] + ctr:]
    let ctr += 1
  endfor

endfor

let abundance = []

for char in uniq(sort(split(str, '\zs')))
  call add(abundance, count(str, char))
endfor

call sort(abundance, 'N')

echo abundance[-1] - abundance[0]
