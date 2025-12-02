#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  int pos = 50, ctr = 0;

  while(getline(in_file, line)){


    string subline = line;

    subline.erase(0, 1);

    int increment = (line[0] == 'R') ? 1 : -1;

    int dist = stoi(subline);

    while (dist-- > 0){

      pos += increment;

      if (pos < 0)
        pos += 100;

      if (pos > 99)
        pos -= 100;

      if (pos == 0)
        ctr++;

    }

  }

  cout << ctr << endl;

}
