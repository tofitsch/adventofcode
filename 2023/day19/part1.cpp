#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

map<char, int> property_map = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

struct Item{
  
  int property[4];
  int score = 0;

  Item(string line){
    
    string field;
   
    stringstream line_stream(line.substr(1, line.length() - 2));

    short ctr = 0;

    while(getline(line_stream, field, ',')){
      
      string property_str = field.substr(2, field.length() - 2);

      property[ctr] = stoi(property_str);

      score += property[ctr];
      
      ctr++;

    }

  }

};

struct Rule{
  
  short property_id;
  bool greater;
  int value;
  string target;

  string apply_to(Item & item){
   
    if(greater && item.property[property_id] > value)
      return target;

    if(! greater && item.property[property_id] < value)
      return target;

    return "";

  }

  Rule(string str){
    
    property_id = property_map[str[0]];

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

  string apply_to(Item & item){
    
    string result = "";

    int ctr = 0;

    while(result == "" && ctr < rules.size()){
      
      result = rules[ctr].apply_to(item);

      ctr++;

    }

    if(result == "")
      return target;

    return result;
    
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

int main(){
  
  string line;

  ifstream in_file("input.txt");

  vector<Item> items;
  map<string, RuleSet> rule_sets;

  bool is_rule = true;

  while(getline(in_file, line)){
    
    if(line.length() == 0){

      is_rule = false;
      continue;

    }

    if(is_rule){
      
      RuleSet rule_set(line);

      rule_sets[rule_set.label] = rule_set;

    }
    else
      items.push_back(Item(line));

  }

  int sum = 0;

  for(Item & item : items){

    string label = "in";

    while(label != "A" && label != "R")
      label = rule_sets[label].apply_to(item);

    if(label == "A")
      sum += item.score;

  }

  cout << sum << endl;

}
