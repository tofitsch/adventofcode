#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
vector<string> rdigits = {"orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};

int main(){

  string regex_str = "";

  for(string & digit : digits)
    regex_str += digit + "|";

  regex_str.pop_back();

  regex rex(regex_str);

  string rregex_str(regex_str.rbegin(), regex_str.rend());
  regex rrex(rregex_str);

  map<string, string> regex_map;
  for(int i = 0; i < digits.size(); ++i){
    regex_map.insert(make_pair(digits[i], to_string(i)));
    regex_map.insert(make_pair(rdigits[i], to_string(i)));
  }

  int sum = 0;
  
  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line)){
    
//    if(line == "fivegfslvcvtvs4")
//      break;
    
    smatch match;

    string rline(line.rbegin(), line.rend());

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

//    cout<<" "<<first_c<<last_c<<endl;

    sum += stoi(num);

//    cout<<num<<endl;

  }

  cout<<sum<<endl;

}
