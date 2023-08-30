#include<iostream>
#include<fstream>
#include<iterator>

#define N_PHASES 100
#define N_OUT_CHAR 8
#define N_OFFSET_CHAR 7
#define PERIODICITY 10000

using namespace std;

int main(){
  
  const int pattern_size = 4;
  
  const short pattern[pattern_size] = {0, 1, 0, -1};
  
  ifstream in_file("input.txt");

  string line;
  
  getline(in_file, line);

  int offset = stoi(line.substr(0, N_OFFSET_CHAR));

  const int line_size = line.size();
  const int data_size = line_size * PERIODICITY - offset;

  if(offset < line_size * PERIODICITY / 2){

    cout<<"ERROR: Method not valid for this input. Offset too small."<<endl;
    exit(1);

  }

  short data[data_size];

  for(int i=0; i<data_size; i++)
    data[i] = line[(offset + i) % line_size] - '0';

  for(int p=0; p<N_PHASES; p++)
    for(int i=data_size - 2; i>=0; i--)
     data[i] = abs(data[i] + data[i + 1]) % 10;

  for(int i=0; i<N_OUT_CHAR; i++) cout<<data[i];
  cout<<endl;

}
