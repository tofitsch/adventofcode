#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

class Coordinate{

  public:
    
    int x, y;

    Coordinate(int X, int Y){

      x = X;
      y = Y;

    }

    pair<int, int> xy(){return {x, y};}

    void translate(string direction){
      
      if(direction == "U") y++;
      if(direction == "R") x++;
      if(direction == "D") y--;
      if(direction == "L") x--;

    }

};

vector<Coordinate> get_cable_coordinates(ifstream& in_file){
  
  Coordinate origin(0, 0);
  
  vector<Coordinate> cable = {origin};

  string line, field;

  getline(in_file, line);

  stringstream line_stream(line);

  while(getline(line_stream, field, ',')){
    
    string direction = field.substr(0, 1);
    int length = stoi(field.substr(1));

    for(int i=0; i<length; i++){
      
      Coordinate new_coord = cable.back();

      new_coord.translate(direction);

      cable.push_back(new_coord);

    }

  }

  return cable;

}

int main(){
  
  ifstream in_file("input.txt");

  vector<Coordinate> cable[2];

  cable[0] = get_cable_coordinates(in_file);
  cable[1] = get_cable_coordinates(in_file);

  vector<int> crossing_diatances;

  for(Coordinate c1 : cable[0]){
    for(Coordinate c2 : cable[1]){
      
      cout<<c1.x<<" "<<c1.y<<" | "<<c2.x<<" "<<c2.y<<endl;
      
      if(c2.x == 0 && c2.y == 0) continue;

      if(c1.xy() == c2.xy()) crossing_diatances.push_back(abs(c1.x) + abs(c1.y));

    }
  }

  sort(crossing_diatances.begin(), crossing_diatances.end());

  cout<<crossing_diatances[0]<<endl;

}
