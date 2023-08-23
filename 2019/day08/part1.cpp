#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

#define X 25
#define Y 6

int main(){
  
  ifstream in_file("input.txt");
  
  string line;

  getline(in_file, line);

  vector<short> zeros = {0, 0, 0};

  vector<vector<short>> digits_in_layer;

  unsigned int pixel_ctr = 0;

  for(char c : line){
    
    if(pixel_ctr % (X * Y) == 0) digits_in_layer.push_back(zeros);

    digits_in_layer.back()[c - '0']++;

    pixel_ctr++;

  }

  int fewest_zeros = (int)1e10;
  int fewest_zeros_layer = 0;

  for(int i=0; i<digits_in_layer.size() - 1; i++){
    
    if(digits_in_layer[i][0] < fewest_zeros){

      fewest_zeros = digits_in_layer[i][0];
      fewest_zeros_layer = i;
    }

  }

  cout<<digits_in_layer[fewest_zeros_layer][1] * digits_in_layer[fewest_zeros_layer][2]<<endl;
  
}
