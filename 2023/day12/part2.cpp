#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

struct Row{
 
  string str;
  vector<int> group_sizes;
  vector<int> group_positions;
  vector<int> group_first_positions;
  vector<int> max_group_size_at;

  Row(string);

  int get_n_valid_solutions();
  void set_first_valid_solution();
  bool set_next_valid_solution();

  void print();

};

void Row::set_first_valid_solution(){
  
  for(int i=0; i<group_sizes.size(); i++){
    
    if(i == 0)
      group_positions[i] = 0;
    else
      group_positions[i] = group_positions[i - 1] + group_sizes[i - 1] + 1;
    
    int end_pos = group_positions[i] + group_sizes[i];

//    cout << str.length() << " " << end_pos << str[end_pos] << " " << i << endl;

    while(max_group_size_at[group_positions[i]] < group_sizes[i] ||
      (group_positions[i] + group_sizes[i] < str.length() && str[group_positions[i] + group_sizes[i]] == '#') ||
      (group_positions[i] > 0 && str[group_positions[i] - 1] == '#')
    )
      group_positions[i]++;

  }

  group_first_positions = group_positions;

}

bool Row::set_next_valid_solution(){
  
  for(int i=group_sizes.size() - 1; i>=0; i--){

    int new_pos = group_positions[i];

    while(new_pos < str.length() - 1){
      
      new_pos++;

      if(i < group_sizes.size() - 1 && new_pos + group_sizes[i] >= group_positions[i + 1])
        break;

      if(max_group_size_at[new_pos] >= group_sizes[i] &&
         (new_pos + group_sizes[i] >= str.length() - 1 || str[new_pos + group_sizes[i]] != '#') && 
         (new_pos == 0 || str[new_pos - 1] != '#')
      ){
        
        group_positions[i] = new_pos;
        
        return true;

      }

    }

    group_positions[i] = group_first_positions[i];

  }

  return false;

}

int Row::get_n_valid_solutions(){
  
  set_first_valid_solution();

  for(int m : max_group_size_at)
    cout << m;

  cout << " ";
  
  for(int g : group_sizes)
    cout << g << ",";
  cout << endl;

  cout << str << endl << endl; 

  int ctr = 1;

  print();
  
  cout << endl;

  while(set_next_valid_solution()){

    print();

    ctr++;

  }

  cout << ctr << endl; 

  exit(0); //XXX
  
  return 0;

}

Row::Row(string line){

  size_t space_pos = line.find(' ');

  string str_original = line.substr(0, space_pos);
  string group_sizes_str_original = line.substr(space_pos + 1);
  string group_sizes_str = "";

  for(int i=0; i<5; i++){

    str += str_original + "?";
    group_sizes_str += group_sizes_str_original + ",";

  }

  str.pop_back();

  for(int i=0; i<str.length(); i++){

    max_group_size_at.push_back(0);

    for(int j=i; j<str.length(); j++)
      if(str[j] != '.')
        max_group_size_at.back()++;
      else
        break;

  }


  stringstream line_stream(group_sizes_str);

  string field;

  while(getline(line_stream, field, ',')){

    group_sizes.push_back(stoi(field));

    group_positions.push_back(0);

  }

}

void Row::print(){
  
  string out = str;

  for(int i=0; i<group_positions.size(); i++)
    for(int s=0; s<group_sizes[i]; s++)
      out[group_positions[i] + s] = 'X';

  cout << out << endl;

}


int main(){

  string line;

  ifstream in_file("example.txt");

  int sum = 0;

  while(getline(in_file, line)){

    Row row(line);

    cout << line << endl;

    sum += row.get_n_valid_solutions();

    break; //XXX

  }

//  cout << sum << endl;

}
