#include <stdio.h>
#include <stdlib.h>
#include "../../clib/set.c"

int find_repeating_sum(FILE * in_file){

  set * s = set_create();

  int terms[1000];

  char line[8];

  int sum = 0;

  int ctr = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){

    terms[ctr] = atoi(line);

    ctr++;

  }

  int n_terms = ctr;

  ctr = 0;

  while(true){

    sum += terms[ctr];

    if(! set_insert(s, sum))
      return sum;

    ctr++;

    if(ctr >= n_terms)
      ctr = 0;

  }

  set_free(s);

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  printf("%i\n", find_repeating_sum(in_file));

  fclose(in_file);
  
}
