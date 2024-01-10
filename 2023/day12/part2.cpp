#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>

using namespace std;

struct Row{
  
  private:
 
    string lava;
    vector<int> group_sizes;

    int sum_group_sizes = 0;

    map<string, long> cache;

    long recurse(string, int, int, long);

  public:

    Row(string);
    long get_n_solutions();

};

Row::Row(string line){

  size_t space_pos = line.find(' ');

  string str_original = line.substr(0, space_pos);
  string group_sizes_str_original = line.substr(space_pos + 1);
  string group_sizes_str = "";

  for(int i=0; i<5; i++){

    lava += str_original + "?";
    group_sizes_str += group_sizes_str_original + ",";

  }

  lava.pop_back();
  group_sizes_str.pop_back();

  stringstream line_stream(group_sizes_str);

  string field;

  while(getline(line_stream, field, ','))
    group_sizes.push_back(stoi(field));

  for(int i : group_sizes)
    sum_group_sizes += i;
  
}

long Row::recurse(string str, int n_group, int group_pos, long ctr){
  
  if(str.length() == 0)
    return (n_group == group_sizes.size() && group_pos < 1);

  switch(str[0]){

    case '#':
      
      if(group_pos == -1 || n_group >= group_sizes.size())
        return 0;

      group_pos++;

      if(group_pos == group_sizes[n_group]){

        group_pos = -1;
        n_group++;

      }

      break;

    case '.':
      
      if(group_pos > 0)
        return 0;

      if(group_pos == -1)
        group_pos++;
      
      break;

    case '?':
      
      str.erase(0, 1);

      return ctr + recurse("#" + str, n_group, group_pos, ctr) + recurse("." + str, n_group, group_pos, ctr);

  }

  string key = str.substr(1, str.length() - 1) + '_' + to_string(n_group) + '_' + to_string(group_pos);

  if(cache.find(key) == cache.end())
    cache[key] = recurse(str.substr(1, str.length() - 1), n_group, group_pos, ctr);

  return cache[key];
    
}

long Row::get_n_solutions(){
  
  return recurse(lava, 0, 0, 0);

}

int main(){

  string line;

  ifstream in_file("input.txt");

  long sum = 0;

  while(getline(in_file, line)){
    
    Row row(line);

    sum += row.get_n_solutions();

  }

  cout << sum << endl;

}
