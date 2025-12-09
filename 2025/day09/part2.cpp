#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Coordinate {

  Coordinate(string line) {

    size_t const pos = line.find(',');

    x = stol(line.substr(0, pos));
    y = stol(line.substr(pos + 1));

  }

  long
    x, y,
    compact_x, compact_y;

};

long rectangle_area(Coordinate const& a, Coordinate const& b)
  {return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);}

bool is_rectange(Coordinate const& a, Coordinate const& b, vector<string> const& grid) {

  for (size_t x = min(a.compact_x, b.compact_x); x <= max(a.compact_x, b.compact_x); ++x)
    for (size_t y = min(a.compact_y, b.compact_y); y <= max(a.compact_y, b.compact_y); ++y)
      if (grid[y][x] == '.')
        return false;

  return true;

}

void flood_fill(vector<string> & grid) {

  vector<pair<long, long>> q; 

  q.push_back({0, 0});

  while (! q.empty()) {

    long const
      x = q.back().first,
      y = q.back().second;

    q.pop_back();

    if (y < 0 || x < 0 || y >= grid.size() || x >= grid[0].size())
      continue;

    if (grid[y][x] == 'b') {

      grid[y][x] = '.';

      q.push_back({x + 1, y});
      q.push_back({x - 1, y});
      q.push_back({x, y + 1});
      q.push_back({x, y - 1});

    }

  }

}

void compactify(vector<Coordinate> & coordinates) {

  set<long> x, y;

  for (Coordinate const& c : coordinates) {

    x.insert(c.x);
    y.insert(c.y);

  }

  for (Coordinate & c : coordinates) {

    c.compact_x = distance(x.begin(), x.find(c.x)) + 1;
    c.compact_y = distance(y.begin(), y.find(c.y)) + 1;

  }

}


vector<string> make_grid(vector<Coordinate> const& coordinates) {

  long
    max_x{0},
    max_y{0};

  for (Coordinate const& c : coordinates) {

    if (c.compact_x > max_x)
      max_x = c.compact_x;

    if (c.compact_y > max_y)
      max_y = c.compact_y;

  }

  vector<string> grid(max_y + 2, string(max_x + 2, 'b'));

  for (size_t i = 0; i < coordinates.size(); ++i) {

    Coordinate const 
      a = coordinates[i],
      b = coordinates[(i + 1) % coordinates.size()];

    grid[a.compact_y][a.compact_x] = 'r';

    if (a.compact_x == b.compact_x) {

      for (size_t y = min(a.compact_y, b.compact_y); y < max(a.compact_y, b.compact_y); ++y)
        if (grid[y][a.compact_x] == 'b')
          grid[y][a.compact_x] = 'g';

    } else {

      for (size_t x = min(a.compact_x, b.compact_x); x < max(a.compact_x, b.compact_x); ++x)
        if (grid[a.compact_y][x] == 'b')
          grid[a.compact_y][x] = 'g';

    }

  }

  return std::move(grid);

}


int main() {

  string line;

  vector<Coordinate> coordinates;

  ifstream in_file("input.txt");

  while (getline(in_file, line))
    coordinates.emplace_back(line);

  compactify(coordinates);

  vector<string> grid = make_grid(coordinates);

  flood_fill(grid);

  long max_area{0};

  for (Coordinate const& a : coordinates) {
    for (Coordinate const& b : coordinates) {

      if (! is_rectange(a, b, grid))
        continue;

      if (rectangle_area(a, b) > max_area)
        max_area = rectangle_area(a, b);

    }
  }

  cout << max_area << endl;

}
