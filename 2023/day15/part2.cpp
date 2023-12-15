#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int label_hash(string str){
  
  int h = 0;

  for(char & c : str){

    if(c == '=' || c == '-')
      break;

    h += c;
    h *= 17;
    h %= 256;

  }

  return h;

}

struct Lense{

  string label;
  int focal_length;

  Lense(string l, int f) : label(l), focal_length(f) {}

};

struct Box{
  
  vector<Lense> lenses;

  void apply(string operation){
    
    if(operation.back() == '-'){

      string label = operation.substr(0, operation.length() - 1);

      for(int i=0; i<lenses.size(); i++)
        if(lenses[i].label == label){

          lenses.erase(lenses.begin() + i);
	  break;

	}

    }
    else{
      
      int focal_length = atoi(& operation.back());
      string label = operation.substr(0, operation.length() - 2);

      bool found = false;

      for(Lense & l : lenses){
        if(l.label == label){

	  l.focal_length = focal_length;
	  found = true;
	  break;

	}
      }

      if(!found)
        lenses.push_back(Lense(label, focal_length));

    }

  }

};

int main(){
 
  int const n_boxes = 256;
  
  Box boxes[n_boxes];
  
  string line, field;

  ifstream in_file("input.txt");
  
  getline(in_file, line);

  stringstream line_stream(line);

  while(getline(line_stream, field, ','))
    boxes[label_hash(field)].apply(field);

  int focusing_power = 0;

  for(int b=0; b<n_boxes; b++)
    for(int l=0; l<boxes[b].lenses.size(); l++)
      focusing_power += (b + 1) * (l + 1) * boxes[b].lenses[l].focal_length;

  cout << focusing_power << endl;

}
