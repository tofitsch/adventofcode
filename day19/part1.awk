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

  recursive_move(t-1, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots)

  rest_ore = ore - ore_bot_costs_ore
  if(rest_ore >= 0) recursive_move(t-1, rest_ore, cla, obs, geo, ore_bots+1, cla_bots, obs_bots, geo_bots)

  rest_ore = ore - cla_bot_costs_ore
  if(rest_ore >= 0) recursive_move(t-1, rest_ore, cla, obs, geo, ore_bots, cla_bots+1, obs_bots, geo_bots)

  rest_ore = ore - obs_bot_costs_ore
  rest_cla = cla - obs_bot_costs_cla
  if(rest_ore >= 0 && rest_cla >= 0) recursive_move(t-1, rest_ore, rest_cla, obs, geo, ore_bots, cla_bots, obs_bots+1, geo_bots)
 
  rest_ore = ore - geo_bot_costs_ore
  rest_obs = obs - geo_bot_costs_obs
  if(rest_ore >= 0 && rest_obs >= 0) recursive_move(t-1, rest_ore, cla, rest_obs, geo, ore_bots, cla_bots, obs_bots, geo_bots+1)

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
