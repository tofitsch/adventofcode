#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

enum Coordinates : short {NONE, X, Y, Z};

constexpr short hash_pair(short a, short b){
  return a * 7 + b;
}

struct Brick{
  
  int front[4], back[4];

  short alignment;

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
        alignment = (front[i] > back[i]) ? i : -i;

    }

  }

};

void get_bricks(vector<Brick> & bricks){

  string line;

  ifstream in_file("example.txt");

  while(getline(in_file, line))
    bricks.push_back(Brick(line));

}

void set_relations(Brick & a, Brick & b){

  if(a.front[Z] < b.front[Z]){

    a.bricks_above.push_back(& b);
    b.bricks_below.push_back(& a);

  }
  else{

    a.bricks_below.push_back(& b);
    b.bricks_above.push_back(& a);

  }
  
}

bool ranges_overlap(int a0, int a1, int b0, int b1){
  
  if(a1 > a0)
    return (b0 >= a0 && b0 <= a1) || (b1 >= a0 && b1 <= a1);
  else
    return (b0 <= a0 && b0 >= a1) || (b1 <= a0 && b1 >= a1);
  
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

        default : overlap = false;
      };

      if(overlap)
        set_relations(a, b);

    }
  }

}

int main(){

  vector<Brick> bricks;

  get_bricks(bricks);

  calc_overlaps(bricks);

}
