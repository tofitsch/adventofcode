#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 64

typedef struct dll_node dll_node;

struct dll_node{

  int value;

  dll_node * next;
  dll_node * prev;

};

void read_line(char * line, int * n_players, int * n_marbels){
  
  char * ptr = line;

  while(* ptr != ' ')
    ptr++;

  * ptr = '\0';

  * n_players = atoi(line);

  ptr += sizeof("players; last marble is worth ");

  line = ptr;

  while(* ptr != ' ')
    ptr++;

  * ptr = '\0';

  * n_marbels = atoi(line) + 1;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  int n_players, n_marbels;

  read_line(line, & n_players, & n_marbels);

  fclose(in_file);

  int score[n_players];

  memset(score, 0, sizeof(score));

  dll_node node;

  node.value = 0;

  node.next = & node;
  node.prev = & node;

  dll_node * current = & node;

  for(int i=1; i<n_marbels; i++){
    
    if(i % 23 == 0){
      
      int player = (i - 1) % n_players;

      for(int j=0; j<6; j++)
        current = current->prev;

      score[player] += i + current->prev->value;

      current->prev->prev->next = current;

      current->prev = current->prev->prev;

    }
    else{

      dll_node * new_node = (dll_node *) malloc(sizeof(dll_node));

      new_node->value = i;

      new_node->prev = current->next;
      new_node->next = current->next->next;

      current = new_node;

      current->prev->next = new_node;
      current->next->prev = new_node;

    }

  }

  int max = 0;

  for(int i=0; i<n_players; i++)
    if(score[i] > max)
      max = score[i];

  printf("%i\n", max);

}
