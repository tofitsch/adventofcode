#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void check_differ_by_one(string & a, string & b){
  
  int diff_pos = a.length();

  for(int i=0; i<a.length(); i++)
    if(a[i] != b[i])
      if(diff_pos < a.length())
        return;
      else
        diff_pos = i;

  if(diff_pos < a.length()){
    
    a.erase(diff_pos, 1);

    cout << a << endl;

    exit(0);

  }

}

int main(){
  
  string line;
 
  ifstream in_file("input.txt");

  vector<string> lines;

  while(getline(in_file, line))
    lines.push_back(line);

  for(int i=0; i<lines.size(); i++)
    for(int j=i+1; j<lines.size(); j++)
      check_differ_by_one(lines[i], lines[j]);

}
