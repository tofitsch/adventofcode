#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

struct Coord {

  int x;
  int y;

  Coord(int X, int Y) : x(X), y(Y) {}

  bool can_see(Coord, vector<vector<bool>> &);

};

bool Coord::can_see(Coord c, vector<vector<bool>> &map){

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

  vector<vector<bool>> map;
  vector<Coord> asteroids;

  ifstream in_file("example.txt");

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
  vector<Coord>::iterator base_it;

  for(vector<Coord>::iterator it = asteroids.begin(); it != asteroids.end(); it++){
    
    int n_in_sight = 0;

    for(Coord b : asteroids)
      if(it->can_see(b, map)) n_in_sight++;

    if(n_in_sight > max_in_sight){

      max_in_sight = n_in_sight;
      base_it = it;

    }

  }

  int ctr = 0;

  while(asteroids.size() > 1){

    for(vector<Coord>::iterator it = asteroids.begin(); it != asteroids.end(); it++){

     if(it == base_it) continue;

     if(base_it->can_see(*it, map)){

       ctr++;

       cout<<ctr<<" "<<it->x<<" "<<it->y<<endl;
       
       if(ctr == 200){

         cout<<it->x * 100 + it->y<<endl;
//         exit(0);

       }

       map[it->x][it->y] = false;

       asteroids.erase(it);

     }

    }

  }

}
