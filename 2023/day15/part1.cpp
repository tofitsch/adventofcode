#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int str_hash(string str){
  
  int h = 0;

  for(char & c : str){

    h += (int) c;
    h *= 17;
    h %= 256;

  }

  return h;

}

int main(){
  
  string line, field;

  ifstream in_file("input.txt");
  
  getline(in_file, line);

  stringstream line_stream(line);

  long sum = 0;

  while(getline(line_stream, field, ','))
    sum += str_hash(field);

  cout << sum << endl;

}
