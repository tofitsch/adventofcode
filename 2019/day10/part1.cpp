#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector<vector<bool>> map;
vector<Coord> asteroids;

struct Coord {

  int x;
  int y;

  Coord(int X, int Y) : x(X), y(Y) {}

  bool can_see(Coord);

};

bool Coord::can_see(Coord c){

  if(x == c.x && y == c.y) return false;

  int dx = abs(c.x - x);
  int dy = abs(c.y - y);

  int dg = dx > dy ? dx : dy;
  int ds = dx < dy ? dx : dy;

  for(int i=dg-1; i>0; i--){
    
    if((i * ds) % dg != 0) continue;

    int X = x + (dx - (dx > dy ? i : (i * ds) / dg)) * (x > c.x ? -1 : 1);
    int Y = y + (dy - (dy > dx ? i : (i * ds) / dg)) * (y > c.y ? -1 : 1);

    if(map[X][Y]) return false;

  }

  return true;

}

int main(){

  ifstream in_file("input.txt");

  string line;

  int x = 0, y = 0;

  while(getline(in_file, line)){

    map.push_back({});
    
    for(char c : line){

      if(c == '#') asteroids.push_back({x, y});

      map.back().push_back(c == '#');

      y++;

    }

    y = 0;
    x++;

  }

  int max_in_sight = 0;

  for(auto a : asteroids){
    
    int n_in_sight = 0;

    for(auto b : asteroids){
      
      if(a.can_see(b)) n_in_sight++;
      
    }

    if(n_in_sight > max_in_sight) max_in_sight = n_in_sight;

  }

  cout<<max_in_sight<<endl;

}
