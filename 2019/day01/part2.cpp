#include<iostream>
#include<fstream>

using namespace std;

int main(){
  
  int fuel, sum = 0;

  ifstream in_file("input.txt");

  while(in_file >> fuel){
    
    while(true){

      fuel = fuel / 3 - 2;

      if(fuel <= 0) break;

      sum += fuel;

    }

  }

  cout<<sum<<endl;

}
