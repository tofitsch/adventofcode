#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

struct Square{

  int id, x0, x1, y0, y1;

  void mark(int *, int const);

  Square(string);

};

void Square::mark(int * grid, int const n){

  for(int x=x0; x<x1; x++)
    for(int y=y0; y<y1; y++)
      grid[y * n + x]++;

}

Square::Square(string line){
  
  string field;
  
  stringstream line_stream(line);

  getline(line_stream, field, ' ');

  field.erase(0, 1);

  id = stoi(field);

  getline(line_stream, field, ' ');
  getline(line_stream, field, ' ');

  field.pop_back();

  stringstream pos_stream(field);

  getline(pos_stream, field, ',');

  x0 = stoi(field);

  getline(pos_stream, field, ',');

  y0 = stoi(field);

  getline(line_stream, field, ' ');

  stringstream width_stream(field);

  getline(width_stream, field, 'x');

  x1 = x0 + stoi(field);

  getline(width_stream, field, 'x');

  y1 = y0 + stoi(field);

}

int main(){
  
  vector<Square> squares;

  int const n = 1000;

  int grid[n][n] = {0};

  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line))
    squares.push_back(Square(line));

  for(Square & s : squares)
    s.mark(& grid[0][0], n);
  
  int count = 0;

  for(int x=0; x<n; x++)
    for(int y=0; y<n; y++)
      if(grid[y][x] > 1)
        count++;

  cout << count << endl;

}
