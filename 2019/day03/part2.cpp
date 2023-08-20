#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

class Coordinate{

  public:
    
    int x, y;

    Coordinate(int X, int Y): x(X), y(Y) {}

    pair<int, int> xy(){return {x, y};}

    void translate(string instruction){

      char direction = instruction[0];
      int length = stoi(instruction.substr(1));
      
      switch(direction){

        case 'U': y += length; break;
        case 'R': x += length; break;
        case 'D': y -= length; break;
        case 'L': x -= length; break;

      }

    }

};

Coordinate origin(0, 0);

class Line{

  public:
    
    Coordinate beg, end;

    Line(Coordinate BEG, Coordinate END): beg(BEG), end(END) {}

    int length(){return abs(beg.x - end.x) + abs(beg.y - end.y);}

    Coordinate get_intersect(Line other){

        if (beg.x == end.x && other.beg.y == other.end.y) {
            // Vertical line and horizontal line
            if (min(beg.y, end.y) <= other.beg.y && other.beg.y <= max(beg.y, end.y) &&
                min(other.beg.x, other.end.x) <= beg.x && beg.x <= max(other.beg.x, other.end.x)) {
                return Coordinate(beg.x, other.beg.y);
            }
        } else if (beg.y == end.y && other.beg.x == other.end.x) {
            // Horizontal line and vertical line
            if (min(beg.x, end.x) <= other.beg.x && other.beg.x <= max(beg.x, end.x) &&
                min(other.beg.y, other.end.y) <= beg.y && beg.y <= max(other.beg.y, other.end.y)) {
                return Coordinate(other.beg.x, beg.y);
            }
        }

        // No intersect
        return origin;

    }

};

vector<Line> get_cable_segments(ifstream& in_file){
  
  vector<Line> segments = {{origin, origin}};

  string line, field;

  getline(in_file, line);

  stringstream line_stream(line);

  while(getline(line_stream, field, ',')){
    
    Coordinate new_coord = segments.back().end;

    new_coord.translate(field);

    Line new_line = {segments.back().end, new_coord};

    segments.push_back(new_line);

  }

  segments.erase(segments.begin());

  return segments;

}

int main(){
  
  ifstream in_file("input.txt");

  vector<Line> cable[2];

  cable[0] = get_cable_segments(in_file);
  cable[1] = get_cable_segments(in_file);

  vector<int> total_path_lengths;

  int path_length[2] = {0, 0};

  for(Line l0 : cable[0]){

    path_length[0] += l0.length();

    path_length[1] = 0;

    for(Line l1 : cable[1]){

      path_length[1] += l1.length();
      
      Coordinate intersect = l0.get_intersect(l1);
      
      if(intersect.xy() != origin.xy()){
        
        Line l0_to_intersect(l0.end, intersect);
        Line l1_to_intersect(l1.end, intersect);

        total_path_lengths.push_back(path_length[0] + path_length[1] - l0_to_intersect.length() - l1_to_intersect.length());

      }

    }
    
  }

  sort(total_path_lengths.begin(), total_path_lengths.end());

  cout<<total_path_lengths[0]<<endl;

}
