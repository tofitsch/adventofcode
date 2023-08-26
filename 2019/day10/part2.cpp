#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

struct Coord {

  int x;
  int y;
  float angle_to_base;

  Coord(int X, int Y) : x(X), y(Y) {}

  bool can_see(Coord, vector<vector<bool>> &);
  void calc_angle_to_base(Coord *);

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

void Coord::calc_angle_to_base(Coord *base){

  float dx = x - base->x;
  float dy = y - base->y;

  float rad = sqrt(pow(dx, 2) + pow(dy, 2));

  float ang = acos(dx / rad);

  angle_to_base = dy < 0 ? -ang : ang;

}

bool compare_angles(const Coord &a, const Coord &b){return a.angle_to_base > b.angle_to_base;}

int main(){

  vector<vector<bool>> map;
  vector<Coord> asteroids;

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

  Coord base = *base_it;

  asteroids.erase(base_it);

  for(vector<Coord>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
    it->calc_angle_to_base(&base);

  sort(asteroids.begin(), asteroids.end(), compare_angles);

  int ctr = 0;

  while(asteroids.size() > 1){
    
    vector<vector<bool>> updated_map = map;

    for(vector<Coord>::iterator it = asteroids.begin(); it != asteroids.end();){

     if(base.can_see(*it, map)){

       ctr++;

       if(ctr == 200){

         cout<<it->y * 100 + it->x<<endl;
         exit(0);

       }

       updated_map[it->x][it->y] = false;

       asteroids.erase(it);

     }

     else it++;

    }

    map = updated_map;

  }

}
