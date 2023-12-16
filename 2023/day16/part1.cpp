#include<iostream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

struct Beam{

  int y, x, direction;

  Beam(int y, int x, int d) : y(y), x(x), direction(d) {}

};

struct Grid{
  
  int n_x, n_y;

  vector<string> grid;

  vector<Beam> beams;

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

    beams.push_back(Beam(0, 0, 1));
    has_beam_horizontal[0][0] = true;

  }

  void propagate_beams(){

    for(auto it = beams.begin(); it != beams.end();){
      
      Beam * new_beam = nullptr;

      switch(it->direction){
        case 0: it->y--; break;
        case 1: it->x++; break;
        case 2: it->y++; break;
        case 3: it->x--; break;
      }

      switch(grid[it->y][it->x]){

        case '/' :
          switch(it->direction){
	    case 0: it->direction = 1; break;
	    case 1: it->direction = 0; break;
	    case 2: it->direction = 3; break;
	    case 3: it->direction = 2; break;
	  }
	  break;

        case '\\':
          switch(it->direction){
	    case 0: it->direction = 3; break;
	    case 1: it->direction = 2; break;
	    case 2: it->direction = 1; break;
	    case 3: it->direction = 0; break;
	  }
	  break;

        case '-' :
          switch(it->direction){
	    case 1: break;
	    case 3: break;
	    default: it->direction = 1; new_beam = new Beam(it->x, it->y, 3); break;
	  }
	  break;

        case '|' :
          switch(it->direction){
	    case 0: break;
	    case 2: break;
	    default: it->direction = 0; new_beam = new Beam(it->x, it->y, 2); break;
	  }
	  break;

      }

      bool occupied = false;

      switch(it->direction){
        case 0: if(has_beam_horizontal[it->y][it->x]) occupied = true; break;
        case 1: if(has_beam_vertical[it->y][it->x])   occupied = true; break;
        case 2: if(has_beam_horizontal[it->y][it->x]) occupied = true; break;
        case 3: if(has_beam_vertical[it->y][it->x])   occupied = true; break;
      }

      if(new_beam){
        switch(new_beam->direction){
          case 0: if(has_beam_horizontal[it->y][it->x]) new_beam = nullptr; break;
          case 1: if(has_beam_vertical[it->y][it->x])   new_beam = nullptr; break;
          case 2: if(has_beam_horizontal[it->y][it->x]) new_beam = nullptr; break;
          case 3: if(has_beam_vertical[it->y][it->x])   new_beam = nullptr; break;
        }
      }

      if(it->x < 0 || it->y < 0 || it->x >= n_x || it->y >= n_y){

        beams.erase(it++);

	new_beam = nullptr;

      }
      else {
        
	if(new_beam)
          beams.insert(it, *new_beam);
        
	if(occupied)
          beams.erase(it++);
	else
          ++it;

      }

    }

  }


};

int main(){

  Grid grid("example.txt");
  
  grid.propagate_beams();
  
}
