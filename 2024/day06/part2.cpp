#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct State {
  
  int x, y, dir = 0;
  static vector<string> grid;

  static void init_grid(string const);
  void init_xy();
  bool move();

  bool const operator < (State const& other) const {
    return y < other.y ? true :
	     y > other.y ? false : 
	       x < other.x ? true :
	         x > other.x ? false :
		   dir < other.dir;
  }

  void print() const; //XXX

};

vector<string> State::grid = {""};

void State::init_xy() {
 
  for (int Y = 0; Y < grid.size(); Y++)
    for (int X = 0; X < grid.at(0).size(); X++)
      if (grid[Y][X] == '^') {
	
	x = X;
	y = Y;

	return;

      }

}

void State::print() const {

  for (string const& line : grid)
    cout << line << endl;
  
  cout << x << " " << y << endl;

}

void State::init_grid(string const file_name) {

  ifstream in_file(file_name);

  while (getline(in_file, grid.back()))
    grid.push_back("");
  
  grid.pop_back();

}

bool State::move() {
  
  int prev_x = x;
  int prev_y = y;

  switch (dir) {
    case 0: y--; break;
    case 1: x++; break;
    case 2: y++; break;
    case 3: x--; break;
  };

  if (y < 0 || y >= grid.size() || x < 0 || x >= grid.at(0).size())
    return false;

  if (grid[y][x] == '#') {

    x = prev_x;
    y = prev_y;

    dir++;
    dir %= 4;

  }

  return true;

}

int main() {
  
  State::init_grid("input.txt");

  State state;

  state.init_xy();

  set<State> path;

  set<pair<int, int>> obstructions; 

  while (true) {

    State future_state = state;
    set<State> future_path = path;

    if(! state.move())
      break;
    
    path.insert(state);

    State::grid[state.y][state.x] = '#';

    while (future_state.move())
      if(! future_path.insert(future_state).second) {
	obstructions.insert({state.y, state.x});
//      State::grid[state.y][state.x] = 'O';
//	state.print();
	break;
      }

    State::grid[state.y][state.x] = '.';

  }

  cout << obstructions.size() << endl;

}

