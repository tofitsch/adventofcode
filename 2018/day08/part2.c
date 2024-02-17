#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct tree_node tree_node;

struct tree_node{
  
  int n_nodes;
  int n_data;

  tree_node * nodes;
  int * data;

  int value;

};

void read_tree_node(tree_node * node, FILE * in_file){
  
  node->value = 0;
  
  fscanf(in_file, "%d", & node->n_nodes);
  node->nodes = (tree_node *) malloc(node->n_nodes * sizeof(tree_node));

  fscanf(in_file, "%d", & node->n_data);
  node->data = (int *) malloc(node->n_data * sizeof(int));

  for(int i=0; i<node->n_nodes; i++)
    read_tree_node(& node->nodes[i], in_file);

  for(int i=0; i<node->n_data; i++){

    fscanf(in_file, "%d", & (node->data[i]));

    if(node->n_nodes == 0)
      node->value += node->data[i];
    else if(node->data[i] > 0 && node->data[i] <= node->n_nodes)
      node->value += node->nodes[node->data[i] - 1].value;

  }

}

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  tree_node start;

  read_tree_node(& start, in_file);

  fclose(in_file);

  printf("%i\n", start.value);

}
