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

  bool in_future_direction(ll x , ll y){
    
    return (x > p0[X]) == (p1[X] > p0[X]);

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

int main(){

  string line;

  ll min = 200000000000000;
  ll max = 400000000000000;

  ifstream in_file("input.txt");

  vector<Hailstone> hailstones;

  while(getline(in_file, line))
    hailstones.push_back(Hailstone(line));

  ll x, y;

  int ctr = 0;

  for(int i=0; i<hailstones.size(); i++){

    Hailstone & a = hailstones[i];

    for(int j=i + 1; j<hailstones.size(); j++){

        Hailstone & b = hailstones[j];

        if(intersect(a.p0[X], a.p0[Y], a.p1[X], a.p1[Y], b.p0[X], b.p0[Y], b.p1[X], b.p1[Y], x, y))
          if(x >= min && x <= max && y >= min && y <= max)
            if(a.in_future_direction(x, y) && b.in_future_direction(x, y))
              ctr++;

    }

  }

  cout << ctr << endl;

}
