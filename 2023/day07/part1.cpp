#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<regex>

using namespace std;

vector<string> hand_types = {
  "(.)\\1{4}",                             // 5 of a kind
  ".*(.)\\1{3}.*",                         // 4 of a kind
  "(.)\\1{2}(.)\\2{1}|(.)\\3{1}(.)\\4{2}", // full house
  ".*(.)\\1{2}.*",                         // 3 of a kind
  ".*(.)\\1.*{2}(.)\\2",                   // 2 pair
  ".*(.)\\1.*",                            // 1 pair
};

string rename_card_values_alphabetically(string & line){
  
  for(char & c : line){

    if(c == 'T') c = 'a';
    else if(c == 'J') c = 'b';
    else if(c == 'Q') c = 'c';
    else if(c == 'K') c = 'd';
    else if(c == 'A') c = 'e';
    else if(c == ' ') break;

  }

  return line;

}

string format_for_scoring(string & line){
  
  string hand;

  stringstream line_stream(line);

  getline(line_stream, hand, ' ');
  
  sort(hand.begin(), hand.end());

  for(int i = 0; i<hand_types.size(); ++i){

    regex pattern(hand_types[i]);

    if(regex_match(hand, pattern))
      return to_string(hand_types.size() - i) + rename_card_values_alphabetically(line);

  }

  return "0" + rename_card_values_alphabetically(line);

}

int main(){
  
  string line, field;

  ifstream in_file("example.txt");

  vector<string> lines;

  while(getline(in_file, line))
    lines.push_back(format_for_scoring(line));

  sort(lines.begin(), lines.end());

  int sum = 0;

  for(int i=0; i<lines.size(); ++i){
    
    cout << i + 1 << " " << lines[i] << endl;

    stringstream line_stream(lines[i]);

    getline(line_stream, field, ' ');
    getline(line_stream, field, ' ');

    sum += (i + 1) * stoi(field);

  }

  cout << sum << endl;

}
