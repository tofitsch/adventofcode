#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<regex>
#include<set>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  map<int, int> n_copies;

  int i_card = 0;

  while(getline(in_file, line)){
    
    n_copies[i_card]++;
    
    line = regex_replace(line, regex("\\s+"), " ");
    
    int pos_winners = line.find(':');
    int pos_card = line.find('|');

    string winners_str = line.substr(pos_winners + 2, pos_card - pos_winners - 3);
    string card_str = line.substr(pos_card + 2);

    stringstream winners_stream(winners_str);
    stringstream card_stream(card_str);

    set<int> winners;
    set<int> card;

    while(getline(winners_stream, field, ' '))
      winners.insert(stoi(field));

    while(getline(card_stream, field, ' '))
      card.insert(stoi(field));

    int win_ctr = 0;

    for(int const & num : card)
      if(winners.find(num) != winners.end())
        win_ctr++;

    for(int i = 0; i < n_copies[i_card]; ++i)
      for(int j = 1; j <= win_ctr; ++j)
        n_copies[i_card + j]++;

    i_card++;

  }

  int sum = 0;

  for(auto & key : n_copies)
    sum += key.second;

  cout << sum << endl;

}
