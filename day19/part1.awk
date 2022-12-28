#!/bin/awk

func recursive_move(t, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, new_ore_bots, new_cla_bots, new_obs_bots, new_geo_bots){
  
  if(t < 0){
    if(geo > most_geo) most_geo = geo
    return
  }

  ore += ore_bots
  cla += cla_bots
  obs += obs_bots
  geo += geo_bots

  ore_bots += new_ore_bots
  cla_bots += new_cla_bots
  obs_bots += new_obs_bots
  geo_bots += new_geo_bots

  rest_ore = ore - geo_bot_costs_ore
  rest_obs = obs - geo_bot_costs_obs
  if(ore_bots >= geo_bot_costs_ore && obs_bots >= geo_bot_costs_obs && rest_ore >= 0 && rest_obs >= 0){
    recursive_move(t-1, rest_ore, cla, rest_obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 0, 0, 0, 1)
  }
  else{
    if(ore < max_ore_cost) recursive_move(t-1, ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 0, 0, 0, 0)

    rest_ore = ore - ore_bot_costs_ore
    if(rest_ore >= 0 && ore_bots < max_ore_cost) recursive_move(t-1, rest_ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 1, 0, 0, 0)

    rest_ore = ore - cla_bot_costs_ore
    if(rest_ore >= 0 && cla_bots < obs_bot_costs_cla) recursive_move(t-1, rest_ore, cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 0, 1, 0, 0)

    rest_ore = ore - obs_bot_costs_ore
    rest_cla = cla - obs_bot_costs_cla
    if(rest_ore >= 0 && rest_cla >= 0 && obs_bots < geo_bot_costs_obs) recursive_move(t-1, rest_ore, rest_cla, obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 0, 0, 1, 0)
 
    rest_ore = ore - geo_bot_costs_ore
    rest_obs = obs - geo_bot_costs_obs
    if(rest_ore >= 0 && rest_obs >= 0) recursive_move(t-1, rest_ore, cla, rest_obs, geo, ore_bots, cla_bots, obs_bots, geo_bots, 0, 0, 0, 1)
  }

}

{
  
  most_geo = 0

  ore_bot_costs_ore = $7
  cla_bot_costs_ore = $13
  obs_bot_costs_ore = $19
  obs_bot_costs_cla = $22
  geo_bot_costs_ore = $28
  geo_bot_costs_obs = $31

  max_ore_cost = ore_bot_costs_ore
  if(cla_bot_costs_ore > max_ore_cost) max_ore_cost = cla_bot_costs_ore
  if(obs_bot_costs_ore > max_ore_cost) max_ore_cost = obs_bot_costs_ore
  if(geo_bot_costs_ore > max_ore_cost) max_ore_cost = geo_bot_costs_ore

  recursive_move(24, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0)

  print most_geo

  sum += NR * most_geo

}

END {print " > " sum}
