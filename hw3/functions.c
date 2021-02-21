#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  printf("read_file start\n");
  
  char cur = 'w';
  
  //get rid of first line
  while (fscanf(fp, "%c", &cur) != 0) {
      if (cur == '\n') {
	break;
      }
  }
  
  
  for (int i = 0; i < size; i++) {
    printf("Word %d:\n", i);
    int j = 0;
    while (fscanf(fp, "%c", &cur) != 0) {
	printf("%c", cur);
	words[i][j] = cur;
	if (cur == '\n') {
	  break;
	  //end of word found
	}
	j++;
	//cur = 0;
    }
  }
  return 0;
}




int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf("match start\n");
  printf(" %s %s %d\n", regex, word, restriction);
  return 0;
}


