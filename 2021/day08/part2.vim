let segmentation = ['012456', '25', '02346', '02355', '1235', '01356', '013456', '025', '0123456', '012356']  

for line in readfile('example.txt')
  
  let words = split(line, ' | \| ')

  let char_frequency = repeat([0], 7)
  let char_frequency_no24 = repeat([0], 7)
  let char_frequency_no6 = repeat([0], 7)

  for w in range(10)
    let n = len(words[w])
    let chars = split(words[w], '\zs')
    for c in chars
      let char_frequency[char2nr(c) - 97] += 1
      if n != 2 && n!= 4 | let char_frequency_no24[char2nr(c) - 97] += 1 | endif
      if n != 6 | let char_frequency_no6[char2nr(c) - 97] += 1 | endif
    endfor
  endfor

  let code = repeat([-1], 7)

  let code[0] = index(char_frequency_no24, 8)
  let code[1] = index(char_frequency, 6)

  let code[4] = index(char_frequency, 4)
  let code[5] = index(char_frequency, 9)
  let code[6] = index(char_frequency_no6, 4)

  for i in range(7)
    if char_frequency[i] == 8 && index(code, i) < 0 | let code[2] = i | endif
    if char_frequency[i] == 7 && index(code, i) < 0 | let code[3] = i | endif
  endfor

  echo code

  let result = ''

  for w in range(10, 13)

    let decoded = []

    for c in split(words[w], '\zs')
      call add(decoded, code[char2nr(c) - 97])
    endfor

    let segments = join(sort(decoded), '')

    echo segments

    let result .= index(segmentation, segments)

  endfor

  echo '> ' result

endfor
