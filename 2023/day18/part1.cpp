#include<iostream>
#include<fstream>
#include<sstream>
#include<limits>
#include<vector>

using namespace std;

struct Instruction{

  char direction;
  int length;

  Instruction(string & line){
     
     string field;

     stringstream line_stream(line);

     getline(line_stream, field, ' ');

     direction = field[0];

     getline(line_stream, field, ' ');

     length = stoi(field);

  }

};

struct Coordinate{

  int y;
  int x;

  int n_y, n_x;

  int min_y = numeric_limits<int>::max();
  int min_x = numeric_limits<int>::max();
  int max_y = numeric_limits<int>::min();
  int max_x = numeric_limits<int>::min();

  int step_ctr;

  Coordinate() : y(0), x(0) {}
  Coordinate(int y, int x) : y(y), x(x) {}
  Coordinate(int y, int x, int n_y, int n_x) : y(y), x(x), n_y(n_y), n_x(n_x) {}

  void apply(Instruction & instruction){
    
    switch(instruction.direction){

      case 'U': y -= instruction.length; break;
      case 'D': y += instruction.length; break;
      case 'L': x -= instruction.length; break;
      case 'R': x += instruction.length; break;

    };

  }

  bool apply_step(Instruction & instruction){
    
    switch(instruction.direction){

      case 'U': y--; break;
      case 'D': y++; break;
      case 'L': x--; break;
      case 'R': x++; break;

    };

    step_ctr++;

    return step_ctr < instruction.length;

  }

  void update_limits(Instruction & instruction){

    apply(instruction);

    if(y > max_y) max_y = y;
    if(x > max_x) max_x = x;
    if(y < min_y) min_y = y;
    if(x < min_x) min_x = x;

  }

  void normalise(){

    y = -min_y + 1 ;
    x = -min_x + 1;

    n_y = max_y - min_y + 1;
    n_x = max_x - min_x + 1;

  }

  void update_grid(Instruction & instruction, vector<string> & grid){
    
    step_ctr = 0;
    
    do grid[y][x] = '#';
    while(apply_step(instruction));

  }

};

void flood_fill(vector<string> & grid, int & sum, Coordinate coord){
  
  if(grid[coord.y][coord.x] != '.')
    return;

  grid[coord.y][coord.x] = 'x';

  sum++;

  if(coord.y > 0)
    flood_fill(grid, sum, Coordinate(coord.y - 1, coord.x, coord.n_y, coord.n_x));
  if(coord.x > 0)
    flood_fill(grid, sum, Coordinate(coord.y, coord.x - 1, coord.n_y, coord.n_x));
  if(coord.y < coord.n_y + 1)
    flood_fill(grid, sum, Coordinate(coord.y + 1, coord.x, coord.n_y, coord.n_x));
  if(coord.x < coord.n_x + 1)
    flood_fill(grid, sum, Coordinate(coord.y, coord.x + 1, coord.n_y, coord.n_x));
  
}

int main(){
  
  vector<Instruction> instructions;

  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line))
    instructions.push_back(Instruction(line));

  Coordinate coord;

  for(Instruction & instruction : instructions)
    coord.update_limits(instruction);
  
  coord.normalise();

  vector<string> grid(coord.n_y + 2, string(coord.n_x + 2, '.'));

  for(Instruction & instruction : instructions)
    coord.update_grid(instruction, grid);

  coord.x = 0;
  coord.y = 0;

  int sum = 0;

  flood_fill(grid, sum, coord);

  cout << (coord.n_y + 2) * (coord.n_x + 2) - sum << endl;

}
