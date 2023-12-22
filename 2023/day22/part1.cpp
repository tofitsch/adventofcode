#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

enum Coordinates : short {NONE, X, Y, Z};

constexpr short hash_pair(short a, short b){
  return a * 4 + b;
}

struct Brick{
  
  int front[4], back[4];

  unsigned short alignment;

  vector<Brick *> bricks_above, bricks_below;

  Brick(string line){
    
    string field;
    
    size_t tilde_pos = line.find('~');

    stringstream a_stream(line.substr(0, tilde_pos));
    stringstream b_stream(line.substr(tilde_pos + 1, line.length() - tilde_pos - 1));

    for(int i=1; i<=3; i++){

      getline(a_stream, field, ',');

      front[i] = stoi(field);
      
      getline(b_stream, field, ',');

      back[i] = stoi(field);

      if(front[i] != back[i])
        alignment = i;

    }

  }

};

void get_bricks(vector<Brick> & bricks){

  string line;

  ifstream in_file("example.txt");

  while(getline(in_file, line))
    bricks.push_back(Brick(line));

}

void set_overlap(Brick & a, Brick & b){

  if(a.front[Z] < b.front[Z]){

    a.bricks_above.push_back(& b);
    b.bricks_below.push_back(& a);

  }
  else{

    a.bricks_below.push_back(& b);
    b.bricks_above.push_back(& a);

  }
  
}

bool is_in_range(int a, int b0, int b1){
  
  if(b1 > b0)
    return a >= b0 && a <= b1;
  else
    return a <= b0 && a >= b1;

}

bool ranges_overlap(int a0, int a1, int b0, int b1){
  
  return is_in_range(a0, b0, b1) || is_in_range(a1, b0, b1);
  
}

void calc_overlaps(vector<Brick> & bricks){

  for(Brick & a : bricks){
    for(Brick & b : bricks){
      
      if(& a == & b)
        continue;

      bool overlap = false;

      switch(hash_pair(a.alignment, b.alignment)){

        case hash_pair(X, X):
          overlap = ranges_overlap(a.front[X], a.back[X], b.front[X], b.back[X]);
          break;

        case hash_pair(Y, Y):
          overlap = ranges_overlap(a.front[Y], a.back[Y], b.front[Y], b.back[Y]);
          break;

        case hash_pair(Z, Z):
          overlap = (a.front[X] == b.front[X] && a.front[Y] == b.front[Y]);
          break;

        case hash_pair(X, Y):
          overlap = is_in_range(a.front[Y], b.front[Y], b.back[Y]) && is_in_range(b.front[X], a.front[X], a.back[X]);
          break;

        case hash_pair(Y, X):
          overlap = is_in_range(a.front[X], b.front[X], b.back[X]) && is_in_range(b.front[Y], a.front[Y], a.back[Y]);
          break;

        case hash_pair(X, Z):
          overlap = (b.front[Y] == a.front[Y]) && is_in_range(b.front[X], a.front[X], a.back[X]);
          break;

        case hash_pair(Y, Z):
          overlap = (b.front[X] == a.front[X]) && is_in_range(b.front[Y], a.front[Y], a.back[Y]);
          break;

        case hash_pair(Z, X):
          overlap = (a.front[Y] == b.front[Y]) && is_in_range(a.front[X], b.front[X], b.back[X]);
          break;

        case hash_pair(Z, Y):
          overlap = (a.front[X] == b.front[X]) && is_in_range(a.front[Y], b.front[Y], b.back[Y]);
          break;

        default:
          overlap = false;

      };

      if(overlap)
        set_overlap(a, b);

    }
  }

}

int main(){

  vector<Brick> bricks;

  get_bricks(bricks);

  calc_overlaps(bricks);

}
