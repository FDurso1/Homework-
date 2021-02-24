#include <stdio.h>
#include <string.h>

#include "functions.h"


#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10

int read_file(FILE *fp, char words[][MAX_WORD_SIZE +1], int size); //declare
int match(const char *regex, const char *word, int restriction); //declare

int main(int argc, const char *argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ]; 
    // TODO: Implement me!
  printf("main\n");
  if (argc !=2) {
    printf("specify a file name / just one file name");
    return 1;
  }
   
  FILE *fptr = NULL;
  fptr = fopen(argv[1], "r");
  
  if (!fptr) {
    printf("file open error\n");
    return -1;
  }
  
  printf("fptr exists\n");
  int size = -1;
  fscanf(fptr, " %d", &size);

  printf("size of file is %d\n", size);
  
  read_file(fptr, words, size);
  fclose(fptr);
  /*  printf("testing the words array\n");
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < MAX_WORD_SIZE +1 && words[i][j] != '\n'; j++) {
      printf("%c", words[i][j]);
    }
    printf("\n");
    } */
  char hold = '0';
  int input = 0;
  int z = 0;
  char reggy[MAX_INPUT_SIZE+1] = "\0";
  while ((input = scanf(" %c", &hold)) == 1) {
     reggy[z] = hold;
     z++;
  }
   printf("reggex expression: ");
   /* for (int i = 0; i < z; i++) {
    printf("%c", reggy[i]);
  }
  printf("\n"); */
  printf("%s\n", reggy);
  
  for (int i = 0; i < size; i++) {
    char curWord[MAX_WORD_SIZE+1] = "";
    for (int j = 0; i < MAX_WORD_SIZE+1 && words[i][j] != '\n'; j++) {
      curWord[j] = words[i][j];
      curWord[j+1] = '\0';
    }
    printf("testing whether %s is found by %s\n", curWord, reggy);
    if( match(reggy, curWord, 10)) {
      printf("%s\n", curWord);
    }
  }



  
    return 0;
}
