#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  
  char line[8];

  FILE * in_file = fopen("input.txt", "r");

  int sum = 0;

  while(fgets(line, sizeof(line), in_file) != NULL)
    sum += atoi(line);

  fclose(in_file);

  printf("%i\n", sum);
 
}
