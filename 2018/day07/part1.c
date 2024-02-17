#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_CHARS 26

int char_compare(const void *a, const void *b){

  return (*(char*)b - *(char*)a);
  
}

bool is_in_arr(char c, char arr[], int n) {

  for(int i=0; i<n; i++)
    if(arr[i] == c)
      return true;

  return false;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  char char_present[MAX_CHARS];

  char must_be_before[MAX_CHARS][MAX_CHARS];
  int n_must_be_before[MAX_CHARS];

  char must_be_after[MAX_CHARS][MAX_CHARS];
  char n_must_be_after[MAX_CHARS];

  memset(n_must_be_before, 0, sizeof(n_must_be_before));
  memset(n_must_be_after, 0, sizeof(n_must_be_after));
  memset(char_present, false, sizeof(char_present));

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    char a = line[5] - 'A';
    char b = line[36] - 'A';

    char_present[a] = true;
    char_present[b] = true;

    char i = 0;

    if(! is_in_arr(a, must_be_before[b], n_must_be_before[b])){
      
      must_be_before[n_must_be_before[b]][b] = a;

      n_must_be_before[b]++;

    }

    if(! is_in_arr(a, must_be_after[a], n_must_be_after[a])){
      
      must_be_after[n_must_be_after[a]][a] = b;

      n_must_be_after[a]++;

    }

  }

  fclose(in_file);

  char str[MAX_CHARS];

  char n_chars = 0;

  for(char i=0; i<MAX_CHARS; i++){
    if(char_present[i]){

      str[n_chars] = i;

      n_chars++;

    }
  }

  for(char i=0; i<n_chars; i++)
    printf("%c", str[i] + 'A');
  printf("\n");

  for(char i=0; i<n_chars; i++){
    
    char c = str[i];

    printf("%c: ", 'A' + c);

    for(int j=0; j<n_must_be_before[c]; j++)
      printf("%c", must_be_before[j][c] + 'A');

    printf(",");

    for(char j=0; j<n_must_be_after[c]; j++)
      printf("%c", must_be_after[j][c] + 'A');

    printf("\n");

  }

  char start;

  for(char i=0; i<n_chars; i++){
    if(n_must_be_after[str[i]] == 0){
      
      start = str[i];

      break;

    }
  }


  printf("start: %c\n\n", start + 'A');

  char order[1000][MAX_CHARS];
  int n_y[MAX_CHARS];
  int x = 0;

  memset(n_y, 0, sizeof(n_y));

  order[0][0] = start;
  n_y[0] = 1;

  bool done = false;

  while(! done){
    
    done = true;
    
    for(int y=0; y<n_y[x]; y++){
//      printf("TEST %i %c\n", n_must_be_before[order[y][x]], order[y][x] + 'A');
      for(int i=0; i<n_must_be_before[order[y][x]]; i++){
        
        order[n_y[x + 1]][x + 1] = must_be_before[i][order[y][x]];

//        printf("%i %i %c%c\n", n_y[x + 1], x + 1, order[n_y[x + 1]][x + 1] + 'A', order[y][x] + 'A');

        n_y[x + 1]++;

        done = false;

      }
    }

    x++;

  }

  int N = 10000; //XXX
  char result[N + 1];

  memset(result, '\0', sizeof(result));

  char * ptr = result + N;

  for(char X=0; X<x; X++){

    printf("TEST %i %i \n", X, n_y[X]);

    char col[n_y[X]];

    for(int Y=0; Y<n_y[X]; Y++)
      col[Y] = order[Y][X];

    qsort(col, n_y[X], sizeof(char), char_compare);

    for(int Y=0; Y<n_y[X]; Y++){
      if(col[Y] + 'A' != * ptr){
        printf("%c", col[Y] + 'A');
        
        ptr--;

        * ptr = col[Y] + 'A';

      }
    }

    printf("\n");

  }

  printf("%s\n", ptr);


  memset(char_present, false, sizeof(char_present));

  char solution[N];

  memset(solution, '\0', sizeof(solution));

  int i = 0;

  while(* ptr != '\0'){
    
    if(!char_present[* ptr - 'A']){

      solution[i] = * ptr;

      i++;

    }

    char_present[* ptr - 'A'] = true;

    ptr++;

  }

  printf("%s\n", solution);

}
