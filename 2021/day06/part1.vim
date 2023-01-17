let fish = split(readfile('input.txt')[0], ',')

for t in range(80)
  for i in range(len(fish))

    if fish[i] == 0 
      let fish[i] = 6
      call add(fish, 8)
    else
      let fish[i] -= 1
    endif

  endfor
endfor

echo len(fish)
