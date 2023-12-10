#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

bool is_one_of(char c, string str){

  for(char & s : str)
    if(c == s)
      return true;

  return false;

}

struct Grid{
  
  vector<string> lines;
  vector<string> tile_types;

  int n_x, n_y, x, y, start_x = 0, start_y = 0, facing = 0;

  void turn_right(){
    
    facing++;

    if(facing == 4)
      facing = 0;

  }

  void turn_left(){
    
    facing--;

    if(facing == -1)
      facing = 3;

  }

  bool facing_valid(){
    
    switch(facing){
      case 0: return is_one_of(facing_at(), "7F|S");
      case 1: return is_one_of(facing_at(), "7J-S");
      case 2: return is_one_of(facing_at(), "LJ|S");
      case 3: return is_one_of(facing_at(), "LF-S");
      default: return false;
    }
   
  }

  bool step(){
    
    tile_types[y][x] = '.';

    char *tile_left = tile_on_side(-1);
    char *tile_right = tile_on_side(1);

    if(tile_left && *tile_left != '.')
      *tile_left = 'L';

    if(tile_right && *tile_right != '.')
      *tile_right = 'R';

    switch(facing){
      case 0: y--; break;
      case 1: x++; break;
      case 2: y++; break;
      case 3: x--; break;
    }

    switch(at(x, y)){

      case '7':
        if(facing == 0)
	  turn_left();
	else
          turn_right();
	break;

      case 'L':
        if(facing == 3)
          turn_right();
	else
          turn_left();
	break;

      case 'J':
        if(facing == 2)
	  turn_right();
	else
          turn_left();
	break;

      case 'F':
        if(facing == 3)
          turn_left();
	else
          turn_right();
	break;

      case 'S':
        start();
        return false;

    }

    return true;

  }

  char *tile_on_side(int side){

    int at_facing = facing + side;

    if(at_facing == 4)
      at_facing = 0;

    if(at_facing == -1)
      at_facing = 3;

    int X = x;
    int Y = y;

    switch(at_facing){
      case 0: Y--; break;
      case 1: X++; break;
      case 2: Y++; break;
      case 3: X--; break;
    }

    if(X >= n_x || Y >= n_y || X < 0 || Y < 0)
      return nullptr;

    return & tile_types[Y][X];

  }

  char facing_at(){
    
    switch(facing){
      case 0: return at(x, y - 1);
      case 1: return at(x + 1, y);
      case 2: return at(x, y + 1);
      case 3: return at(x - 1, y);
      default: return ' ';
    }


  }

  char at(int x, int y){

    if(x >= n_x || y >= n_y || x < 0 || y < 0)
      return ' ';

    return lines[y][x];

  }

  void start(){
    
    x = start_x;
    y = start_y;

    while(!facing_valid())
      turn_right();

  }

  Grid(string in_file_name){

    string line;

    ifstream in_file(in_file_name);

    while(getline(in_file, line)){
      
      if(start_x == 0){

        size_t pos = line.find('S');
        
        if(pos != string::npos){
          
          start_x = (int) pos;
          start_y = lines.size();

        }

      }

      lines.push_back(line);
      tile_types.push_back(string(line.length(), ' '));

    }

    n_x = lines.back().length();
    n_y = lines.size();

    in_file.close();

  }

  void print(){
    
    const char* cout_highlight = "\033[1;31m";
    const char* cout_reset = "\033[0m";

    cout << x << " " << y << " " << facing << endl;

    for(int Y=0; Y<n_y; Y++){
      for(int X=0; X<n_x; X++)
        if(x == X && y == Y)
	  cout << cout_highlight << tile_types[Y][X] << cout_reset;
	else
	  cout << tile_types[Y][X];
      cout<<endl;
    }
    cout<<endl;

  }

};

int main(){

  Grid grid("input.txt");

  grid.start();

  int n_steps = 1;

  while(grid.step())
    n_steps++;

  grid.print();

  cout << n_steps / 2 << endl;

}
