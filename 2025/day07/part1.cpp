#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void recurse(size_t const x, size_t const y, vector<string> & grid, size_t & ctr) {

  if (y == grid.size())
    return;

  char & c = grid[y][x];

  switch (c) {

    case 'S':
    case '.':
      c = '|';
      recurse(x, y + 1, grid, ctr);
      break;

    case '^':
      ++ctr;
      recurse(x - 1, y, grid, ctr);
      recurse(x + 1, y, grid, ctr);

  }

}

int main(){
  
  string line;

  ifstream in_file("input.txt");

  vector<string> grid;

  while (getline(in_file, line))
    grid.push_back(line);

  size_t const source = grid[0].find('S');

  size_t ctr{0};

  recurse(source, 0, grid, ctr);

  cout << ctr << endl;

}
