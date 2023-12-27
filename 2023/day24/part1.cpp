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

  bool in_future_direction(int x , int y){
    
    return ( ( (x > p0[X]) == (p1[X] > p0[X]) ) && ( (y > p0[Y]) == (p1[Y] > p0[Y]) ) );

  }

};

bool intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int & x, int & y){
  
  int denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

  if(denominator == 0)
    return false;

  int numerator_x = (x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4);
  int numerator_y = (x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4);

  x = numerator_x / denominator;
  y = numerator_y / denominator;

  return true;
  
}

int main(){

  string line;

  ifstream in_file("example.txt");

  vector<Hailstone> hailstones;

  while(getline(in_file, line))
    hailstones.push_back(Hailstone(line));

  int x, y;

  int ctr = 0;

  int min = 7;
  int max = 27;

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
