#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_CHARS 26
#define N_WORKERS 5
#define TIME_FOR_A 61

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  bool needs[MAX_CHARS][MAX_CHARS];
  bool available[MAX_CHARS];
  bool finished[MAX_CHARS];

  memset(available, false, sizeof(available));
  memset(needs, false, sizeof(needs));
  memset(finished, false, sizeof(finished));

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    char a = line[5] - 'A';
    char b = line[36] - 'A';

    available[a] = true;
    available[b] = true;

    needs[a][b] = true;

  }

  fclose(in_file);

  int t = 0;

  char task[N_WORKERS];
  int time[N_WORKERS];

  for(int w=0; w<N_WORKERS; w++){
    task[w] = ' ';
    time[w] = 1;
  }

  bool done = false;

  while(! done){
    
    done = true;

    for(int w=0; w<N_WORKERS; w++){
      
      time[w]--;

      if(time[w] <= 0 && task[w] != ' ')
        finished[task[w] - 'A'] = true;

    }

    for(int w=0; w<N_WORKERS; w++){

      if(time[w] <= 0){
        
        char c = MAX_CHARS;

        for(char i=0; i<MAX_CHARS; i++){

          if(! available[i])
            continue;
          
          for(char j=0; j<MAX_CHARS; j++)
            if(needs[j][i] && ! finished[j])
              goto next;

          if(i > c)
            continue;

          c = i;

          next:;

        }

        if(c != MAX_CHARS){

          task[w] = c + 'A';

          time[w] = TIME_FOR_A + c;
         
          available[c] = false;

        }

      }

      if(time[w] > 0)
        done = false;

    }

    t++;

  }

  printf("%i\n", t - 1);

}

