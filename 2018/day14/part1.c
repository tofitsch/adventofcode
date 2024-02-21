#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 16
#define MAX_SCORES 1048576
#define MAX_DIGITS 16
#define SOLUTION_LENGTH 10
#define START_0 3
#define START_1 7

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  int pos_solution = atoi(line);

  fclose(in_file);

  int n_scores = 2;

  int scores[MAX_SCORES];

  scores[0] = START_0;
  scores[1] = START_1;

  int pos_0 = 0;
  int pos_1 = 1;

  while(n_scores < pos_solution + SOLUTION_LENGTH){
    
    int num = scores[pos_0] + scores[pos_1];
    
    char digits_str[MAX_DIGITS];

    sprintf(digits_str, "%d", num);

    for(int i=0; digits_str[i]!='\0'; i++){
      
      scores[n_scores] = digits_str[i] - '0';

      n_scores++;

    }

    pos_0 += scores[pos_0] + 1;
    pos_1 += scores[pos_1] + 1;

    pos_0 %= n_scores;
    pos_1 %= n_scores;

//    for(int i=0; i<n_scores; i++)
//      printf("%i ", scores[i]);
//
//    printf("\n");

  }

  for(int i=pos_solution; i<pos_solution + SOLUTION_LENGTH; i++)
    printf("%i", scores[i]);

  printf("\n");

}
