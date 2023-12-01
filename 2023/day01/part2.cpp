#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main(){

  string regex_str = "";

  for(string & digit : digits)
    regex_str += digit + "|";

  regex_str.pop_back();

  regex rex(regex_str);

  map<string, string> regex_map;
  for(int i = 0; i < digits.size(); ++i)
    regex_map.insert(make_pair(digits[i], to_string(i)));

  int sum = 0;
  
  string line;

  ifstream in_file("example.txt");

  while(getline(in_file, line)){
    
    smatch match;
    
    while(regex_search(line, match, rex))
      line = regex_replace(line, rex, regex_map[match.str()], regex_constants::format_first_only);
    
    char first_c = ' ';
    char last_c = ' ';
    
    for(char & c : line){
      
      if(isdigit(c)){
        
        last_c = c;

        if(first_c == ' ')
          first_c = c;

      }

    }

    string num(1, first_c);
    num += last_c;

    sum += stoi(num);

    cout<<num<<endl;

  }

  cout<<sum<<endl;

}
