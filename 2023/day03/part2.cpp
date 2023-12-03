#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

struct Number {

  pair<int, int> beg;
  pair<int, int> end;

  bool adjecent_to_symbol = false;

  string num_str = "";

  void print(){cout<<beg.first<<", "<<beg.second<<" ; "<<end.first<<","<<end.second<<" : "<<num_str<<endl;}

  vector<pair<int, int>> neighbours(int & x_max, int & y_max){
    
    vector<pair<int, int>> vec;
    
    for(int x = beg.second - 1; x <= end.second + 1; x++)
      for(int y : {beg.first - 1, beg.first + 1})
        if(y >= 0 && y < y_max && x >= 0 && x < x_max)
          vec.push_back(make_pair(y, x));

    int y = beg.first;
    for(int x : {beg.second - 1, end.second + 1})
      if(y >= 0 && y < y_max && x >= 0 && x < x_max)
        vec.push_back(make_pair(y, x));

    return vec;

  }

};

int main(){
  
  string line;

  ifstream in_file("input.txt");

  vector<string> grid;

  while(getline(in_file, line))
    grid.push_back(line);

  int y_max = grid.size();
  int x_max = grid[0].size();

  Number empty_num; 

  vector<Number> nums;

  for(int y = 0; y < y_max; y++){
    
    Number num = empty_num;

    for(int x = 0; x < x_max; x++){

      char c = grid[y][x];

      if(isdigit(c)){
        
        if(num.num_str == "")
          num.beg = make_pair(y, x);
        num.num_str += c;

      }

      if((!isdigit(c) && num.num_str.size() > 0) || (isdigit(c) && x == x_max - 1)){

        num.end = make_pair(y, x - 1);
        
        nums.push_back(num);

        num = empty_num;

      }

    }

  }

  for(Number & num : nums)
    for(pair<int, int> neighbour : num.neighbours(x_max, y_max))
      if(!isdigit(grid[neighbour.first][neighbour.second]) && grid[neighbour.first][neighbour.second] != '.')
        num.adjecent_to_symbol = true;

  int sum = 0;

  for(int y = 0; y < y_max; y++){
    for(int x = 0; x < x_max; x++){
      if(grid[y][x] == '*'){

        vector<Number> gear_neighbours;

        for(Number & num : nums){
          for(pair<int, int> neighbour : num.neighbours(x_max, y_max)){
            if(neighbour.first == y && neighbour.second == x){

              gear_neighbours.push_back(num);
              break;

            }
          }
        }

        if(gear_neighbours.size() == 2){
          
          int prod = 1;

          for(Number & num : gear_neighbours)
            prod *= stoi(num.num_str);

          sum += prod;
          
        }

      }
    }
  }

  cout << sum << endl;

}
