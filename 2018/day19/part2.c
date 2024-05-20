#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

int main(){
  
  char line[MAX_LINE_LENGTH];

  int reg[N_REGISTERS];

  memset(reg, 0, sizeof(reg));

  reg[0] = 1;

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

  int ip = 0;

  while(ip < n_ops) {

    reg[ip_reg] = ip;

    apply(ops[ip], reg);

    ip = reg[ip_reg] + 1;

    /* 
      * printing out the values of all registers R for each step while running the programm reveals that R0 changes by +R3 every time R3 is a factor of R2 
      * note that every time that happens R1 * R3 = R2 and the instruction pointer is ip=8
      * this involves a lot of incrementing by 1 to reach and would therefore run way too long
      * hence, the following insert to skip most of these steps
    */
    if(ip == 8) {

      if(reg[2] % reg[3] == 0)
        reg[0] += reg[3];

      reg[1] = reg[2];
      reg[5] = 0;

    }

  }

  // the last factor or R2 (which is its value itself) is added twice and therefore has to be subtracted again here
  printf("%i\n", reg[0] - reg[2]);

}
