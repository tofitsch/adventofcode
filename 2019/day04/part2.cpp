#include<iostream>
#include<fstream>
#include<sstream>

#define NUM_DIGITS 6

using namespace std;

int main(){

  ifstream in_file("input.txt");

  string line, field;

  getline(in_file, line);

  stringstream line_stream(line);

  getline(line_stream, field, '-');

  int min = stoi(field);

  getline(line_stream, field, '-');

  int max = stoi(field);

  int ctr = 0;

  for(int i=min; i<=max; i++){

    char num_str[NUM_DIGITS + 1];
    snprintf(num_str, NUM_DIGITS + 1, "%d", i);

    bool valid = false;
    
    for(int i=1; i<NUM_DIGITS; i++){
      
      if(num_str[i] < num_str[i-1]){

        valid = false;
        break;

      }

      if(num_str[i] == num_str[i-1]
         && (i < 2 || num_str[i] != num_str[i-2])
         && (i == NUM_DIGITS || num_str[i] != num_str[i+1]) 
        ) valid = true;

    }

    if(valid) ctr++;
    
  }

  cout<<ctr<<endl;

}
