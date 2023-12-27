#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

map<char, int> dimensions = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

struct Hypercube{
 
  string rule_set_label = "in";
  
  vector<int> min = {1, 1, 1, 1};
  vector<int> max = {4000, 4000, 4000, 4000};

  long volume(){
    
    long v = 1;

    for(int i=0; i<4; i++)
      v *= max[i] - min[i] + 1;

    return v;

  }

  bool empty(){

    for(int i=0; i<4; i++)
      if(min[i] < 0)
        return true;

    return false;

  }

};

void split_range(int min, int max, bool greater, int value, int & min_accepted, int & max_accepted, int & min_rejected, int & max_rejected) {

  if(greater){

    min_accepted = value + 1;
    max_accepted = max;
    min_rejected = min;
    max_rejected = value;

  }
  else{

    min_accepted = min;
    max_accepted = value - 1;
    min_rejected = value;
    max_rejected = max;

  }
 
  if(min_accepted > max_accepted){

    min_accepted = -1;
    max_accepted = -1;

  }
 
  if(min_rejected > max_rejected){

    min_rejected = -1;
    max_rejected = -1;

  }

}

struct Rule{
  
  short dim;
  bool greater;
  int value;
  string target;

  pair<Hypercube, Hypercube> apply_to(Hypercube & h){
    
    Hypercube h_accepted = h;
    Hypercube h_rejected = h;
    
    h_accepted.rule_set_label = target;

    split_range(h.min[dim], h.max[dim], greater, value, h_accepted.min[dim], h_accepted.max[dim], h_rejected.min[dim], h_rejected.max[dim]);

    return {h_accepted, h_rejected};

  }

  Rule(string str){
    
    dim = dimensions[str[0]];

    greater = (str[1] == '>');

    size_t colon_pos = str.find(':');

    string value_str = str.substr(2, colon_pos - 2);

    value = stoi(value_str);

    target = str.substr(colon_pos + 1);

  }

};

struct RuleSet{
  
  vector<Rule> rules;

  string label;
  string target;

  RuleSet() {}

  vector<Hypercube> apply_to(Hypercube h){
    
    vector<Hypercube> h_vec;
     
    for(Rule & rule : rules){
      
      pair<Hypercube, Hypercube> accepted_rejected = rule.apply_to(h);

      if(! accepted_rejected.first.empty())
        h_vec.push_back(accepted_rejected.first);

      h = accepted_rejected.second;

    }

    h.rule_set_label = target;

    if(! h.empty())
      h_vec.push_back(h);

    return h_vec;

  }

  RuleSet(string line){
    
    size_t brace_pos = line.find('{');

    label = line.substr(0, brace_pos);

    string rule_str = line.substr(brace_pos + 1, line.length() - brace_pos - 2);

    string field;

    vector<string> fields;
  
    stringstream rule_stream(rule_str);

    while(getline(rule_stream, field, ','))
      fields.push_back(field);

    target = fields.back();

    fields.pop_back();

    for(string & str : fields)
      rules.push_back(Rule(str));

    
  }

};

void recursive_split(map<string, RuleSet> & rule_sets, long & n_accepted, Hypercube h){

  if(rule_sets.find(h.rule_set_label) == rule_sets.end()){
    
    if(h.rule_set_label == "A")
      n_accepted += h.volume();
      
    return;

  }
  
  vector<Hypercube> h_vec = rule_sets[h.rule_set_label].apply_to(h);

  for(Hypercube & next : h_vec)
    recursive_split(rule_sets, n_accepted, next);

}

int main(){
  
  string line;

  ifstream in_file("input.txt");

  map<string, RuleSet> rule_sets;

  while(getline(in_file, line)){
    
    if(line.length() == 0)
      break;

    RuleSet rule_set(line);

    rule_sets[rule_set.label] = rule_set;

  }

  Hypercube h;

  long n_accepted = 0;

  recursive_split(rule_sets, n_accepted, h);

  cout << n_accepted << endl;

}
