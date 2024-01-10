#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

struct Row{
  
  private:
 
    string str;
    vector<int> group_sizes;
    int sum_group_sizes = 0;
    set<string> solutions;

    void recurse(string, int, int, int);

  public:

    Row(string);
    int get_n_solutions();

};

Row::Row(string line){

  size_t space_pos = line.find(' ');

  str = line.substr(0, space_pos) + '.';
  
  stringstream line_stream(line.substr(space_pos + 1));

  string field;

  while(getline(line_stream, field, ','))
    group_sizes.push_back(stoi(field));

  for(int i : group_sizes)
    sum_group_sizes += i;

}

void Row::recurse(string lava, int str_pos, int n_group, int group_pos){
  
  if(str_pos == lava.length() - 1){
    
    int n_x = 0;
    
    for(char & c : lava){

      if(c == '#' || c == '?')
        return;

      if(c == 'x')
        n_x++;

    }

    if(n_x != sum_group_sizes)
       return;

    solutions.insert(lava);

    return;

  }

  char * c = & lava[str_pos];
  
  switch(* c){

    case '#':
      
      if(n_group >= group_sizes.size())
        break;
      
      * c =  'x';

      if(group_pos == 0 && n_group > 0 && lava[str_pos - 1] == 'x')
        break;

//      cout << lava << endl;

      group_pos++;

      if(group_pos == group_sizes[n_group]){

        group_pos = 0;
        n_group++;

      }

      recurse(lava, str_pos + 1, n_group, group_pos);

      break;

    case '.':
      
      if(group_pos != 0)
        break;

      recurse(lava, str_pos + 1, n_group, group_pos);

      break;

    case '?':
      
      * c =  '#';

      recurse(lava, str_pos, n_group, group_pos);

      * c =  '.';

      recurse(lava, str_pos, n_group, group_pos);

      break;

  }
    
}

int Row::get_n_solutions(){
  
  recurse(str, 0, 0, 0);
  
  return solutions.size();

}

int main(){

  string line;

  ifstream in_file("input.txt");

  int sum = 0;

  while(getline(in_file, line)){
    
    Row row(line);

    sum += row.get_n_solutions();

  }

  cout << sum << endl;

}
