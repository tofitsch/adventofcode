#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 60000

char const capital_offset = 'a' - 'A';

typedef struct dll_node dll_node;

struct dll_node{
  
  char value;

  dll_node * next;
  dll_node * prev;

};

bool will_react(dll_node * a, dll_node * b){

  return abs(a->value - b->value) == capital_offset;

}

void remove_pair(dll_node * node, dll_node * start_node, dll_node * reacting_nodes[], int * n_reacting_nodes){

  if(node == start_node)
    start_node = node->next->next;

  if(node->prev != NULL && node->next->next != NULL && will_react(node->prev, node->next->next)){

    reacting_nodes[* n_reacting_nodes] = node->prev;
    
    (* n_reacting_nodes)++;

  }

  if(node->next->next != NULL)
    node->next->next->prev = node->prev;

  if(node->prev != NULL)
    node->prev->next = node->next->next;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  fclose(in_file);

  dll_node * dll[MAX_LINE_LENGTH];
  dll_node * reacting_nodes[MAX_LINE_LENGTH];
  int n_reacting_nodes = 0;

  dll_node * start_node = NULL;

  int n = 0;

  while(line[n] != '\n'){

    dll[n] = (dll_node *) malloc(sizeof(dll_node));

    dll[n]->value = line[n];

    dll[n]->prev = NULL;
    dll[n]->next = NULL;

    if(n > 0){
      
      dll[n]->prev = dll[n - 1];
      dll[n - 1]->next = dll[n];

    }
    else
      start_node = dll[n];

    if(n > 0 && will_react(dll[n], dll[n - 1])){

      reacting_nodes[n_reacting_nodes] = dll[n - 1];

      n_reacting_nodes++;

    }

    n++;

  }

  for(int i=0; i<n_reacting_nodes; i++){
    remove_pair(reacting_nodes[i], start_node, reacting_nodes, & n_reacting_nodes);
    printf("%i %i\n", i, n_reacting_nodes);
  }

  dll_node * node = start_node;

  int ctr = 0;

  do{
    printf("%c", node->value);
    ctr++;
  }while((node = node->next) != NULL);

  printf("\n%i\n", ctr);

}
