#!/bin/awk

func recursive_move(t, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots,  i, j, k, l, rest_ore, rest_cla, rest_obs){

  if(t == 0){
    if(geo > most_geo) most_geo = geo
    return ""
  }

  ore += ore_bots
  cla += cla_bots
  obs += obs_bots
  geo += geo_bots

  for(i=0; i<=ore_bot_costs_ore/ore; i++){
    for(j=0; j<=cla_bot_costs_ore/ore; j++){
      for(k=0; k<=obs_bot_costs_ore/ore; k++){
        for(l=0; l<=geo_bot_costs_ore/ore; l++){

          rest_ore = ore-i*ore_bot_costs_ore-j*cla_bot_costs_ore-k*obs_bot_costs_ore-l*geo_bot_costs_ore
          rest_cla = cla-k*obs_bot_costs_cla
          rest_obs = obs-l*geo_bot_costs_obs

          if(rest_ore >= 0 && rest_cla >=0 && rest_obs >=0)
            recursive_move(t-1, rest_ore, rest_cla, rest_obs, geo, ore_bots+i, cla_bots+j, obs_bots+k, geo_bots+l)

        }
      }
    }
  }

}

{

  ore_bot_costs_ore = $7
  cla_bot_costs_ore = $13
  obs_bot_costs_ore = $19
  obs_bot_costs_cla = $22
  geo_bot_costs_ore = $28
  geo_bot_costs_obs = $31

  recursive_move(25, 0, 0, 0, 0, 1, 0, 0, 0)

  print most_geo 

}
