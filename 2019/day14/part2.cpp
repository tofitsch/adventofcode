#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<string, long> quantities;
map<string, vector<pair<string, long>>> recipes;

void do_recipe(string product, long factor){
  
  factor /= recipes[product].back().second; 
  if(factor == 0) factor++;

  quantities[product] += recipes[product].back().second * factor;

  for(int i=0; i<recipes[product].size() - 1; i++)
    quantities[recipes[product][i].first] -= recipes[product][i].second * factor;

}

bool step(){
   
    bool complete = true;

    for(auto &x : quantities){

      if(x.first == "ORE") continue;
      
      while(x.second < 0){

        complete = false;

        do_recipe(x.first, -x.second);

      }

    }

    return complete;

}

long get_ore_for_fuel(long fuel){
  
  quantities.clear();

  quantities["FUEL"] = -fuel;

  while(!step()){}

  return -quantities["ORE"];

}

int main(){

  ifstream in_file("input.txt");

  string line, field;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);

    bool is_number = true;

    vector<pair<string, long>> vec;

    while(getline(line_stream, field, ' ')){
      
      if(field == "=>") continue;

      if(field.back() == ',') field.pop_back();
      
      if(is_number) vec.push_back({"", stoi(field)});
      else vec.back().first = field;

      is_number = !is_number;
      
    }

    recipes[vec.back().first] = vec;

  }

  long target = 1e12;

  long min = 1;
  long max = target;
  long mid;

  long ore;

  while(abs(min - max) > 1){
    
    mid = min + (max - min) / 2;

    ore = get_ore_for_fuel(mid);

    if(ore > target) max = mid;
    else min = mid;

    cout<<min<<" "<<max<<" "<<ore<<endl;

  }

  if(ore > target) mid--;

  cout<<mid<<endl;

}
