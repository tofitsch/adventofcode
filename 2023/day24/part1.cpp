#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

enum Coordinates : short {X, Y, Z};

struct Hailstone{

  int p0[3], p1[3];

  Hailstone(string line){
    
    size_t split_pos = line.find('@');

    stringstream stream_p(line.substr(0, split_pos - 1));
    stringstream stream_v(line.substr(split_pos + 2, line.length() - split_pos - 1));

    string field;

    for(int i=0; i<3; i++){

      getline(stream_p, field, ',');
      p0[i] = stoi(field);

      getline(stream_v, field, ',');
      p1[i] = p0[i] + stoi(field);

    }

  }

};

bool intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float & x, float & y){
  
  int denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

  if(denominator == 0)
    return false;

  int numerator_x = (x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4);
  int numerator_y = (x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4);

  x = (float) numerator_x / denominator;
  y = (float) numerator_y / denominator;

  return true;
  
}


int main(){

  string line;

  ifstream in_file("example.txt");

  vector<Hailstone> hailstones;

  while(getline(in_file, line))
    hailstones.push_back(Hailstone(line));

  float x, y;

  int ctr = 0;

  for(Hailstone & a : hailstones)
    for(Hailstone & b : hailstones)
      if(& a != & b)
        if(intersect(a.p0[X], a.p0[Y], a.p1[X], a.p1[Y], b.p0[X], b.p0[Y], b.p1[X], b.p1[Y], x, y))
          if(x >= 7 && x <= 27 && y >= 7 && y <= 27){
            cout << x << " " << y << endl;
            ctr++;
          }

  cout << ctr << endl;

}
