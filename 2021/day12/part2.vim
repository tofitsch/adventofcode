let links = {}
let ctr = 0

function! Move(path, visited_small_twice)
  for link in g:links[a:path[-1]]
    if link == 'start' | continue | endif
    if link == 'end' | let g:ctr += 1 | continue | endif
    if match(link, '[a-z]') == 0 && index(a:path, link) != -1
      if a:visited_small_twice
       continue
      else
       call Move(a:path + [link], 1)
      endif
    else
      call Move(a:path + [link], a:visited_small_twice)
    endif
  endfor
endfunction

for line in readfile('input.txt')
  let nodes = split(line, '-')
  for i in [0, 1]
    if has_key(links, nodes[0])
      call add(links[nodes[0]], nodes[1])
    else
      let links[nodes[0]] = [nodes[1]]
    endif
    call reverse(nodes)
  endfor
endfor

call Move(['start'], 0)

echo ctr
