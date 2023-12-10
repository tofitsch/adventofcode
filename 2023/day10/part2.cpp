#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

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

  void label_remaining_tiles(){

    vector<pair<int, int>> remaining_tiles;

    for(int Y=0; Y<n_y; Y++)
      for(int X=0; X<n_x; X++)
        if(tile_types[Y][X] == ' ')
	  remaining_tiles.push_back({Y, X});
    
    int ctr = 0;

    while(remaining_tiles.size() > 0){

     if(ctr == 100)
       break;
     ctr++;
      
      vector<int> tiles_that_got_labeled;

      for(int t=0; t<remaining_tiles.size(); t++){

        for(int n=0; n<4; n++){
	  
	  pair<int, int> coord = remaining_tiles[t];

	  char *neighbor_type = tile_neighbor(coord.second, coord.first, n);

          if(neighbor_type && is_one_of(*neighbor_type, "RL")){
	    
	    tile_types[coord.first][coord.second] = *neighbor_type;

	    tiles_that_got_labeled.push_back(t);

	    break;
	    
	  }

	}

      }

     sort(tiles_that_got_labeled.rbegin(), tiles_that_got_labeled.rend());

     for(int i : tiles_that_got_labeled)
       remaining_tiles.erase(remaining_tiles.begin() + i);

    }

    for(auto & coord :remaining_tiles)
      tile_types[coord.first][coord.second] = ' ';

  }

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

    char *tile_left = tile_neighbor(x, y, facing + 3);
    char *tile_right = tile_neighbor(x, y, facing + 1);

    if(tile_left && *tile_left == ' ')
      *tile_left = 'L';

    if(tile_right && *tile_right == ' ')
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

  char *tile_neighbor(int X, int Y, int side){
   
    switch(side % 4){
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

  grid.label_remaining_tiles();

  grid.print();

  cout << n_steps / 2 << endl;

}
