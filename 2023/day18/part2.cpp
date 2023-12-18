#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

string directions_string = "RDLU";

struct Instruction{

  char direction;
  long length;

  Instruction(string & line){
     
     string length_string = line.substr(line.length() - 7,  5);

     stringstream length_stream;

     length_stream << std::hex << length_string;
     length_stream >> length;

     direction = directions_string[line[line.length() - 2] - '0'];

  }

};

struct Coordinate{

  long y = 0;
  long x = 0;

  void apply(Instruction & instruction){
    
    switch(instruction.direction){

      case 'U': y -= instruction.length; break;
      case 'D': y += instruction.length; break;
      case 'L': x -= instruction.length; break;
      case 'R': x += instruction.length; break;

    };

  }

};

long shoe_lace_formula(vector<Coordinate> vertices){
  
  long sum = 0;

  vertices.push_back(vertices[0]);

  for(int i=0; i<vertices.size() - 1; i++)
    sum += vertices.at(i).x * vertices.at(i + 1).y - vertices.at(i + 1).x * vertices.at(i).y;

  vertices.pop_back();

  return abs(sum / 2);

}

long picks_theorem(long area, long circumference){
  
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

  long circumference = 0;

  for(Instruction & instruction : instructions){
    
    vertices.push_back(coord);

    circumference += instruction.length;

    coord.apply(instruction);


  }

  long area = shoe_lace_formula(vertices);
  
  cout << picks_theorem(area, circumference) << endl;

}
