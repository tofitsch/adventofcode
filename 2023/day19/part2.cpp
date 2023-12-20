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

    void print();

  private:
    
    static int const n_limits = 4;
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
  
  int from, to;

  Limit() : from(limit_min), to(limit_max) {}
  Limit(int f, int t) : from(f), to(t) {}

  pair<Limit, Limit> invert(){
    
    return make_pair(Limit(limit_min, from), Limit(to, limit_max));

  }

};

struct Graph::LimitSet{

  vector<vector<Limit>> limits{n_limits, vector<Limit>()};

  void add(int i, Limit limit){
    
    limits[i].push_back(limit);

  }

  void print(){
    
    for(int i=0; i<n_limits; i++){
      
      cout << i << ": ";

      for(Limit & limit : limits[i])
        cout << limit.from << "-" << limit.to << " ";

      cout << endl;

    }

  }

};

struct Graph::Edge{

  bool active = true;

  Node * in, * out;

  LimitSet limit_set;

  Edge(Node * in, Node * out, LimitSet l) : in(in), out(out), limit_set(l) {}

  void print(){
    
    cout << in->label << "->" << out->label << endl;

    limit_set.print();

    cout << endl;

  }

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

    LimitSet target_limits;

    for(string & str : fields){
      
      Rule rule(str);
      
      LimitSet rule_limits;

      Limit rule_limit;

      if(rule.greater)
        rule_limit = Limit(rule.value, limit_max);
      else
        rule_limit = Limit(limit_min, rule.value);

      pair<Limit, Limit> target_limit = rule_limit.invert();

      rule_limits.add(rule.property_id, rule_limit);

      target_limits.add(rule.property_id, target_limit.first);
      target_limits.add(rule.property_id, target_limit.second);

      edges.push_back(Edge(& nodes[label], & nodes[rule.target], rule_limits));

      nodes[label].edges.push_back(& edges.back());

    }

    edges.push_back(Edge(& nodes[label], & nodes[target], target_limits));
    nodes[label].edges.push_back(& edges.back());
    
  }

}

void Graph::print(){

  for(Edge & edge : edges)
    edge.print();

}

int main(){
  
  Graph graph("example.txt");

  graph.print();

}

