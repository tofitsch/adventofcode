#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  int 
    pos = 50,
    sum = 0;

  while (getline(in_file, line)) {
    
    string subline = line;

    subline.erase(0, 1);

    if (line[0] == 'R')
      pos += stoi(subline);
    else
      pos -= stoi(subline);

    while (pos < 0)
      pos += 100;

    while (pos > 99)
      pos -= 100;

    if (pos == 0)
      sum++;

  }

  cout << sum << endl;

}
