#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_CHARS 26

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  bool needs[MAX_CHARS][MAX_CHARS];
  bool available[MAX_CHARS];

  memset(available, false, sizeof(available));
  memset(needs, false, sizeof(needs));

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    char a = line[5] - 'A';
    char b = line[36] - 'A';

    available[a] = true;
    available[b] = true;

    needs[a][b] = true;

  }

  fclose(in_file);

  char c = 0;

  while(c != MAX_CHARS){
   
    c = MAX_CHARS;

    for(char i=0; i<MAX_CHARS; i++){

      if(! available[i])
        continue;
      
      for(char j=0; j<MAX_CHARS; j++)
        if(needs[j][i] && available[j])
          goto next;

      if(i > c)
        continue;

      c = i;

      next:;

    }

    if(c != MAX_CHARS){

      printf("%c", c + 'A');
     
      available[c] = false;

    }

  }

  printf("\n");

}
