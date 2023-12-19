#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

map<char, int> property_map = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

struct Item{
  
  short property[4];

  Item(string line){
    
    string field;
   
    stringstream line_stream(line.substr(1, line.length() - 2));

    short ctr = 0;

    while(getline(line_stream, field, ',')){
      
      string property_str = field.substr(2, field.length() - 2);

      property[ctr] = stoi(property_str);
      
      ctr++;

    }

    print();
    cout << endl;

  }

  void print(){

    for(int i=0; i<4; i++)
      cout << property[i] << " ";
    cout << endl;

  }

};

struct Rule{
  
  short property;
  bool greater;
  int value;
  string target;

  Rule(string str){
    
    property = property_map[str[0]];

    greater = (str[1] == '>');

    size_t colon_pos = str.find(':');

    string value_str = str.substr(2, colon_pos - 2);

    value = stoi(value_str);

    target = str.substr(colon_pos + 1);

  }

  void print(){

    cout << property << (greater ? '>' : '<') << value << ':' << target << endl;

  }

};

struct RuleSet{
  
  vector<Rule> rules;

  string label;
  string target;

  RuleSet() {}

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

    print();
    cout << endl;
    
  }

  void print(){
    
    cout << label << endl;

    for(Rule & rule : rules)
      rule.print();

    cout << target << endl;

  }

};

int main(){
  
  string line;

  ifstream in_file("example.txt");

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

}
