#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<boost/multiprecision/cpp_int.hpp>

#define ll boost::multiprecision::cpp_int

using namespace std;

enum Coordinates : short {X, Y, Z};

struct Hailstone{

  ll p0[3], p1[3];

  Hailstone(string line){
    
    size_t split_pos = line.find('@');

    stringstream stream_p(line.substr(0, split_pos - 1));
    stringstream stream_v(line.substr(split_pos + 2, line.length() - split_pos - 1));

    string field;

    for(int i=0; i<3; i++){

      getline(stream_p, field, ',');
      p0[i] = stol(field);

      getline(stream_v, field, ',');
      p1[i] = p0[i] + stol(field);

    }

  }

};

bool intersect(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4, ll & x, ll & y){

  ll denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

  if(denominator == 0)
    return false;

  ll numerator_x = (x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4);
  ll numerator_y = (x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4);

  x = (ll) numerator_x / denominator;
  y = (ll) numerator_y / denominator;

  return true;
  
}

bool is_solution(vector<Hailstone> & hailstones, ll & x, ll & y, ll dx, ll dy, bool y_is_z){

  ll x0, y0;

  Hailstone & a = hailstones[0];

  for(int i=1; i<hailstones.size(); i++){

      Hailstone & b = hailstones[i];

      if(y_is_z){

        if(! intersect(a.p0[X], a.p0[Z], a.p1[X] - dx, a.p1[Z] - dy, b.p0[X], b.p0[Z], b.p1[X] - dx, b.p1[Z] - dy, x, y))
          continue;

      }
      else{

        if(! intersect(a.p0[X], a.p0[Y], a.p1[X] - dx, a.p1[Y] - dy, b.p0[X], b.p0[Y], b.p1[X] - dx, b.p1[Y] - dy, x, y))
          continue;

      }

      if(i == 1){

        x0 = x;
        y0 = y;

      }
      else if(x != x0 || y != y0)
        return false;

  }

  return true;

}

int main(){

  string line;

  ifstream in_file("input.txt");

  vector<Hailstone> hailstones;

  while(getline(in_file, line))
    hailstones.push_back(Hailstone(line));

  bool found = false;

  ll d_min = -1000;
  ll d_max = 1000;

  ll x, y, z;

  for(ll dx=d_min; dx<=d_max; dx++){
    for(ll dy=d_min; dy<=d_max; dy++){
      if(is_solution(hailstones, x, y, dx, dy, false)){
        for(ll dz=d_min; dz<=d_max; dz++){
          if(is_solution(hailstones, x, z, dx, dz, true)){

            cout << x + y + z << endl;

            exit(0);

          }
        }
      }
    }
  }

}
