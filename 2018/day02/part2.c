#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int differ_by_one(char * a, char * b){
  
  int i = 0;

  int pos = -1;

  while(a[i] != '\n'){
    
    if(a[i] != b[i])
      if(pos >= 0)
        return -1;
      else
        pos = i;

    if(b[i] == '\n')
      return -1;

    i++;

  }

  return pos;

}

int main(){
  
  char line[64];
  char * lines[500];

  int line_ctr = 0;

  FILE * in_file = fopen("input.txt", "r");

  while(fgets(line, sizeof(line), in_file) != NULL){

    lines[line_ctr] = malloc(strlen(line) + 1);

    strcpy(lines[line_ctr], line);

    line_ctr++;

  }

  for(int i=0; i<line_ctr; i++){
    for(int j=i+1; j<line_ctr; j++){

      int index = differ_by_one(lines[i], lines[j]);

      if(index >= 0){
        
        int k = 0;
        
        while(lines[i][k] != '\0'){
          
          if(k != index)
            printf("%c", lines[i][k]);

          k++;

        }
      }

    }
  }

  fclose(in_file);

}
