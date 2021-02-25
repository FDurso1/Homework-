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
  
  if (argc > 3) {
    return 1;
  }
   
  FILE *fptr = NULL;
  fptr = fopen(argv[1], "r");
  
  if (!fptr) {
    return -1;
  }
  int newRes = DEFAULT_RESTRICTION;

  if (argc == 3) {
    newRes = *argv[2] - '0';
    if (newRes < 1) {
      return -2;
    }
  }
  
  int size = -1;
  fscanf(fptr, " %d", &size); 
  read_file(fptr, words, size);
  fclose(fptr);
  
  char hold = '0';
  int input = 0;
  int index = 0;
  char reggy[MAX_INPUT_SIZE+1] = "\0";

  while ((input = scanf(" %c", &hold)) == 1) {
     reggy[index] = hold;
     index++;
  }
  int aSuccess = 0;
  for (int i = 0; i < size; i++) {
    char curWord[MAX_WORD_SIZE+1] = "";
    for (int j = 0; i < MAX_WORD_SIZE+1 && words[i][j] != '\n'; j++) {
      curWord[j] = words[i][j];
      curWord[j+1] = '\0';
    }
    if( match(reggy, curWord, newRes)) {
      aSuccess = 1;
      printf("%s\n", curWord);
    }
  }
  if (aSuccess == 0) {
    printf("No match found for regex '%s'\n", reggy);
  }
  return 0;
}
