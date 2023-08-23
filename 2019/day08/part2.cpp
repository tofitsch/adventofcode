#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

#define X 25
#define Y 6

int main(){
  
  ifstream in_file("input.txt");

  short img[X][Y] = {};
  
  string line;

  getline(in_file, line);

  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int z = 0;

  for(int col=0; col<Y; col++)
    for(int row=0; row<X; row++)
      img[row][col] = 2;

  for(char c : line){
    
    if(img[x][y] == 2) img[x][y] = c - '0';
    
    x++;
    
    if(x % X == 0){x = 0; y++;}
    if(y % Y == 0){y = 0; z++;}

  }

  char decode[3] = {'.', '#', ' '};

  for(int col=0; col<Y; col++){

    for(int row=0; row<X; row++)
      cout<<decode[img[row][col]];

    cout<<endl;

  }
  
}
