#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

int main(){
  
  int sum = 0;
  
  string line, field;

  ifstream in_file("input.txt");

  while(getline(in_file, line)){

    map<string, int> max_counts = {
      {"red", 0},
      {"green", 0},
      {"blue", 0},
    };

    bool game_possible = true;
    
    stringstream line_stream(line);

    vector<string> fields;
    
    while(getline(line_stream, field, ' '))
      fields.push_back(field);

    for(int i = 3; i < fields.size(); i+=2){
      
      if(i != fields.size() - 1)
        fields.at(i).pop_back();

      string colour = fields.at(i);
      int count = stoi(fields.at(i - 1));

      if(max_counts[colour] < count)
        max_counts[colour] = count;

    }

    int power = 1.;

    for(auto & key : max_counts)
      power *= key.second;

    sum += power;

  }

  cout << sum << endl;

}
