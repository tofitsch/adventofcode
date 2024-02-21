#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 16
#define MAX_CHARS 50000000
#define START_0 3
#define START_1 7

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  int length = strlen(line) - 1;

  line[length] = '\0';

  fclose(in_file);

  char * scores = malloc(MAX_CHARS * sizeof(char));
  
  memset(scores, '\0', sizeof(scores));

  scores[0] = '3';
  scores[1] = '7';

  long n_scores = 2;

  long pos_0 = 0;
  long pos_1 = 1;

  while(n_scores - length < 0 || strcmp(line, scores + n_scores - length) != 0){
    
    char num = scores[pos_0] - '0' + scores[pos_1] - '0';

    if(num > 9){

      scores[n_scores++] = '1';

      if(strcmp(line, scores + n_scores - length) == 0)
        break;

    }

    scores[n_scores++] = num % 10 + '0';

    pos_0 += scores[pos_0] - '0' + 1;
    pos_1 += scores[pos_1] - '0' + 1;

    pos_0 %= n_scores;
    pos_1 %= n_scores;

  }

  printf("%li\n", n_scores - length);

}
