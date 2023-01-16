let ctr = 0

let arr = readfile('input.txt')

let i = 4
while i < len(arr)

  let val = arr[i] + arr[i-1] + arr[i-2]
  let prev_val = arr[i-1] + arr[i-2] + arr[i-3]

  if str2nr(val) > str2nr(prev_val)
    let ctr += 1
  endif

  let i += 1

endwhile
  
echo ctr + 1
