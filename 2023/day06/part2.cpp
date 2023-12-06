#include<iostream>
#include<fstream>
#include<sstream>
#include<regex>
#include<math.h>

using namespace std;

long read_line(ifstream & in_file){
  
  regex not_digit("[^0-9]");

  string line;

  getline(in_file, line);

  line = regex_replace(line, not_digit, "");

  return stol(line);

}

int main(){

  ifstream in_file("input.txt");

  long time = read_line(in_file);
  long dist = read_line(in_file);
  
  // time_left = (time - time_charging) * time_charging - dist
  // time_left = - time_charging^2 + time * time_charging - dist
  // y = a*x^2 + b*x + c
  // y: time_left
  // x: time_charging
  // a: -1.
  // b: time
  // c: -dist
  // roots of y: ( -b +- sqrt(b^2 - 4ac) ) / (2a)

  long root_pos = ( -time + sqrt(time*time - 4.*dist) ) / -2.;
  long root_neg = ( -time - sqrt(time*time - 4.*dist) ) / -2.;

  cout << root_neg - root_pos << endl;

}
