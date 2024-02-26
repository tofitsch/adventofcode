#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 32
#define MAX_EXAMPLES 2000
#define MAX_OPERATIONS 2000
#define N_OPS 16

#define INF 1000

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

  if(line[0] == '\n')
    return false;

  read_register(line, ex->before);
  
  fgets(line, sizeof(line), in_file);

  read_operation(line, ex->operation);

  fgets(line, sizeof(line), in_file);

  read_register(line, ex->after);

  fgets(line, sizeof(line), in_file);

  (* n_examples)++;

  return true;


}

void apply(int op_id, int op[], int reg[]){
  
  switch(op_id){
    
    case 0: //addr
      reg[op[3]] = reg[op[1]] + reg[op[2]];
      break;

    case 1: //addi
      reg[op[3]] = reg[op[1]] + op[2];
      break;

    case 2: //mulr
      reg[op[3]] = reg[op[1]] * reg[op[2]];
      break;

    case 3: //muli
      reg[op[3]] = reg[op[1]] * op[2];
      break;

    case 4: //banr
      reg[op[3]] = reg[op[1]] & reg[op[2]];
      break;

    case 5: //bani
      reg[op[3]] = reg[op[1]] & op[2];
      break;

    case 6: //borr
      reg[op[3]] = reg[op[1]] | reg[op[2]];
      break;

    case 7: //bori
      reg[op[3]] = reg[op[1]] | op[2];
      break;

    case 8: //setr
      reg[op[3]] = reg[op[1]];
      break;

    case 9: //seti
      reg[op[3]] = op[1];
      break;

    case 10: //gtir
      reg[op[3]] = op[1] > reg[op[2]] ? 1 : 0;
      break;

    case 11: //gtri
      reg[op[3]] = reg[op[1]] > op[2] ? 1 : 0;
      break;

    case 12: //gtrr
      reg[op[3]] = reg[op[1]] > reg[op[2]] ? 1 : 0;
      break;

    case 13: //eqir
      reg[op[3]] = op[1] == reg[op[2]] ? 1 : 0;
      break;

    case 14: //eqri
      reg[op[3]] = reg[op[1]] == op[2] ? 1 : 0;
      break;

    case 15: //eqrr
      reg[op[3]] = reg[op[1]] == reg[op[2]] ? 1 : 0;
      break;

  };

}

bool registers_eq(int a[], int b[]){
  
  for(int i=0; i<4; i++)
    if(a[i] != b[i])
      return false;

  return true;

}

bool solve_step(bool (* a)[N_OPS], int b[], bool transpose){

  int last_x_true, y;
  
  for(y=0; y<N_OPS; y++){
    
    last_x_true = -1;

    for(int x=0; x<N_OPS; x++)
      if(a[y][x])
        if(last_x_true < 0)
          last_x_true = x;
        else
         goto next;

    if(last_x_true != -1)
      break;

    next:;

  }

  if(last_x_true == -1)
    return false;

  b[last_x_true] = y;

  for(int y=0; y<N_OPS; y++)
    a[y][last_x_true] = false;

  return true;

}

void solve(bool (* a)[N_OPS], int b[]){
  
  int n_solves = 0;

  while(n_solves < N_OPS)
    n_solves += solve_step(a, b, false);

}

int main(){

  example examples[MAX_EXAMPLES];

  int n_examples = 0;

  example operations[MAX_OPERATIONS];

  int n_operations = 0;
  
  FILE * in_file = fopen("input.txt", "r");

  while(read_example(in_file, examples, & n_examples))
    continue;

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  while(fgets(line, sizeof(line), in_file) != NULL)
    read_operation(line, operations[n_operations++].operation);

  fclose(in_file);

  bool incidence_mtx[N_OPS][N_OPS];

  memset(incidence_mtx, true, sizeof(incidence_mtx));

  for(int i=0; i<n_examples; i++){
    
    example * ex = & examples[i];

    for(int j=0; j<N_OPS; j++){
      
      int reg[4];

      memcpy(reg, ex->before, sizeof(reg));
      
      apply(j, ex->operation, reg);

      if(! registers_eq(reg, ex->after))
        incidence_mtx[j][ex->operation[0]] = false;

    }

  }

  int encoding[N_OPS];

  solve(incidence_mtx, encoding);

  int reg[4] = {0, 0, 0, 0};

  for(int i=0; i<n_operations; i++)
    apply(encoding[operations[i].operation[0]], operations[i].operation, reg);
 
  printf("%i\n", reg[0]);

}
