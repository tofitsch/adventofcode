#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

struct Range{
  
  long beg, end, offset;

};

struct Rule{
  
  vector<Range> ranges;

  void apply(long & val){
    
    for(Range & range : ranges)
      if(range.beg <= val && range.end >= val){

        val += range.offset;
	break;

      }

  }

};

void read_rule(string & line, vector<Rule> & rules, int & rule_ctr){
  
  if(rules.size() < rule_ctr)
    rules.push_back(Rule());
  
  string field;

  stringstream line_stream(line);

  vector<long> nums;

  while(getline(line_stream, field, ' '))
    nums.push_back(stol(field));

  rules.back().ranges.push_back(Range{nums[1], nums[1] + nums[2] - 1, nums[0] - nums[1]});

}

void read_seeds(string & line, vector<long> & seeds){
  
  string field;

  stringstream line_stream(line);

  while(getline(line_stream, field, ' '))
    if(isdigit(field[0]))
      seeds.push_back(stol(field));

}

int main(){
  
  string line;

  ifstream in_file("input.txt");
  
  vector<long> seeds;
  vector<Rule> rules;

  int rule_ctr = 0;

  while(getline(in_file, line)){
     
    if(line.find("seeds:") != string::npos)
      read_seeds(line, seeds);

    else if(line.back() == ':')
      rule_ctr++;

    else if(line.length() > 0)
      read_rule(line, rules, rule_ctr);

  }

  for(long & seed : seeds)
    for(Rule & rule : rules)
      rule.apply(seed);

  sort(seeds.begin(), seeds.end());
   
  cout << seeds[0] << endl;

}
