#include <stdio.h>
#include <string.h>

#include "functions.h"


#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10

int read_file(FILE *fp, char words[][MAX_WORD_SIZE +1], int size); //declare

int main(int argc, const char *argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ]; 
    // TODO: Implement me!
  printf("main\n");
  printf("argc: %d\n", argc);
  printf("argv[1] = %s\n", argv[1]);
  FILE* fptr;
  fptr = fopen("input.txt", "w");
  fprintf(fptr, "5\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa");
  fclose(fptr);
  if (!fptr) {
    printf("no file exists\n");
    return -1;
  }
  printf("fptr exists\n");
  int size = fscanf(fptr, " %d", &size);
  printf("size of file is %d\n", size);
  
  read_file(fptr, words, 5);
    return 0;
}
