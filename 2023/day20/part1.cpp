#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;


class Graph{
  
  private:
    
    enum NodeType{Broadcaster, FlipFlop, Conjunction};

    struct Node;

  public:

    map<string, Node> nodes;

    Graph(string);

    void print();
  
};

struct Graph::Node{
  
  NodeType type;
  string label;

  vector<string> outputs;
  vector<Node *> links;

  Node() {}
  Node(string);

  void print();

};

Graph::Node::Node(string line){
   
  string field;
  
  stringstream line_stream(line);

  vector<string> fields;

  while(getline(line_stream, field, ' '))
    fields.push_back(field);

  switch(fields[0][0]){
    case '%': type = FlipFlop; break;
    case '&': type = Conjunction; break;
    default: type = Broadcaster;
  };

  if(type == Broadcaster)
    label = "broadcaster";
  else
    label = fields[0].substr(1, fields[0].length() - 1);

  for(int i=2; i<fields.size(); i++){
    
    if(fields[i].back() == ',')
      fields[i].pop_back();

    outputs.push_back(fields[i]);

  }

}

void Graph::Node::print(){
  
  cout << type << " " << label << " ;";

  for(string & output : outputs)
    cout << output << ";";

  cout << endl;

}

Graph::Graph(string in_file_name){

  string line;

  ifstream in_file(in_file_name);

  while(getline(in_file, line)){
    
    Node node(line);

    nodes[node.label] = node;

  }

  for(auto & [key, node] : nodes)
    for(string & output : node.outputs)
      if(nodes.find(output) != nodes.end())
        node.links.push_back(& nodes[output]);

}

void Graph::print(){
  
  for(auto & [key, node] : nodes)
    node.print();

}

int main(){
 
  Graph graph("example.txt");

  graph.print();

}
