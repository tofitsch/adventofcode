#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

map<char, int> property_map = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

class Graph{

  public:

    Graph(string);

  private:
    
    static int const limit_min = 0;
    static int const limit_max = 4001;
  
    struct Rule;
    struct Edge;
    struct Node;

    struct Limit;
    struct LimitSet;

    map<string, Node> nodes;
    vector<Edge> edges;

};

struct Graph::Rule{
  
  short property_id;
  bool greater;
  int value;
  string target;

  Rule(string str){
    
    property_id = property_map[str[0]];

    greater = (str[1] == '>');

    size_t colon_pos = str.find(':');

    string value_str = str.substr(2, colon_pos - 2);

    value = stoi(value_str);

    target = str.substr(colon_pos + 1);

  }

};

struct Graph::Node{
  
  bool active = true;
  
  vector<Edge *> edges;
  string label;

  Node() {}
  Node(string l) : label(l) {}

};
  
struct Graph::Limit{

  int greater, smaller;

  Limit() : greater(limit_min), smaller(limit_max) {}
  Limit(int g, int l) : greater(g), smaller(l) {}

};

struct Graph::LimitSet{

  vector<vector<Limit>> limits{4, vector<Limit>()};

  void add(int id, Limit limit){
    
    limits[id].push_back(limit);

  }

};

struct Graph::Edge{

  bool active = true;

  Node * in, * out;

  LimitSet limit_set;

  Edge(Node * in, Node * out, LimitSet l) : in(in), out(out), limit_set(l) {}

/*TODO
  void restrict(vector<Edge *> restrictions){
    
    for(Edge * restriction : restrictions){

      for(int i=0; i<4; i++){

          if(greater[i] > restriction.greater[i]);
            greater[i] = restriction.greater[i];

          if(smaller[i] > restriction.smaller[i]);
            smaller[i] = restriction.smaller[i];
        
      }

    }
 */

};

Graph::Graph(string in_file_name){
  
  string line;
  
  ifstream in_file(in_file_name);

  nodes["A"] = Node("A");
  nodes["R"] = Node("R");

  vector<string> lines;

  while(getline(in_file, line))
    if(line.length() == 0)
      break;
    else
      lines.push_back(line);

  for(string & line : lines){
    
    size_t brace_pos = line.find('{');

    string label = line.substr(0, brace_pos);

    nodes[label] = Node(label);

  }

  for(string & line : lines){
    
    size_t brace_pos = line.find('{');

    string label = line.substr(0, brace_pos);

    string rule_str = line.substr(brace_pos + 1, line.length() - brace_pos - 2);

    string field;

    vector<string> fields;
  
    stringstream rule_stream(rule_str);

    while(getline(rule_stream, field, ','))
      fields.push_back(field);

    string target = fields.back();

    fields.pop_back();

    for(string & str : fields){
      
      Rule rule(str);
      
      LimitSet limits;

      if(rule.greater)
        limits.add(rule.property_id, Limit(rule.value, limit_max));
      else
        limits.add(rule.property_id, Limit(limit_min, rule.value));

      edges.push_back(Edge(& nodes[label], & nodes[rule.target], limits));

    }

    LimitSet limits;
    
    for(int i=0; i<4; i++)
      limits.add(i, Limit(limit_min, limit_max));

    edges.push_back(Edge(& nodes[label], & nodes[target], limits));

  }

}

int main(){
  
  Graph graph("example.txt");

}

