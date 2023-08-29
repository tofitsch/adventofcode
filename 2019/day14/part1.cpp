#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<string, int> quantities;
map<string, vector<pair<string, int>>> recipes;

void do_recipe(string product){
  
  quantities[product] += recipes[product].back().second;

  for(int i=0; i<recipes[product].size() - 1; i++)
    quantities[recipes[product][i].first] -= recipes[product][i].second;

}

bool step(){
   
    bool complete = true;

    for(auto &x : quantities){

      if(x.first == "ORE") continue;
      
      while(x.second < 0){

        complete = false;

        do_recipe(x.first);

      }

    }

    return complete;

}

int main(){

  ifstream in_file("input.txt");

  string line, field;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);

    bool is_number = true;

    vector<pair<string, int>> vec;

    while(getline(line_stream, field, ' ')){
      
      if(field == "=>") continue;

      if(field.back() == ',') field.pop_back();
      
      if(is_number) vec.push_back({"", stoi(field)});
      else vec.back().first = field;

      is_number = !is_number;
      
    }

    recipes[vec.back().first] = vec;

  }

  quantities["FUEL"] = -1;

  while(!step()){}

  cout<<-quantities["ORE"]<<endl;

}
