#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 60000

typedef struct dll_node dll_node;

struct dll_node{
  
  char value;

  dll_node * next;
  dll_node * prev;

};

bool will_react(dll_node * a, dll_node * b){

  return abs(a->value - b->value) == abs('a' - 'A');

}

void remove_pair(dll_node * node, dll_node ** start_node, dll_node * reacting_nodes[], int * n_reacting_nodes){
  
  if(! will_react(node, node->next))
    return;
  
  if(node->prev != NULL && node->next->next != NULL && will_react(node->prev, node->next->next)){

    reacting_nodes[* n_reacting_nodes] = node->prev;
    
    (* n_reacting_nodes)++;

  }

  if(node == * start_node){
    * start_node = node->next->next;
  }

  node->value = ' ';
  node->next->value = ' ';

  if(node->next->next != NULL)
    node->next->next->prev = node->prev;

  if(node->prev != NULL)
    node->prev->next = node->next->next;

}

int get_final_length(char * line){

  dll_node * reacting_nodes[MAX_LINE_LENGTH];
  int n_reacting_nodes = 0;

  int n = 0;

  bool prev_node_reacts = false;

  dll_node * prev_node = NULL;
  dll_node * start_node = NULL;

  while(line[n] != '\n'){

    dll_node * new_node = (dll_node *) malloc(sizeof(dll_node));

    new_node->value = line[n];

    new_node->prev = NULL;
    new_node->next = NULL;

    if(n > 0){
      
      new_node->prev = prev_node;
      prev_node->next = new_node;

    }
    else
      start_node = new_node;

    if(n > 0 && will_react(new_node, prev_node) && ! prev_node_reacts){

      reacting_nodes[n_reacting_nodes] = prev_node;

      n_reacting_nodes++;

      prev_node_reacts = true;

    }
    else
      prev_node_reacts = false;

    prev_node = new_node;

    n++;

  }

  for(int i=0; i<n_reacting_nodes; i++)
    remove_pair(reacting_nodes[i], & start_node, reacting_nodes, & n_reacting_nodes);

  int ctr = 1;

  dll_node * node = start_node;

  while((node = node->next) != NULL)
    ctr++;

  return ctr;

}

char * remove_letter(char * str_in, char c){
  
  char * str_out = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));

  char * str_out_itr = str_out;

  while(* str_in != '\0'){
    
    if(* str_in != c && * str_in != c + - 'a' + 'A'){

      * str_out_itr = * str_in;

      str_out_itr++;

    }
    
    str_in++;

  }

  str_out_itr = '\0';

  return str_out;
  
}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char full_line[MAX_LINE_LENGTH];

  fgets(full_line, sizeof(full_line), in_file);

  fclose(in_file);

  int min = -1;

  for(char c='a'; c<='z'; c++){

    char * line = remove_letter(full_line, c);

    int length = get_final_length(line);

    if(min < 0 || length < min)
      min = length;

  }

  printf("%i\n", min);

}
