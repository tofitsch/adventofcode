#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<vector<string>> grid;

  while (getline(in_file, line)) {

    grid.push_back({});

    stringstream line_stream(line);

    while (getline(line_stream, field, ' '))
      if (field.length() > 0)
        grid.back().push_back(field);

  }

  size_t sum{0};

  for (size_t x = 0; x < grid.back().size(); ++x) {

    size_t result = (grid.back().at(x) == "+") ? 0 : 1; 

    for (size_t y = 0; y < grid.size() - 1; ++y) {
      
      if (grid.back().at(x) == "+")
        result += stol(grid.at(y).at(x));
      else
        result *= stol(grid.at(y).at(x));

    }

    sum += result;

  }

  cout << sum << endl;

}
