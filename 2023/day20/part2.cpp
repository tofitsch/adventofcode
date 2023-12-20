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

    struct SubGraphMonitor;

    int n_fired_low = 0;
    int n_fired_high = 0;

    Graph(string);

    void broadcast();

    SubGraphMonitor get_subgraph_monitor(string);

    void print();
  
};

struct Graph::Node{
  
  NodeType type;
  string label;
 
  bool fired = false;

  queue<bool> signals_received;
  map<Node *, bool> last_signal_from;
  vector<string> output_labels;
  vector<Node *> outputs;
  vector<Node *> inputs;

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
  
  cout << "Node " << label << endl;

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

    for(Node * output : outputs){
      
      fired = true;

      if(state)
        n_fired_high++;
      else
        n_fired_low++;

      output->signals_received.push(state);

      if(output->type == T_Conjunction)
        output->last_signal_from[this] = state;

      q.push(output);

//      cout << label << (state ? " -high-> " : " -low-> ") << output->label << endl;

    }

  }

  void print() override{
    
    cout << "FlipFlop" << (state ? ":hi " : ":lo ") << label << " ;";

    for(string & output : output_labels)
      cout << output << ";";

    cout << endl;

  }

};

struct Graph::Conjunction : Graph::Node{
  
  Conjunction(string line) : Node(line) {
    
    for(Node * input : inputs)
      last_signal_from[input] = false;

  }

  void fire(queue<Node *> & q, int & n_fired_low, int & n_fired_high) override{

    if(signals_received.empty())
      return;

    signals_received.pop();

    int n_high_inputs = 0;

    for(auto [input, is_high] : last_signal_from)
      if(is_high)
        n_high_inputs++;

    bool signal = ! (n_high_inputs == inputs.size());
   
    for(Node * output : outputs){
      
      fired = true;

      if(signal)
        n_fired_high++;
      else
        n_fired_low++;

      output->signals_received.push(signal);

      if(output->type == T_Conjunction)
        output->last_signal_from[this] = signal;

      q.push(output);

//      cout << label << (signal ? " -high-> " : " -low-> ") << output->label << endl;

    }

  }

  void print() override{
    
    cout << "Conjunction" << " " << label << " ;";

    for(string & output : output_labels)
      cout << output << ";";

    cout << endl;

  }
  
};

struct Graph::Broadcaster : Graph::Node{
  
  Broadcaster(string line) : Node(line) {}
  
  void fire(queue<Node *> & q, int & n_fired_low, int & n_fired_high) override{
    
    for(Node * output : outputs){
      
      fired = true;
      
      n_fired_low++;

      output->signals_received.push(false);

      if(output->type == T_Conjunction)
        output->last_signal_from[this] = false;

      q.push(output);

//      cout << label << " -low-> " << output->label << endl;

    }

  }

  void print() override{
    
    cout << "Broadcaster" << " " << label << " ;";

    for(string & output : output_labels)
      cout << output << ";";

    cout << endl;

  }
  
};

struct Graph::SubGraphMonitor{
  
  vector<vector<bool *>> sub_graph_states;
  vector<long> periodicity;

  long step = 0;

  void print(){
    
    int ctr = 0;
  
    for(vector<bool *> & sub_graph_state : sub_graph_states){
      
      cout << ctr << " ";
  
      for(bool * b : sub_graph_state)
        cout << *b;

      cout << "  " << periodicity[ctr] << endl;

      ctr++;
  
    }
  
  }

  bool find_periodicity(){
    
    int ctr = 0;
    
    for(vector<bool *> & sub_graph_state : sub_graph_states){
      
      if(periodicity[ctr] > 0)
        continue;
      
      bool all_on = true;

      for(bool * b : sub_graph_state){

        if(! (*b)){
          all_on = false;
          break;
        }

      }

      if(all_on)
        periodicity[ctr] = step;

      ctr++;

    }

    step++;

    for(long & p : periodicity)
      if(p == 0)
        return false;

    return true;

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

  for(auto & [key, node] : nodes){
    for(string & output : node->output_labels){

      if(nodes.find(output) == nodes.end())
        nodes[output] = new Node();

      nodes[output]->label = output;

      node->outputs.push_back(nodes[output]);
      nodes[output]->inputs.push_back(node);

    }
  }

}

void Graph::broadcast(){

  for(auto [key, node] : nodes)
    node->fired = false;
  
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

Graph::SubGraphMonitor Graph::get_subgraph_monitor(string label_out){
  
  SubGraphMonitor monitor;
  
  Node * start_node = nodes["broadcaster"];
  Node * end_node = nodes[label_out]->inputs[0];
  
  for(Node * input : end_node->inputs){
    
    monitor.sub_graph_states.push_back({});

    vector<Node *> sub_graph;

    q.push(input);

    while(! q.empty()){
     
      for(Node * n : q.front()->inputs){
        if(find(sub_graph.begin(), sub_graph.end(), n) == sub_graph.end()){

          q.push(n);

          sub_graph.push_back(n);

        }
      }

      q.pop();

    }

    for(Node * n : sub_graph)
      if(n->type == T_FlipFlop)
        monitor.sub_graph_states.back().push_back(& (((FlipFlop*) n)->state));

    monitor.sub_graph_states.back().push_back(& (((Conjunction *) end_node)->fired));

  }

  monitor.periodicity = vector<long>(monitor.sub_graph_states.size(), 0);

  return monitor;

}

int main(){
 
  Graph graph("input.txt");

  Graph::SubGraphMonitor monitor = graph.get_subgraph_monitor("rx");

  while(! monitor.find_periodicity()){

    monitor.print();

    graph.broadcast();

    cout << endl;

  }

//  graph.print();

}
