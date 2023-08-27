#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

#define N_STEPS 1000

using namespace std;

struct Moon{

  int id;
  vector<int> pos;
  vector<int> vel;

  Moon(string, int);

  void apply_velocity();
  void apply_gravity(Moon &);

};

Moon::Moon(string line, int n){
    
    id = n;
    
    string field;

    stringstream line_stream(line);

    while(getline(line_stream, field, ',')){
      
      pos.push_back(stoi(field.substr(3, field.length() - 2)));
      vel.push_back(0);

    }

}

void Moon::apply_gravity(Moon &m){
  
  for(int i=0; i<pos.size(); i++){
    
    if(pos[i] < m.pos[i]){vel[i]++; m.vel[i]--;}
    if(pos[i] > m.pos[i]){vel[i]--; m.vel[i]++;}

  }

}

void Moon::apply_velocity(){

  for(int i=0; i<pos.size(); i++) pos[i] += vel[i];

}

template<class T>
bool arr_equal_along_row(T *a, T *b, const int &n_rows, const int &n_cols, int &row){
  
  for(int i=0; i<n_rows; i++){

    int idx = i * n_rows + row;

    if(a[idx] != b[idx]) return false;

  }

  return true;

}

int gcd(long a, long b){return b == 0 ? a : gcd(b, a % b);}

int lcm(long a, long b){return (a * b) / gcd(a, b);}

int main(){
  
  vector<Moon> moons;

  ifstream in_file("example.txt");

  for(string line; getline(in_file, line); moons.emplace_back(line, moons.size())) {}

  const int n_dim = moons[0].pos.size();
  const int n_moons = moons.size();

  int periodicity[n_dim] = {};

  pair<int, int> initial_state[n_moons][n_dim];
  pair<int, int> current_state[n_moons][n_dim];

  for(int d=0; d<n_dim; d++)
    for(int m=0; m<n_moons; m++)
       initial_state[m][d] = {moons[m].pos[d], moons[m].vel[d]};

  int step = 0;

  while(true){

    step++;

    for(int i=0; i<moons.size(); i++){
      for(int j=i+1; j<moons.size(); j++){
        
        moons[i].apply_gravity(moons[j]);
        
      }
    }

    for(Moon &moon : moons) moon.apply_velocity();

    for(int d=0; d<n_dim; d++){
      
      if(periodicity[d] > 0) continue;

      for(int m=0; m<n_moons; m++)
         current_state[m][d] = {moons[m].pos[d], moons[m].vel[d]};

      if(arr_equal_along_row(*current_state, *initial_state, n_dim, n_moons, d)){
        
        cout<<d<<" "<<step<<endl;
        periodicity[d] = step;

      }

    }

    if(find(periodicity, periodicity + n_dim, 0) == periodicity + n_dim) break;

  }

  long lowest_common_multiple = 1;

  for(int d=0; d<n_dim; d++)
    lowest_common_multiple = lcm(lowest_common_multiple, periodicity[d]);

  cout<<lowest_common_multiple<<endl;

}

