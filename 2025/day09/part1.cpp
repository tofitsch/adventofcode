#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Coordinate {

  Coordinate(string line) {

    size_t const pos = line.find(',');

    x = stol(line.substr(0, pos));
    y = stol(line.substr(pos + 1));

  }

  long x, y;

};

long rectangle_area(Coordinate const& a, Coordinate const& b)
  {return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);}

int main() {

  string line;

  vector<Coordinate> coordinates;

  ifstream in_file("input.txt");

  while (getline(in_file, line))
    coordinates.emplace_back(line);

  long max_area{0};

  for (Coordinate const& a : coordinates)
    for (Coordinate const& b : coordinates)
      if (rectangle_area(a, b) > max_area)
        max_area = rectangle_area(a, b);

  cout << max_area << endl;

}
