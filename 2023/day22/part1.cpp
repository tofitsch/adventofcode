#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

enum Coordinates : short {NONE, X, Y, Z};

constexpr short hash_pair(short a, short b){
  return a * 4 + b;
}

struct Brick{
  
  int id;
  
  int front[4], back[4];

  int * z_top, * z_bot;

  unsigned short alignment = Z;

  bool removable = true;

  vector<Brick *> bricks_above, bricks_below;

  Brick(string line, int id) : id(id) {
    
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

  void calc_top_bot(){

    if(front[Z] > back[Z]){

      z_top = & front[Z];
      z_bot = & back[Z];

    }
    else{

      z_top = & back[Z];
      z_bot = & front[Z];

    }

  }

  static bool lower_z_bot(const Brick * a, const Brick * b){

    return * a->z_bot < * b->z_bot;

  }

  static bool lower_z_top(const Brick * a, const Brick * b){

    return * a->z_top < * b->z_top;

  }

  void let_fall(){
    
    * z_top -= * z_bot - 1;
    * z_bot = 1;

    if(bricks_below.size() > 0){

      sort(bricks_below.begin(), bricks_below.end(), lower_z_top);
     
      * z_top += * bricks_below.back()->z_top;
      * z_bot += * bricks_below.back()->z_top;

    }
    
  }

};

void get_bricks(vector<Brick *> & bricks){

  string line;

  ifstream in_file("input.txt");

  int id = 0;

  while(getline(in_file, line)){

    bricks.push_back(new Brick(line, id));

    id++;

  }

  for(Brick * brick : bricks)
    brick->calc_top_bot();

}

bool is_in_range(int a, int b0, int b1){
  
  if(b1 > b0)
    return a >= b0 && a <= b1;
  else
    return a <= b0 && a >= b1;

}

bool ranges_overlap(int a0, int a1, int b0, int b1){
  
  return is_in_range(a0, b0, b1) || is_in_range(a1, b0, b1) || is_in_range(b0, a0, a1) || is_in_range(a1, b0, b1);
  
}

void calc_overlaps(vector<Brick *> & bricks){

  for(Brick * a : bricks){
    for(Brick * b : bricks){

      if(* a->z_bot >= * b->z_bot)
        continue;

      bool overlap = false;

      switch(hash_pair(a->alignment, b->alignment)){

        case hash_pair(X, X):
          overlap = (a->front[Y] == b->front[Y]) && ranges_overlap(a->front[X], a->back[X], b->front[X], b->back[X]);
          break;

        case hash_pair(Y, Y):
          overlap = (a->front[X] == b->front[X]) && ranges_overlap(a->front[Y], a->back[Y], b->front[Y], b->back[Y]);
          break;

        case hash_pair(Z, Z):
          overlap = (a->front[X] == b->front[X] && a->front[Y] == b->front[Y]);
          break;

        case hash_pair(X, Y):
          overlap = is_in_range(a->front[Y], b->front[Y], b->back[Y]) && is_in_range(b->front[X], a->front[X], a->back[X]);
          break;

        case hash_pair(Y, X):
          overlap = is_in_range(a->front[X], b->front[X], b->back[X]) && is_in_range(b->front[Y], a->front[Y], a->back[Y]);
          break;

        case hash_pair(X, Z):
          overlap = (b->front[Y] == a->front[Y]) && is_in_range(b->front[X], a->front[X], a->back[X]);
          break;

        case hash_pair(Y, Z):
          overlap = (b->front[X] == a->front[X]) && is_in_range(b->front[Y], a->front[Y], a->back[Y]);
          break;

        case hash_pair(Z, X):
          overlap = (a->front[Y] == b->front[Y]) && is_in_range(a->front[X], b->front[X], b->back[X]);
          break;

        case hash_pair(Z, Y):
          overlap = (a->front[X] == b->front[X]) && is_in_range(a->front[Y], b->front[Y], b->back[Y]);
          break;

      };

      if(overlap){

        a->bricks_above.push_back(b);
        b->bricks_below.push_back(a);

      }

    }
  }

}

int count_removobale_bricks(vector<Brick *> & bricks){

  for(Brick * brick : bricks){

    int n_supports = 0;

    Brick * support = nullptr;

    for(Brick * brick_below : brick->bricks_below){
      if(* brick_below->z_top == * brick->z_bot - 1){

        support = brick_below;

        n_supports++;

      }
    }

    if(n_supports == 1)
      support->removable = false;

  }

  int n_removable = 0; 

  for(Brick * brick : bricks)
    if(brick->removable)
      n_removable++;

  return n_removable;

}

int main(){

  vector<Brick *> bricks;

  get_bricks(bricks);

  sort(bricks.begin(), bricks.end(), Brick::lower_z_bot);

  calc_overlaps(bricks);

  for(Brick * brick : bricks)
   brick->let_fall(); 

  cout << count_removobale_bricks(bricks) << endl;

}
