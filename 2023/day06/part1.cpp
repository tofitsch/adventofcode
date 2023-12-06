#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<int> times, dists;

  getline(in_file, line);

  stringstream time_stream(line);

  while(getline(time_stream, field, ' '))
    if(isdigit(field[0]))
      times.push_back(stoi(field));

  getline(in_file, line);

  stringstream dist_stream(line);

  while(getline(dist_stream, field, ' '))
    if(isdigit(field[0]))
      dists.push_back(stoi(field));

  int prod = 1.;

  for(int i=0; i<times.size(); ++i){
    
    int n_wins = 0;

    for(int t=1; t<times.at(i); ++t)
      if((times.at(i) - t) * t > dists.at(i))
        n_wins++;

    prod *= n_wins;

  }

  cout << prod << endl;

}
