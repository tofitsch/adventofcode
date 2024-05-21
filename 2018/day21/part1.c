#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* 
 not a general solution.
 the following solution R0 comes from observing that in the input only one line is affected by R0:
 ip=28:  eqrr 4 0 5     // R5 = R4 == R0
 when letting the program run (with any value of R0) until it reaches this line one gets the following values in the registers:
 R0=? R1=27 R2=1 R3=1 R4=16128384
 hence, setting R0 to the the value of R4 here yields the solution
*/

#define R0 16128384

#define MAX_LINE_LENGTH 32
#define MAX_OPERATIONS 64
#define OP_LENGTH 4
#define N_REGISTERS 6
#define N_OP_TYPES 16

const char * op_types[N_OP_TYPES] = {
  "addr", "addi", "mulr", "muli",
  "banr", "bani", "borr", "bori",
  "setr", "seti", "gtir", "gtri",
  "gtrr", "eqir", "eqri", "eqrr"
};

int str_to_op_type(char * str) {
  
  for(int i=0; i < N_OP_TYPES; ++i)
    if(strcmp(str, op_types[i]) == 0)
      return i;

  return -1;

}

void read_operation(char * line, int op[]) {

  char * ptr_beg = line;
  char * ptr_end = line;

  for(int i=0; i<OP_LENGTH; ++i){

    while(* ptr_end != ' ' && * ptr_end != '\n')
      ptr_end++;

    * ptr_end = '\0';

    if(i == 0)
      op[i] = str_to_op_type(ptr_beg);
    else
      op[i] = atoi(ptr_beg);

    ptr_beg = ptr_end + 1;

  }

}

void apply(int op[], int reg[]){
  
  switch(op[0]){
    
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

int run(int r0, int * reg, int ip_reg, int (* ops)[OP_LENGTH], int n_ops) {

  int ip = 0;

  memset(reg, 0, sizeof(reg));

  reg[0] = r0;

  int n_steps = 0;
  
  while(ip < n_ops) {
    
    n_steps++;
    
    reg[ip_reg] = ip;

    apply(ops[ip], reg);

    ip = reg[ip_reg] + 1;

    printf("%i\t: ", ip);
    for(int i=0; i<4; ++i)
      printf("%i\t", ops[ip][i]);
    printf(": ");
    for(int i=0; i<6; ++i)
      printf("%i\t", reg[i]);
    printf("\n");

  }

  return n_steps;

}

int main(){
  
  char line[MAX_LINE_LENGTH];

  int reg[N_REGISTERS];

  int ops[MAX_OPERATIONS][OP_LENGTH];

  int n_ops = 0;
  
  FILE * in_file = fopen("input.txt", "r");

  fgets(line, sizeof(line), in_file);

  char * ptr_ip_reg = line;

  while(* ptr_ip_reg != ' ')
    ptr_ip_reg++;

  int ip_reg = atoi(ptr_ip_reg);

  while(fgets(line, sizeof(line), in_file) != NULL)
   read_operation(line, ops[n_ops++]);
  
  fclose(in_file);

  printf("%i\n", run(R0, reg, ip_reg, ops, n_ops));

}
