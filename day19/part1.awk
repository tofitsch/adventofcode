#!/bin/awk

func recursive_move(t, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots,  i, j, k, l){

  if(t == 0){
    print t, "\t|", ore, cla, obs, geo, "\t|", ore_bots, cla_bots, obs_bots, geo_bots
    return ""
  }

  ore += ore_bots
  cla += cla_bots
  obs += obs_bots
  geo += geo_bots

  i=1
  while(ore >= i*geo_bot_costs_ore && obs >= i*geo_bot_costs_obs){
    recursive_move(t-1, ore-i*geo_bot_costs_ore, cla, obs-i*geo_bot_costs_obs, geo, ore_bots, cla_bots, obs_bots, geo_bots+i)
    i++
  }

  j=1
  while(ore >= j*obs_bot_costs_ore && cla >= j*obs_bot_costs_cla){
    recursive_move(t-1, ore-j*obs_bot_costs_ore, cla-j*obs_bot_costs_cla, obs, geo, ore_bots, cla_bots, obs_bots+j, geo_bots)
    j++
  }

  k=1
  while(ore >= k*cla_bot_costs_ore){
    recursive_move(t-1, ore-k*cla_bot_costs_ore, cla, obs, geo, ore_bots, cla_bots+k, obs_bots, geo_bots)
    k++
  }

  l=1
  while(ore >= l*ore_bot_costs_ore){
    recursive_move(t-1, ore-l*ore_bot_costs_ore, cla, obs, geo, ore_bots+l, cla_bots, obs_bots, geo_bots)
    l++
  }

  recursive_move(t-1, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots)

}

END {

  ore_bot_costs_ore = $7
  cla_bot_costs_ore = $13
  obs_bot_costs_ore = $19
  obs_bot_costs_cla = $22
  geo_bot_costs_ore = $28
  geo_bot_costs_obs = $31


  recursive_move(15, 0, 0, 0, 0, 1, 0, 0, 0)

}
