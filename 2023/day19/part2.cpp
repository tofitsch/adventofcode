#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

map<char, int> dimensions = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

struct Hypercube{
 
  string rule_set_label = "in";
  
  vector<int> min = {0, 0, 0, 0};
  vector<int> max = {4000, 4000, 4000, 4000};

  int volume(){
    
    int v = 1;

    for(int i=0; i<4; i++)
      v *= max[i] - min[i];

    return v;

  }

};

struct Rule{
  
  short dim;
  bool greater;
  int value;
  string target;

  pair<Hypercube, Hypercube> apply_to(Hypercube & h){
    
    Hypercube h_accepted = h;
    Hypercube h_rejected = h;
    
    h_accepted.rule_set_label = target;

    //TODO: check logic
    if(greater){

      if(h.min[dim] <= value)
        h_accepted.min[dim] = value + 1;
      if(h.max[dim] > value)
        h_rejected.max[dim] = value;

    }
    else{

      if(h.max[dim] >= value)
        h_accepted.max[dim] = value - 1;
      if(h.min[dim] < value)
        h_rejected.min[dim] = value;

    }

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

  void print(){

    cout << dim << (greater ? '>' : '<') << value << ':' << target << endl;

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

      h_vec.push_back(accepted_rejected.first);

      h = accepted_rejected.second;

    }

    h.rule_set_label = target;

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

  void print(){
    
    cout << label << endl;

    for(Rule & rule : rules)
      rule.print();

    cout << target << endl;

  }

};

void recursive_split(map<string, RuleSet> & rule_sets, vector<Hypercube> & accepted, Hypercube h){

  if(rule_sets.find(h.rule_set_label) == rule_sets.end()){
    
    if(h.rule_set_label == "A")
      accepted.push_back(h);

    cout << h.rule_set_label << " " << h.volume() << endl;

    return;

  }
  
  vector<Hypercube> h_vec = rule_sets[h.rule_set_label].apply_to(h);

  for(Hypercube & next : h_vec)
    recursive_split(rule_sets, accepted, next);

}

int main(){
  
  string line;

  ifstream in_file("example.txt");

  map<string, RuleSet> rule_sets;

  while(getline(in_file, line)){
    
    if(line.length() == 0)
      break;

    RuleSet rule_set(line);

    rule_sets[rule_set.label] = rule_set;

  }

//  for(auto [label, rule_set] : rule_sets)
//    rule_set.print();

  Hypercube h;

  vector<Hypercube> accepted;

  recursive_split(rule_sets, accepted, h);

  int sum = 0;

  for(Hypercube & a : accepted)
    sum += h.volume();

  cout << sum << endl;

}
