#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 32
#define MAX_EXAMPLES 2000

typedef struct example example;

struct example{
  
  int before[4];
  int operation[4];
  int after[4];

};

void read_register(char * line, int reg[]){

  reg[0] = line[9]  - '0';
  reg[1] = line[12] - '0';
  reg[2] = line[15] - '0';
  reg[3] = line[18] - '0';

}

void read_operation(char * line, int operation[]){

  char * ptr_beg = line;
  char * ptr_end = line;

  for(int i=0; i<4; i++){

    while(* ptr_end != ' ' && * ptr_end != '\n')
      ptr_end++;

    * ptr_end = '\0';

    operation[i] = atoi(ptr_beg);

    ptr_beg = ptr_end + 1;

  }

}

bool read_example(FILE * in_file, example examples[], int * n_examples){
  
  example * ex = & examples[* n_examples];
  
  char line[MAX_LINE_LENGTH];
  
  fgets(line, sizeof(line), in_file);

  if(line[0] == '\n'){

    //TODO: better way to skip 3 lines
    fgets(line, sizeof(line), in_file);
    fgets(line, sizeof(line), in_file);
    fgets(line, sizeof(line), in_file);

    return false;

  }

  read_register(line, ex->before);
  
  fgets(line, sizeof(line), in_file);

  read_operation(line, ex->operation);

  fgets(line, sizeof(line), in_file);

  read_register(line, ex->after);

  fgets(line, sizeof(line), in_file); //TODO: better way to skip 1 line

  (* n_examples)++;

  for(int i=0; i<4; i++)
    printf("%i ", ex->before[i]);
  printf("\n");
  for(int i=0; i<4; i++)
    printf("%i ", ex->operation[i]);
  printf("\n");
  for(int i=0; i<4; i++)
    printf("%i ", ex->after[i]);
  printf("\n\n");

  return true;


}

int main(){

  example examples[MAX_EXAMPLES];

  int n_examples;
  
  FILE * in_file = fopen("input.txt", "r");

  while(read_example(in_file, examples, & n_examples))
    continue;

  fclose(in_file);

}
