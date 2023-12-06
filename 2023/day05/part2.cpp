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

  vector<long> get_discontinuities(vector<long> next_rule_discontinuities){
    
    vector<long> discs;

    for(Range & range : ranges){

      discs.push_back(range.beg);
      discs.push_back(range.end);

    }

    for(long dis : next_rule_discontinuities){

      bool found_range = false;

      for(Range & range : ranges){
        if(range.beg + range.offset <= dis && range.end + range.offset >= dis){

          discs.push_back(dis - range.offset);
          found_range = true;
          break;

        }
      }

      if(!found_range)
        discs.push_back(dis);

    }

    return discs;

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

void read_seed_ranges(string & line, vector<pair<long, long>> & seed_ranges){
  
  string field;

  stringstream line_stream(line);

  int field_ctr = 0;

  while(getline(line_stream, field, ' ')){
    
    field_ctr++;

    if(field_ctr < 2)
      continue;

    if(field_ctr % 2 == 0)
      seed_ranges.push_back({stol(field), 0});
    else
      seed_ranges.back().second = seed_ranges.back().first + stol(field);

  }

}

int main(){
  
  string line;

  ifstream in_file("input.txt");
  
  vector<pair<long, long>> seed_ranges;
  vector<Rule> rules;

  int rule_ctr = 0;

  while(getline(in_file, line)){
     
    if(line.find("seeds:") != string::npos)
      read_seed_ranges(line, seed_ranges);

    else if(line.back() == ':')
      rule_ctr++;

    else if(line.length() > 0)
      read_rule(line, rules, rule_ctr);

  }

  vector<long> discontinuities;

  for(int i = rules.size() - 1; i >= 0; --i)
    discontinuities = rules[i].get_discontinuities(discontinuities);

  vector<long> discontinuities_with_seeds;

  for(long & dis : discontinuities)
    for(auto & sr : seed_ranges)
      if(dis >= sr.first && dis <= sr.second)
        discontinuities_with_seeds.push_back(dis);

  for(auto & sr : seed_ranges){

    discontinuities_with_seeds.push_back(sr.first);
    discontinuities_with_seeds.push_back(sr.second);

  }

  for(long & dis : discontinuities_with_seeds)
    for(Rule & rule : rules)
      rule.apply(dis);

  sort(discontinuities_with_seeds.begin(), discontinuities_with_seeds.end());

  cout << discontinuities_with_seeds[0] << endl;

}
