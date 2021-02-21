#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  printf("read_file start\n");
  
  char curr[MAX_WORD_SIZE+1]= "";
  fgets(curr, MAX_WORD_SIZE+1, fp);
  //get rid of first line (which originally contained the number of lines)
  
  
  for (int i = 0; i < size; i++) {
    printf("Word %d:\n", i);
    fgets(curr, MAX_WORD_SIZE+1, fp);
    printf("curr: %s\n", curr);

    for (int j = 0; j < MAX_WORD_SIZE && curr[j] != '\0'; j++) {
      words[i][j] = curr[j];
    }
  }
  return 0;
}


int getWordSize(const char *word) {
  int i = 0;
  for (i = 0; i < MAX_WORD_SIZE +1 && word[i] != '\0'; i++){}
  return i;

}

int simpleMatch(const char *regex, const char *word);

int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf("match start\n");
  //  int toReturn = 1;
  
  //if the regex expression is just a word in the list
  if (simpleMatch(regex, word) == 1) {
    return 1;
  }
  int wordSize =  getWordSize(word);
  printf("The size of the word being assessed is %d\n", wordSize);

  
  for (int i = 0; i < MAX_WORD_SIZE && regex[i] != '\0'; i++) {
    
  }

  
  printf(" %s %s %d\n", regex, word, restriction);
  return 0;
}
    /*
int star(const char *regex, const char *word) {

  return 0;
}

int question(const char *regex, const char *word) {

  return 0;
}
    

int tilde(const char *regex, const char *word, int restriction) {
  
  return 0;
}
    */

/*
  This method is used to check whether the regex expression is just a 
 */
int simpleMatch(const char* regex, const char* word) {
  for(int i = 0; i < MAX_WORD_SIZE+1; i++) {
    if (regex[i] != word[i]) {
      return 0;
    }
  }
  return 1;
}
    
int isSorQ(char c) {
  return (c == '*' || c == '?' || c == '~');
} 
