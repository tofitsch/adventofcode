#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct State {
  
  int x, y, dir = 0;
  static vector<string> grid;

  static void init_grid(string const);
  static int count_visited();
  void init_xy();
  bool move();

  void print() const; //XXX

};

vector<string> State::grid = {""};

int State::count_visited() {

  int count = 0;

  for (int Y = 0; Y < grid.size(); Y++)
    for (int X = 0; X < grid.at(0).size(); X++)
      if (grid[Y][X] == 'x')
	count++;
  
  return count;

}

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
  
  grid[y][x] = 'x'; //XXX

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
  
  State::init_grid("example.txt");

  State s;

  s.init_xy();

  while(s.move());

  cout << State::count_visited() << endl;

}
