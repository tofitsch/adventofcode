#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void count(char * c, bool * has2, bool * has3){
  
  int counts[26] = {0};

  while(* c != '\n'){
    
    counts[* c - 'a']++;

    c++;

  }

  for(int i=0; i<26; i++)
    if(counts[i] == 2)
      * has2 = true;
    else if(counts[i] == 3)
      * has3 = true;

}

int main(){
  
  char line[64];

  FILE * in_file = fopen("input.txt", "r");

  int n2 = 0;
  int n3 = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){

    bool has2 = false;
    bool has3 = false;

    count(line, & has2, & has3);

    if(has2) n2++;
    if(has3) n3++;

  }

  fclose(in_file);

  printf("%i\n", n2 * n3);
 
}
