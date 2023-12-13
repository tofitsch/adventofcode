#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector<string> transpose(vector<string> & grid, int & n_x, int & n_y){
  
  vector<string> grid_t(n_x, "");

  for(int x=0; x<n_x; x++)
    for(int y=0; y<n_y; y++)
      grid_t[x] += grid[y][x];

  return grid_t;

}

long dist(vector<bool> & dim_expands, int & a, int & b){
  
  int min, max;

  if(a > b){
    max = a;
    min = b;
  }
  else{
    max = b;
    min = a;
  }

  int n_expansions = 0;

  for(int i=min; i<max; i++)
    if(dim_expands[i])
      n_expansions++;

  return abs(a - b) + n_expansions * (1e6 - 1);

}

int main(){

  string line;

  ifstream in_file("input.txt");

  vector<string> grid;

  while(getline(in_file, line))
    grid.push_back(line);

  int n_x = grid[0].length();
  int n_y = grid.size();

  vector<string> grid_t = transpose(grid, n_x, n_y);

  vector<bool> row_expands(grid.size(), false);
  vector<bool> col_expands(grid_t.size(), false);

  for(int y=0; y<n_y; y++)
    if(grid[y].find("#") == string::npos)
      row_expands[y] = true;

  for(int x=0; x<n_x; x++)
    if(grid_t[x].find("#") == string::npos)
      col_expands[x] = true;

  vector<pair<int, int>> coords;
  
  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      if(grid[y][x] == '#')
        coords.push_back({y, x});
  
  long sum = 0;
  
  for(auto & ca : coords)
    for(auto & cb : coords)
      if(ca != cb)
        sum += dist(row_expands, ca.first, cb.first) + dist(col_expands, ca.second, cb. second);
  
  cout << sum / 2 << endl;
  
}
