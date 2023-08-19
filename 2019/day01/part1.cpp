#include<iostream>
#include<fstream>

using namespace std;

int main(){
  
  int mass, sum = 0;

  ifstream in_file("input.txt");

  while(in_file >> mass) sum += mass / 3 - 2;

  cout<<sum<<endl;

}
