#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>

using namespace std;

int main(){

  vector<string> grid;
  
  string line;

  ifstream in_file("input.txt");

  while (getline(in_file, line))
    grid.push_back(line);

  int const
    n_x = grid[0].length(),
    n_y = grid.size();

  auto n_neighbours = [&](int y, int x) -> size_t {

    size_t n{0};

    for (int X = max(x - 1, 0); X <= min(x + 1, n_x - 1); ++X)
      for (int Y = max(y - 1, 0); Y <= min(y + 1, n_y - 1); ++Y)
        if ((Y != y || X != x) && grid[Y][X] == '@')
          ++n;

    return n;

  };

  size_t ctr{0};

  for (int y = 0; y < n_y; ++y)
    for (int x = 0; x < n_x; ++x)
      if (grid[y][x] == '@' && n_neighbours(y , x) < 4)
        ++ctr;

  cout << ctr << endl;

}
