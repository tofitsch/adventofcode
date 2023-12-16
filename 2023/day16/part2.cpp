#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct Beam{

  int y, x, direction;

  Beam(int y, int x, int d) : y(y), x(x), direction(d) {}

};

struct Grid{
  
  int n_x, n_y;

  vector<string> grid;

  vector<Beam> beam_fronts;

  vector<vector<bool>> has_beam_horizontal;
  vector<vector<bool>> has_beam_vertical;
  
  Grid(string in_file_name){

    string line;

    ifstream in_file(in_file_name);

    while(getline(in_file, line)){

      grid.push_back(line);

      has_beam_horizontal.push_back(vector<bool>(line.length(), false));
      has_beam_vertical.push_back(vector<bool>(line.length(), false));

    }

    n_x = grid[0].size();
    n_y = grid.size();

    beam_fronts.push_back(Beam(0, -1, 1));
    has_beam_horizontal[0][0] = true;

  }

  void init(Beam beam){
    
    beam_fronts = {beam};

    for(int y=0; y<n_y; y++){
      for(int x=0; x<n_x; x++){

        has_beam_horizontal[y][x] = false;
        has_beam_vertical[y][x] = false;

      }
    }

  }

  vector<Beam> propagate_beam_front(Beam & beam){

    vector<Beam> new_beams;

    switch(beam.direction){
      case 0: beam.y--; break;
      case 1: beam.x++; break;
      case 2: beam.y++; break;
      case 3: beam.x--; break;
    }

    if(beam.x < 0 || beam.y < 0 || beam.x >= n_x || beam.y >= n_y)
      return {};

    bool remove_beam = false;

    switch(grid[beam.y][beam.x]){

      case '/' :
        switch(beam.direction){
          case 0: beam.direction = 1; break;
          case 1: beam.direction = 0; break;
          case 2: beam.direction = 3; break;
          case 3: beam.direction = 2; break;
        }
        break;

      case '\\':
        switch(beam.direction){
          case 0: beam.direction = 3; break;
          case 1: beam.direction = 2; break;
          case 2: beam.direction = 1; break;
          case 3: beam.direction = 0; break;
        }
        break;

      case '-' :
        switch(beam.direction){
          case 1: break;
          case 3: break;
          default: new_beams = {Beam(beam.y, beam.x, 1), Beam(beam.y, beam.x, 3)}; remove_beam = true; break;
        }
        break;

      case '|' :
        switch(beam.direction){
          case 0: break;
          case 2: break;
          default: new_beams = {Beam(beam.y, beam.x, 0), Beam(beam.y, beam.x, 2)}; remove_beam = true; break;
        }
        break;

    }

    switch(beam.direction){
      case 0: if(grid[beam.y][beam.x] == '.' && has_beam_vertical[beam.y][beam.x])   remove_beam = true; break;
      case 1: if(grid[beam.y][beam.x] == '.' && has_beam_horizontal[beam.y][beam.x]) remove_beam = true; break;
      case 2: if(grid[beam.y][beam.x] == '.' && has_beam_vertical[beam.y][beam.x])   remove_beam = true; break;
      case 3: if(grid[beam.y][beam.x] == '.' && has_beam_horizontal[beam.y][beam.x]) remove_beam = true; break;
    }

    for(Beam & new_beam : new_beams){
      switch(new_beam.direction){
        case 0: if(has_beam_vertical[beam.y][beam.x]) new_beam.direction = -1; break;
        case 1: if(has_beam_horizontal[beam.y][beam.x])   new_beam.direction = -1; break;
        case 2: if(has_beam_vertical[beam.y][beam.x]) new_beam.direction = -1; break;
        case 3: if(has_beam_horizontal[beam.y][beam.x])   new_beam.direction = -1; break;
      }
    }

    vector<Beam> out_beams;

    if(!remove_beam)
      out_beams.push_back(beam);

    for(Beam & new_beam : new_beams)
      if(new_beam.direction >= 0)
        out_beams.push_back(new_beam);

    for(Beam & b : out_beams)
      if(b.direction == 0 || b.direction == 2)
        has_beam_vertical[beam.y][beam.x] = true;
      else
        has_beam_horizontal[beam.y][beam.x] = true;
    
    return out_beams;

  }

  void propagate(){
    
    vector<Beam> new_beam_fronts;

    for(Beam & beam : beam_fronts)
      for(Beam new_beam : propagate_beam_front(beam))
        new_beam_fronts.push_back(new_beam);
    
    beam_fronts = new_beam_fronts;

  }

  int count_occupied_tiles(){
    
    int ctr = 0;
    
    for(int y=0; y<n_y; y++)
      for(int x=0; x<n_x; x++)
        if(has_beam_vertical[y][x] || has_beam_horizontal[y][x])
	  ctr++;
    
    return ctr;

  }

};

void eval(Grid & grid, int & max){

  while(grid.beam_fronts.size() > 0)
    grid.propagate();

  int occupied_tiles = grid.count_occupied_tiles();

  if(occupied_tiles > max)
    max = occupied_tiles;

}

int main(){

  Grid grid("input.txt");

  int max = 0;
  
  for(int y=0; y<grid.n_y; y++){
    
    grid.init(Beam(y, -1, 1));
    eval(grid, max);

    grid.init(Beam(y, grid.n_x, 3));
    eval(grid, max);

  }

  for(int x=0; x<grid.n_x; x++){
    
    grid.init(Beam(-1, x, 2));
    eval(grid, max);

    grid.init(Beam(grid.n_y, x, 0));
    eval(grid, max);

  }

  cout << max << endl;

  
}
