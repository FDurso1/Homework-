#include "functions.h"

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 128

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

int getRegexSize(const char *regex) {
  int i = 0;
  for (i = 0; i < MAX_INPUT_SIZE +1 && regex[i] != '\0'; i++){}
  return i;
}

int simpleMatch(const char *regex, const char *word);
int isWild(char c);
int recursiveSolution(const char *regex, const char *word, int *regIdxP, int *wordIdxP);

char* getLettersUntilNextWild(const char *regex, const char *word, int *regIdxP, int *wordIdxP);

int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf("match start\n");
  //  int toReturn = 1

  //if the regex expression is just a word in the list
  if (simpleMatch(regex, word) == 1) {
    return 1;
  }
  
  int wordSize =  getWordSize(word);
  printf("The size of the word being assessed is %d\n", wordSize);

  int regSize = getRegexSize(regex);
  printf("The size of the regex being assessed is %d\n", regSize);

  
  int *regIdxP = 0;
  int *wordIdxP = 0;

  int works =  recursiveSolution(regex, word, regIdxP, wordIdxP);
  
  printf(" %s %s %d\n", regex, word, restriction);
  return works;
}

int recursiveSolution(const char *regex, const char *word, int *regIdxP, int *wordIdxP) {
  //while regIdx < regSize
  //getLetters()
  printf("%s%s%d%d\n", regex, word, *regIdxP, *wordIdxP);
  return 0;
}

    char* getLettersUntilNextWild(const char *regex, const char *word, int *regIdxP, int *wordIdxP) {
      
    char* toReturn[MAX_WORD_SIZE+1];
    toReturn[0] = '\0';
    int startIdx = *regIdxP;
    
    while (isWild(regex[*regIdxP]) == 1) {
      strncat(toReturn, regex[*regIdxP], 1);
      strncat(toReturn, '\0', 1);
      *regIdxP++;
    }
    if (regex[*regIdxP] == '*' || regex[*regIdxP] == '?') {
      *regIdxP--;
      toReturn[*regIdxP] = '\0';
    }
    if (*regIdx - startIdx > 0) {
      if (compareStrings(toReturn, word, wordIdxP) == 0) {
	printf("the non-wild related characters starting from %d do not match those in the regex string at %d\n", *wordIdxP, *regIdxP);
	return 1;
      }
      //compare the strings based on current wordIdx positions
    }
    //work out what wild card is being called and call that function
    
    
  }

  int compareStrings(char* letters, char* word, int *wordIdxP) {
    printf("starting compare word idx: %d\n", *wordIdxP);
    
    int size = getWordSize(letters);
    for (int i = 0; i < size; i++) {
      if (word[*wordIdxP + i] != letters[i]) {
	return 0;
      }
    }
    printf("ending compare word idx: %d\n", *wordIdxP);
    return 1;
  }

/*
  This method is used to check whether the regex expression is easy
 */
int simpleMatch(const char* regex, const char* word) {
  for(int i = 0; i < MAX_WORD_SIZE+1; i++) {
    if (regex[i] != word[i]) {
      return 0;
    }
  }
  return 1;
}
    
int isWild(char c) {
  if (c == '*' || c == '?' || c == '~') {
    return 1;
  }
  return 0;
} 

/*
I need to break up the regex expression into a series of regex commands

Ex: ab*cd?e~f = 

starts with a

any number of b's

next a c

0-1 d's

next an e.

up to <restriction> chars

next an f

This would match with abbbbcezzzzzzzf.

To accomplish this:
char* getLettersUntilWild(regex)

Have a method to get and save the string immeaditly following the wild card.
This updates regIdx as it goes.

If the wild card is a * or ?, the method chops off the last letter and RegIdx
is decreased by 1.

test whether the returned string matches word from wordIdx
update wordIdx as you go along

Then, perform the proper wild call the next letter in regIdx and the one after 
determining the type of call
 - this will updates wordIdx has letters are checked




