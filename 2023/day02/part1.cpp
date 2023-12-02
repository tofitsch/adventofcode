#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

int main(){
  
  map<string, int> max_draws = {
    {"red", 12},
    {"green", 13},
    {"blue", 14},
  };

  int sum = 0;
  
  string line, field;

  ifstream in_file("input.txt");

  while(getline(in_file, line)){
    
    bool game_possible = true;
    
    stringstream line_stream(line);

    vector<string> fields;
    
    while(getline(line_stream, field, ' '))
      fields.push_back(field);

    fields.at(1).pop_back();

    int id = stoi(fields.at(1));

    for(int i = 3; i < fields.size(); i+=2){
      
      if(i != fields.size() - 1)
        fields.at(i).pop_back();

      string colour = fields.at(i);
      int count = stoi(fields.at(i - 1));

      if(count > max_draws[colour]){
        
        game_possible = false;

        break;

      }

    }

    if(game_possible)
      sum += id;

  }

  cout << sum << endl;

}
