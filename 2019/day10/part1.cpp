#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct Coord {

  int x;
  int y;

  Coord(int X, int Y) : x(X), y(Y) {}

};

int gcd(int a, int b) {

  while(b != 0){

    int temp = b;
    b = a % b;
    a = temp;

  }

  return a;

}

int main(){

  vector<Coord> asteroids;
  vector<vector<bool>> map;
   
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

  for(auto a : asteroids){
    
    int n_in_sight = 0;

    for(auto b : asteroids){
      
      if(a.x == b.x && a.y == b.y) continue;

      bool is_obstructed = false;

      int dx = abs(b.x - a.x);
      int dy = abs(b.y - a.y);

      if(dx > dy){

        for(int i=dx-1; i>0; i--){
          
          if((i * dy) %  dx != 0) continue;

          int x = a.x + (dx - i) * (a.x > b.x ? -1 : 1);
          int y = a.y + (dy - i * dy / dx) * (a.y > b.y ? -1 : 1);

          cout<<"A "<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<x<<" "<<y<<endl;

          if(map[x][y]){

            is_obstructed = true;
            break;

          }

        }

      }
      else{

        for(int i=dy-1; i>0; i--){
          
          if((i * dx) %  dy != 0) continue;

          int x = a.x + (dx - i * dx / dy) * (a.x > b.x ? -1 : 1);
          int y = a.y + (dy - i) * (a.y > b.y ? -1 : 1);

          cout<<"B "<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<x<<" "<<y<<endl;

          if(map[x][y]){

            is_obstructed = true;
            break;

          }

        }

      }

      if(!is_obstructed) n_in_sight++;

    }

    cout<<n_in_sight<<endl;

    if(n_in_sight > max_in_sight) max_in_sight = n_in_sight;

  }

  cout<<max_in_sight<<endl;

}
