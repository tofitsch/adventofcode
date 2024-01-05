#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> rotate_right(vector<string> & grid){

  int n = grid.size();

  vector<string> grid_t(n, string(n, ' '));

  for(int x=0; x<n; x++)
    for(int y=0; y<n; y++)
      grid_t[y][x] = grid[n - 1 - x][y];

  return grid_t;

}

bool move_rocks_north(vector<string> & grid){
  
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

int get_load(vector<string> & grid){

  int load = 0;

  for(int y=0; y<grid.size(); y++)
    for(int x=0; x<grid[y].length(); x++)
      if(grid[y][x] == 'O')
        load += grid.size() - y;

  return load;

}

void print(vector<string> & grid, int s){
  
  cout << "After " << s << " cycle:" << endl;

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].length(); x++){

      cout << grid[y][x];

    }

    cout << endl;

  }

  cout << endl;

}

int main(){

  string line;

  ifstream in_file("input.txt");

  vector<string> grid;

  while(getline(in_file, line))
    grid.push_back(line);

  long n_steps = 1e9;

  vector<vector<string>> states;

  for(long s=0; s < n_steps; s++){
    
    cout << s << ": " << get_load(grid) << endl;
      
//    print(grid, s);
      
    vector<vector<string>>::iterator same_state_it = find(states.begin(), states.end(), grid);

    if(same_state_it != states.end()){
      
      long offset = distance(states.begin(), same_state_it);

      long period = s - offset;
      
      cout << "TEST " << s << " " <<  offset << " " << period << endl;
      cout << offset + (n_steps - offset) % period << endl;

      grid = states[offset + (n_steps - offset) % period];


      break;

    }
    
    states.push_back(grid);
    
    for(int i=0; i<4; i++){

      while(move_rocks_north(grid))
        continue;

      grid = rotate_right(grid);

    }

  }

  cout << get_load(grid) << endl;

}
