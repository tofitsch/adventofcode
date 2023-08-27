#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#define N_STEPS 1000

using namespace std;

struct Moon{

  int id;
  vector<int> pos;
  vector<int> vel;

  Moon(string, int);

  void apply_velocity();
  void apply_gravity(Moon &);
  int energy();

  //XXX
  void print(){
    
    for(int p : pos) cout<<p<<" ";
    cout<<" | ";
    for(int v : vel) cout<<v<<" ";
    cout<<" | "<<energy()<<endl;

  }

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

int Moon::energy(){
  
  int e_pot = 0;
  int e_kin = 0;

  for(int i=0; i<pos.size(); i++){
    
    e_pot += abs(pos[i]);
    e_kin += abs(vel[i]);

  }
  
  return e_pot * e_kin;

}

int main(){
  
  vector<Moon> moons;

  ifstream in_file("input.txt");

  for(string line; getline(in_file, line); moons.emplace_back(line, moons.size())) {}

  for(int step=1; step<=N_STEPS; step++){

    for(int i=0; i<moons.size(); i++){
      for(int j=i+1; j<moons.size(); j++){
        
        moons[i].apply_gravity(moons[j]);
        
      }
    }

    for(Moon &moon : moons) moon.apply_velocity();

    for(Moon &moon : moons) moon.print();
    cout<<endl;

  }

  int e_tot = 0;

  for(Moon &moon : moons) e_tot += moon.energy();

  cout<<e_tot<<endl;

}

