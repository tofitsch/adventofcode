#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Graph{
  
  private:
    
    enum NodeType{T_Broadcaster, T_FlipFlop, T_Conjunction};

    struct Node;
    struct FlipFlop;
    struct Conjunction;
    struct Broadcaster;

    map<string, Node*> nodes;

    queue<Node *> q;

  public:

    int n_fired_low = 0;
    int n_fired_high = 0;

    Graph(string);

    void broadcast();

    void print();
  
};

struct Graph::Node{
  
  NodeType type;
  string label;

  queue<bool> signals_received;
  vector<string> output_labels;
  vector<Node *> outputs;

  Node() {}
  Node(string);

  virtual void fire(queue<Node *> &, int &, int &) {};

  virtual void print();

};

Graph::Node::Node(string line){
   
  string field;
  
  stringstream line_stream(line);

  vector<string> fields;

  while(getline(line_stream, field, ' '))
    fields.push_back(field);

  switch(fields[0][0]){
    case '%': type = T_FlipFlop; break;
    case '&': type = T_Conjunction; break;
    default: type = T_Broadcaster;
  };

  if(type == T_Broadcaster)
    label = "broadcaster";
  else
    label = fields[0].substr(1, fields[0].length() - 1);

  for(int i=2; i<fields.size(); i++){
    
    if(fields[i].back() == ',')
      fields[i].pop_back();

    output_labels.push_back(fields[i]);

  }

}

void Graph::Node::print(){
  
  cout << type << " " << label << " ;";

  for(string & output : output_labels)
    cout << output << ";";

  cout << endl;

}

struct Graph::FlipFlop : Graph::Node{
  
  bool state = false;

  FlipFlop(string line) : Node(line) {}

  void fire(queue<Node *> & q, int & n_fired_low, int & n_fired_high) override{
    
    if(signals_received.empty())
      return;

    bool signal = signals_received.front();

    signals_received.pop();

    if(signal)
      return;

    state = ! state;

    cout << "FlipFlop " << label << (state ? " high" : " low") << endl;

    for(Node * output : outputs){

      if(state)
        n_fired_high++;
      else
        n_fired_low++;

      output->signals_received.push(state);

      q.push(output);

    }

  }

  void print() override{
    
    cout << type << " " << label << " ;";

    for(string & output : output_labels)
      cout << output << ";";

    cout << (state ? " | high" : " | low") << endl;

  }

};

struct Graph::Conjunction : Graph::Node{
  
  Conjunction(string line) : Node(line) {}

  void fire(queue<Node *> & q, int & n_fired_low, int & n_fired_high) override{

    bool signal = false;

    while(! signals_received.empty()){

      if(! signals_received.front())
        signal = true;

      signals_received.pop();

    }
   
    cout << "Conjunction " << label << (signal ? " high" : " low") << endl;

    for(Node * output : outputs){
      
      if(signal)
        n_fired_high++;
      else
        n_fired_low++;

      output->signals_received.push(signal);

      q.push(output);

    }

  }
  
};

struct Graph::Broadcaster : Graph::Node{
  
  Broadcaster(string line) : Node(line) {}
  
  void fire(queue<Node *> & q, int & n_fired_low, int & n_fired_high) override{
    
    cout << "Broadcaster " << label << " low" << endl;
    
    for(Node * output : outputs){
      
      n_fired_low++;

      output->signals_received.push(false);

      q.push(output);

    }

  }
  
};

Graph::Graph(string in_file_name){

  string line;

  ifstream in_file(in_file_name);

  while(getline(in_file, line)){
    
    Node node(line);

    switch(node.type){
      case T_FlipFlop : nodes[node.label] = new FlipFlop(line); break;
      case T_Conjunction : nodes[node.label] = new Conjunction(line); break;
      default : nodes[node.label] = new Broadcaster(line); break;
    };
      
  }

  for(auto & [key, node] : nodes)
    for(string & output : node->output_labels)
      if(nodes.find(output) != nodes.end())
        node->outputs.push_back(nodes[output]);

}

void Graph::broadcast(){
  
  q.push(nodes["broadcaster"]);

  n_fired_low++;

  while(! q.empty()){

    Node * node = q.front();
    
    q.pop();

    node->fire(q, n_fired_low, n_fired_high);

  }
  
}

void Graph::print(){
  
  for(auto & [key, node] : nodes)
    node->print();

}

int main(){
 
  Graph graph("example.txt");

  for(int i=0; i<1000; i++)
    graph.broadcast();

  cout << endl;

  graph.print();

  cout << graph.n_fired_low << " " << graph.n_fired_high << endl;

}
