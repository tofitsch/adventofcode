func Nr2Bin(nr)
  let n = a:nr
  let r = ''
  while n
    let r = '01'[n % 2] . r
    let n = n / 2
  endwhile
  return printf('%04d', r)
endfunc

let line = readfile('example.txt')[0]

let binary = ''

for c in range(len(line)) | let binary = binary . Nr2Bin(str2nr(line[c], 16)) | endfor

let pkg_beg = 0

let pkg_version = str2nr(binary[pkg_beg : pkg_beg + 2], 2)
let pkg_type = str2nr(binary[pkg_beg + 3 : pkg_beg + 5], 2)

if pkg_type == 4

  let pkg_end = -1
  let sub_pkgs = ''
  
  let sub_pkg_pos = pkg_beg + 6
  
  while pkg_end < 0
  
    let sub_pkgs = sub_pkgs . binary[sub_pkg_pos + 1 : sub_pkg_pos + 4]
  
    if binary[sub_pkg_pos] == 0
      let pkg_end = sub_pkg_pos + 5
    else
      let sub_pkg_pos += 5
    endif
  
  endwhile
  
  let pkg_beg = (4 - ((pkg_end - pkg_beg) % 4)) % 4 + 1
  
  let pkg_content = str2nr(sub_pkgs, 2)

  echo pkg_version pkg_type sub_pkgs

else

  let pkg_length_type = binary[pkg_beg + 6]
  
  if pkg_length_type == 0

    let sub_pkg_length = str2nr(binary[pkg_beg + 7 : pkg_beg + 21], 2)

    echo pkg_version pkg_type pkg_length_type sub_pkg_length

  else

    let sub_pkg_n = str2nr(binary[pkg_beg + 7 : pkg_beg + 17], 2)

    echo pkg_version pkg_type pkg_length_type sub_pkg_n

  endif

endif

