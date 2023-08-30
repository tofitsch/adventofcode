#include<iostream>
#include<fstream>
#include<iterator>

#define N_PHASES 100
#define N_OUT_CHAR 8

using namespace std;

short apply_pattern(const short *data, const int &data_size, const short* pattern, const int & pattern_size, const int &pos){
 
  short sum = 0;

  for(int i=0; i<data_size; i++)
    sum += data[i] * pattern[((i + 1) / (pos + 1)) % pattern_size];

  return abs(sum % 10);

}

int main(){
  
  const int pattern_size = 4;
  
  const short pattern[pattern_size] = {0, 1, 0, -1};
  
  ifstream in_file("input.txt");

  string line;
  
  getline(in_file, line);

  const int data_size = line.size();

  short data[data_size];
  short new_data[data_size];

  for(int i=0; i<data_size; i++) data[i] = line[i] - '0';

  for(int p=0; p<N_PHASES; p++){

    for(int i=0; i<data_size; i++) 
      new_data[i] = apply_pattern(data, data_size, pattern, pattern_size, i);

    for(int i=0; i<data_size; i++) 
      data[i] = new_data[i];

  }

  for(int i=0; i<N_OUT_CHAR; i++) cout<<data[i];
  cout<<endl;

}
