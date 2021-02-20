#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  printf("read_file start\n");
  char cur = '0';
  for (int i = 0; i < size; i++) {
    printf("i: %d\n", i);
    int j = 0;
    while ((cur = fscanf(fp, " %c", &cur) != '\n')) {
	printf("j: %d, cur: %c\n", j, cur);
	words[i][j] = cur;
	j++;
	if (j > 40) {
	  return -1;
	}
    }
  }
  return 0;
}




int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf(" %s %s %d\n", regex, word, restriction);
  return 0;
}


