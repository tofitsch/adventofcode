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
  ".*(.)\\1.*(.)\\2.*",                    // 2 pair
  ".*(.)\\1.*",                            // 1 pair
};

string rename_card_values_alphabetically(string & line){
  
  for(char & c : line){

    if(c == 'J') c = '1';
    else if(c == 'T') c = 'a';
    else if(c == 'Q') c = 'b';
    else if(c == 'K') c = 'c';
    else if(c == 'A') c = 'd';
    else if(c == ' ') break;

  }

  return line;

}

string joker_replace(string hand, char card){
  
  for(char & c : hand)
    if(c == 'J') c = card;

  return hand;

}

string format_for_scoring(string & line){
  
  string hand_with_joker;

  stringstream line_stream(line);

  getline(line_stream, hand_with_joker, ' ');

  int max_hand_type = 0;

  for(char c : hand_with_joker){

    string hand = joker_replace(hand_with_joker, c);

    sort(hand.begin(), hand.end());

    for(int i = 0; i<hand_types.size(); ++i){

      regex pattern(hand_types[i]);

      if(regex_match(hand, pattern) && hand_types.size() - i > max_hand_type)
        max_hand_type = hand_types.size() - i;

    }

  }

  return to_string(max_hand_type) + rename_card_values_alphabetically(line);

}

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<string> lines;

  while(getline(in_file, line))
    lines.push_back(format_for_scoring(line));

  sort(lines.begin(), lines.end());

  long sum = 0;

  for(long i=0; i<lines.size(); ++i){
    
    stringstream line_stream(lines[i]);

    getline(line_stream, field, ' ');
    getline(line_stream, field, ' ');

    sum += (i + 1) * stol(field);

  }

  cout << sum << endl;

}
