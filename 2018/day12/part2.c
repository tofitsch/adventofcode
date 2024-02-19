#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 128
#define N_STEPS 500
#define STEP_SIZE 10
#define STEPS 50000000000

typedef struct dll_node dll_node;

struct dll_node{

  bool value;
  bool next_value;

  int id;

  dll_node * next;
  dll_node * prev;

};

void extend_start(dll_node ** start_node, bool value){

   dll_node * prev_start = * start_node;
    
   * start_node = (dll_node *) malloc(sizeof(dll_node));

   (* start_node)->value = value;

   (* start_node)->id = prev_start->id - 1;

   (* start_node)->next = prev_start;
   prev_start->prev = * start_node;

   (* start_node)->prev = NULL;
    
}

void extend_end(dll_node ** end_node, bool value){

   dll_node * prev_end = * end_node;
    
   * end_node = (dll_node *) malloc(sizeof(dll_node));

   (* end_node)->value = value;

   (* end_node)->id = prev_end->id + 1;

   (* end_node)->prev = prev_end;
   prev_end->next = * end_node;

   (* end_node)->next = NULL;

 }

dll_node * read_state(char * line, dll_node ** start_node, dll_node ** end_node){

  line = & line[sizeof("initial state:")];

  * start_node = (dll_node *) malloc(sizeof(dll_node));

  (* start_node)->value = (* line == '#');
  (* start_node)->id = 0;

  (* start_node)->prev = NULL;
  (* start_node)->next = NULL;

  * end_node = * start_node;

  while(* line != '\n'){

    line++;

    extend_end(end_node, (* line == '#'));

  }

}

char to_char(bool arr[], int n){

  char c = 0;

  for(int i=0; i<n; i++)
    c |= (arr[i] << i);

  return c;

}

void read_rule(char * line, bool rules[]){
  
  bool arr[5];

  for(int i=0; i<5; i++)
    arr[i] = (line[i] == '#');

  rules[to_char(arr, 5)] = (line[9] == '#');
  
}

void step(dll_node ** start_node, dll_node ** end_node, bool rules[]){
  
  
  if((* start_node)->value){

    extend_start(start_node, false);
    extend_start(start_node, false);

  }

  if((* end_node)->value){

    extend_end(end_node, false);
    extend_end(end_node, false);

  }

  dll_node * node = * start_node;

  bool arr[5];

  while(node != NULL){

    arr[0] = (node->prev == NULL || node->prev->prev == NULL) ? false : node->prev->prev->value;
    arr[1] = (node->prev == NULL) ? false : node->prev->value;
    arr[2] = node->value;
    arr[3] = (node->next == NULL) ? false : node->next->value;
    arr[4] = (node->next == NULL || node->next->next == NULL) ? false : node->next->next->value;

    node->next_value = rules[to_char(arr, 5)];

    node = node->next;

  }

  node = * start_node;

  while(node != NULL){

    node->value = node->next_value;

    node = node->next;

  }

}

int get_id_sum(dll_node * start_node){

  int id_sum = 0;

  dll_node * node = start_node;

  while(node != NULL){
    
    if(node->value)
      id_sum += node->id;

    node = node->next;

  }

  return id_sum;

}

int main(){
  
  char line[MAX_LINE_LENGTH];
  
  FILE * in_file = fopen("input.txt", "r");

  fgets(line, sizeof(line), in_file);

  dll_node * start_node, * end_node;

  read_state(line, & start_node, & end_node);

  fgets(line, sizeof(line), in_file);

  bool rules[(int) pow(2, 5)];

  memset(rules, false, sizeof(rules));

  while(fgets(line, sizeof(line), in_file) != NULL)
    read_rule(line, rules);

  fclose(in_file);

  long id_sum[3];

  long slope;

  memset(id_sum, 0, sizeof(id_sum));

  int i = 0;

  for(i=0; i<N_STEPS; i++){

    step(& start_node, & end_node, rules);

    if(i % STEP_SIZE == 0){

      id_sum[0] = id_sum[1];
      id_sum[1] = id_sum[2];
      id_sum[2] = get_id_sum(start_node);

    }

    if(id_sum[1] - id_sum[0] == id_sum[2] - id_sum[1]){
      
      slope = (id_sum[1] - id_sum[0]) / STEP_SIZE;

      break;

    }

  }

  printf("%li\n", id_sum[2] + (STEPS - i - 1) * slope);

}
