#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 16
#define SOLUTION_LENGTH 10
#define START_0 3
#define START_1 7

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  int pos_solution = atoi(line);

  fclose(in_file);

  char scores[pos_solution + SOLUTION_LENGTH];

  scores[0] = START_0;
  scores[1] = START_1;

  int n_scores = 2;

  int pos_0 = 0;
  int pos_1 = 1;

  while(n_scores < pos_solution + SOLUTION_LENGTH){
    
    char num = scores[pos_0] + scores[pos_1];

    if(num > 9){
      
      scores[n_scores] = num / 10;

      n_scores++;
      
    }

    scores[n_scores] = num % 10;

    n_scores++;
    
    pos_0 += scores[pos_0] + 1;
    pos_1 += scores[pos_1] + 1;

    pos_0 %= n_scores;
    pos_1 %= n_scores;

  }

  for(int i=pos_solution; i<pos_solution + SOLUTION_LENGTH; i++)
    printf("%c", scores[i] + '0');

  printf("\n");

}
