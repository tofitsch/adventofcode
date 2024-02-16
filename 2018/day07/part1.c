#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_CHARS 26

int a_less_than_b(const void *a, const void *b) {

  return * (int *) b - * (int *) a;

}

bool is_in_arr(int num, int arr[], int n) {

  for(int i=0; i<n; i++)
    if(arr[i] == num)
      return true;

  return false;

}

int main(){

  FILE * in_file = fopen("example.txt", "r");

  char line[MAX_LINE_LENGTH];

  char char_present[MAX_CHARS];

  int must_be_before[MAX_CHARS][MAX_CHARS];
  int n_must_be_before[MAX_CHARS];
  int must_be_after[MAX_CHARS][MAX_CHARS];
  int n_must_be_after[MAX_CHARS];

  memset(n_must_be_before, 0, sizeof(n_must_be_before));
  memset(n_must_be_after, 0, sizeof(n_must_be_after));
  memset(char_present, false, sizeof(char_present));

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    int a = line[5] - 'A';
    int b = line[36] - 'A';

    char_present[a] = true;
    char_present[b] = true;

    int i = 0;

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

  int n_chars = 0;

  for(int i=0; i<MAX_CHARS; i++){
    if(char_present[i]){

      str[n_chars] = i;

      n_chars++;

    }
  }

  for(int i=0; i<n_chars; i++)
    printf("%c", str[i] + 'A');
  printf("\n");

  for(int i=0; i<n_chars; i++){
    
    char c = str[i];

    printf("%c: ", 'A' + c);

    for(int j=0; j<n_must_be_before[c]; j++)
      printf("%c", must_be_before[j][c] + 'A');

    printf(",");

    for(int j=0; j<n_must_be_after[c]; j++)
      printf("%c", must_be_after[j][c] + 'A');

    printf("\n");

  }

  int start;

  for(int i=0; i<n_chars; i++){
    if(n_must_be_after[str[i]] == 0){
      
      start = str[i];

      break;

    }
  }

  printf("%c\n\n", start + 'A');

  char order[MAX_CHARS][MAX_CHARS];
  int n_y[MAX_CHARS];
  int x = 0;

  memset(n_y, 0, sizeof(n_y));

  order[0][0] = start;
  n_y[0] = 1;

  bool done = false;

  while(! done){
    
    done = true;
    
    for(int y=0; y<n_y[x]; y++){
      for(int i=0; i<n_must_be_before[order[y][x]]; i++){

        order[n_y[x + 1]][x + 1] = must_be_before[i][order[y][x]];

        n_y[x + 1]++;

        done = false;

      }
    }

    x++;

  }

  char result[MAX_CHARS + 1];

  memset(result, '\0', sizeof(result));

  char * ptr = result + MAX_CHARS;

  for(int X=0; X<x; X++){

//    qsort(order[X], n_y[X], sizeof(char), a_less_than_b);

    for(int Y=0; Y<n_y[X]; Y++){
      printf("%c", order[Y][X] + 'A');
      if(order[Y][X] + 'A' != * ptr){
        
        ptr--;

        * ptr = order[Y][X] + 'A';

      }
    }

    printf("\n");

  }

//  while(* result == '\0')
//   (result)++;

  printf("%s\n", ptr);

}
