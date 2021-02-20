#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  printf("read_file start\n");
  char cur[] = NULL;
  
  for (int i = 0; i < size; i++) {
    printf("Word %d:\n", i);
    int j = 0;
    while ((fscanf(fp, "%s", &cur) != 0) {
	printf("%c", cur);
	words[i][j] = cur;
	j++;
    }
  }
  return 0;
}




int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf(" %s %s %d\n", regex, word, restriction);
  return 0;
}


