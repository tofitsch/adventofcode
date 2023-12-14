#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

bool  move_rocks_north(vector<string> & grid){
  
  int moved = false;
  
  for(int y=1; y<grid.size(); y++)
    for(int x=0; x<grid[y].length(); x++)
      if(grid[y][x] == 'O' && grid[y - 1][x] == '.'){

        grid[y][x] = '.';
        grid[y - 1][x] = 'O';

	moved = true;

      }

  return moved;

}

int main(){

  string line;

  ifstream in_file("input.txt");

  vector<string> grid;

  while(getline(in_file, line))
    grid.push_back(line);

  while(move_rocks_north(grid))
   continue;

  int load = 0;

  for(int y=0; y<grid.size(); y++)
    for(int x=0; x<grid[y].length(); x++)
      if(grid[y][x] == 'O')
        load += grid.size() - y;

  cout << load << endl;

}
