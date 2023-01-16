let ctr = 0
let prev_val = 0

for val in readfile('input.txt')
  
  if str2nr(val) > str2nr(prev_val)
    let ctr += 1
  endif

  let prev_val = val

endfor

echo ctr - 1
