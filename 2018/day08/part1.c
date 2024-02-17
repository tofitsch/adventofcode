#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct tree_node tree_node;

struct tree_node{
  
  int n_nodes;
  int n_data;

  tree_node * nodes;
  int * data;

};

void read_tree_node(tree_node * node, FILE * in_file, int * sum_data){
  
  fscanf(in_file, "%d", & (node->n_nodes));
  node->nodes = (tree_node *) malloc(node->n_nodes * sizeof(tree_node));

  fscanf(in_file, "%d", & (node->n_data));
  node->data = (int *) malloc(node->n_data * sizeof(int));


  for(int i=0; i<node->n_nodes; i++){

    tree_node new_node;

    read_tree_node(& new_node, in_file, sum_data);

  }

  for(int i=0; i<node->n_data; i++){

    fscanf(in_file, "%d", & (node->data[i]));

    * sum_data += node->data[i];

  }

}

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  int sum_data = 0;

  tree_node start;

  read_tree_node(& start, in_file, & sum_data);

  fclose(in_file);

  printf("%i\n", sum_data);

}
