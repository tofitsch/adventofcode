#!/bin/awk

func recursive_move(t, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots,  i, j, k, l, rest_ore, rest_cla, rest_obs){

  if(t == 0){
    print t, "\t|", ore, cla, obs, geo, "\t|", ore_bots, cla_bots, obs_bots, geo_bots
    return ""
  }

  ore += ore_bots
  cla += cla_bots
  obs += obs_bots
  geo += geo_bots

  for(i=0; i<28; i++){
    for(j=0; j<28; j++){
      for(k=0; k<28; k++){
        for(l=0; l<28; l++){
          rest_ore = ore-i*geo_bot_costs_ore-j*obs_bot_costs_ore-k*cla_bot_costs_ore-l*ore_bot_costs_ore
          rest_cla = cla-j*obs_bot_costs_cla
          rest_obs = obs-i*geo_bot_costs_obs
          if(rest_ore >= 0 && rest_cla >=0 && rest_obs >=0 && rest_ore < 3 && rest_cla < 8 && rest_obs < 12)
            recursive_move(t-1, rest_ore, rest_cla, rest_obs, geo, ore_bots+l, cla_bots+k, obs_bots+j, geo_bots+i)
        }
      }
    }
  }

}

END {

  ore_bot_costs_ore = $7
  cla_bot_costs_ore = $13
  obs_bot_costs_ore = $19
  obs_bot_costs_cla = $22
  geo_bot_costs_ore = $28
  geo_bot_costs_obs = $31


  recursive_move(10, 0, 0, 0, 0, 1, 0, 0, 0)

}
