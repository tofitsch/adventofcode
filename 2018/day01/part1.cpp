#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  int sum = 0;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);

    while(getline(line_stream, field, ' '))
      sum += stoi(field);

  }

  cout << sum << endl;

}
