#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct Row{
 
  string str;
  vector<int> nums;
  vector<int> pos_hidden;
  string hidden_str = "";

  int n_broken = 0;
  int n_broken_visible = 0;
  int n_hidden = 0;
  int n_broken_hidden = 0;
  int n_intact_hidden = 0;

  string place_hidden_str_into_str(){
   
    string result_str = str;

    int ctr = 0;
    
    for(int & pos : pos_hidden){
      
      result_str[pos] = hidden_str[ctr];
      
      ctr++;

    }

    return result_str;

  }

  vector<int> get_groupings(string s){
    
    vector<int> grouping;
    
    for(int i=0; i<s.size(); i++){

      if(s[i] == '#' && (i == 0 || s[i - 1] != '#'))
        grouping.push_back(1);

      if(i > 0 && s[i] == '#' && s[i - 1] == '#')
        grouping.back()++;

    }

    return grouping;

  }
  
  Row(string line){

    size_t space_pos = line.find(' ');

    str = line.substr(0, space_pos);

    for(int i=0; i<str.length(); i++)
      if(str[i] == '?')
        pos_hidden.push_back(i);
    
    stringstream line_stream(line.substr(space_pos + 1));

    string field;

    while(getline(line_stream, field, ','))
      nums.push_back(stoi(field));

    for(int & num : nums)
      n_broken += num;

    n_broken_visible = count(str.begin(), str.end(), '#');
    n_hidden = pos_hidden.size();
    n_broken_hidden = n_broken - n_broken_visible;
    n_intact_hidden = n_hidden - n_broken_hidden;

    for(int i=0; i<n_broken_hidden; i++)
      hidden_str += "#";

    for(int i=0; i<n_intact_hidden; i++)
      hidden_str += ".";

  }

  int get_n_valid(){
    
    int n_valid = 0;

    do{

      string s =  place_hidden_str_into_str();

      vector<int> grouping = get_groupings(s);

      if(grouping == nums)
        n_valid++;

    }while(next_permutation(hidden_str.begin(), hidden_str.end()));
    
    return n_valid;

  }
  
};

int main(){

  string line;

  ifstream in_file("input.txt");

  int sum = 0;

  while(getline(in_file, line)){

    Row row(line);

    sum += row.get_n_valid();

  }

  cout << sum << endl;

}
