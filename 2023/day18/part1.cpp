#include<iostream>
#include<fstream>
#include<sstream>
#include<limits>
#include<vector>

using namespace std;

struct Instruction{

  char direction;
  int length;

  Instruction(string & line){
     
     string field;

     stringstream line_stream(line);

     getline(line_stream, field, ' ');

     direction = field[0];

     getline(line_stream, field, ' ');

     length = stoi(field);

  }

};

struct Coordinate{

  int y = 0;
  int x = 0;

  void apply(Instruction & instruction){
    
    switch(instruction.direction){

      case 'U': y -= instruction.length; break;
      case 'D': y += instruction.length; break;
      case 'L': x -= instruction.length; break;
      case 'R': x += instruction.length; break;

    };

  }

};

int shoe_lace_formula(vector<Coordinate> vertices){
  
  int sum = 0;

  vertices.push_back(vertices[0]);

  for(int i=0; i<vertices.size() - 1; i++)
    sum += vertices.at(i).x * vertices.at(i + 1).y - vertices.at(i + 1).x * vertices.at(i).y;

  vertices.pop_back();

  return sum / 2;

}

int picks_theorem(int area, int circumference){
  
  return area - circumference / 2 + 1 + circumference;

}

int main(){
  
  vector<Instruction> instructions;

  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line))
    instructions.push_back(Instruction(line));

  vector<Coordinate> vertices;

  Coordinate coord;

  int circumference = 0;

  for(Instruction & instruction : instructions){
    
    vertices.push_back(coord);

    circumference += instruction.length;

    coord.apply(instruction);


  }

  int area = shoe_lace_formula(vertices);
  
  cout << picks_theorem(area, circumference) << endl;

}
