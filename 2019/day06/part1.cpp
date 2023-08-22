#include<iostream>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

int main(){
  
  ifstream in_file("input.txt");

  map<string, string> M_of_m;

  string line, m, M;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);
    
    getline(line_stream, M, ')');
    getline(line_stream, m, ')');

    M_of_m[m] = M;

  }

  int ctr = 0;

  for(auto map_element : M_of_m){

    m = map_element.first;

    while(m != "COM"){

      m = M_of_m[m];

      ctr++;

    }

  }

  cout<<ctr<<endl;

}
