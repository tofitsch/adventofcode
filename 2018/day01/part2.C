#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int find_repeating_sum(FILE * in_file){

  char line[8];

  int sum = 0;

  int ctr = 0;

  int mem[1000000];

  while(true){

    while(fgets(line, sizeof(line), in_file) != NULL){

      char * token = strtok(line, " ");

      while(token != NULL){

        sum += atoi(token);

        for(int i=0; i<=ctr; i++)
          if(mem[i] == sum)
            return sum;

        mem[ctr] = sum;

        ctr++;

        token = strtok(NULL, " ");

      }

    }

    fseek(in_file, 0, SEEK_SET);

  }

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  printf("%i\n", find_repeating_sum(in_file));

  fclose(in_file);
  
}

