#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<algorithm>

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

  vector<string> chain_san;

  m = "SAN";

  while(m != "COM"){

    chain_san.push_back(m);

    m = M_of_m[m];

  }

  m = "YOU";

  vector<string>::iterator crossing = chain_san.end();

  int ctr = 0;

  while(crossing == chain_san.end()){

    crossing = find(chain_san.begin(), chain_san.end(), m);

    m = M_of_m[m];

    ctr++;

  }

  cout<<ctr + crossing - chain_san.begin() - 3<<endl;

}
