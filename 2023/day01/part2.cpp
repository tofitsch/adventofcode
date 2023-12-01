#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

string reverse(string str){
  
  string r_string(str.rbegin(), str.rend());
  
  return r_string;

}

int main(){

  string regex_str = "";

  for(string & digit : digits)
    regex_str += digit + "|";

  regex_str.pop_back();

  regex rex(regex_str);
  regex rrex(reverse(regex_str));

  map<string, string> regex_map;

  for(int i = 0; i < digits.size(); ++i){

    regex_map.insert(make_pair(digits[i], to_string(i)));
    regex_map.insert(make_pair(reverse(digits[i]), to_string(i)));

  }

  int sum = 0;
  
  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line)){
    
    smatch match;

    string rline = reverse(line);

    if(regex_search(line, match, rex))
      line = regex_replace(line, rex, regex_map[match.str()], regex_constants::format_first_only);

    if(regex_search(rline, match, rrex))
      rline = regex_replace(rline, rrex, regex_map[match.str()], regex_constants::format_first_only);

    char first_c = ' ';
    char last_c = ' ';
    
    for(char & c : line)
      if(isdigit(c))
        if(first_c == ' ')
          first_c = c;

    for(char & c : rline)
      if(isdigit(c))
        if(last_c == ' ')
          last_c = c;

    string num(1, first_c);
    num += last_c;

    sum += stoi(num);

  }

  cout<<sum<<endl;

}
