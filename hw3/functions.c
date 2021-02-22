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

int isWild(char c);
int tildeRec(const char *word, char c, int i);

int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf("match start\n");
  
  
  int wordSize =  getWordSize(word);
  printf("The size of the word being assessed is %d\n", wordSize);

  int regSize = getRegexSize(regex);
  printf("The size of the regex being assessed is %d\n", regSize);

  if (regSize == 1) { //if regex is size 1
    printf("reg size is 1\n");
    if (regex[0] == '~') { //if it's a tilde
      if (getWordSize(word) <= restriction) { //check word size and return accordingly
	return 0;
      }
      else {
	return 1;
      }
    }
    else if (getWordSize(word) > 1) { //if it's a letter, and word is longer than 1 letter, return false
      return 0;
    }
    else if (getWordSize(word) == 1) {
      return regex[0] == word[0]; //return if they're the same character
    }
    else {
      printf("ERROR! ERROR! ABORT! ABORT!\n");
      return -1;
    }
  }
  else { //regex is at least size 2
    printf("reg size is 2+\n");
    if (isWild(regex[0]) == 0 && regex[0] !='~' && isWild(regex[1]) == 0) { //if neither the first nor second character of regex is a * or ?, and the first is not a ~ 
      if (regex[0] == word[0]) { //if the first character of regex and word match
	printf("The first characters of regex and word match, recurring\n");
	return match(regex++, word++, restriction); //recursion
      }
      else {
	printf("The first characters do not match, returning 0\n");
	return 0; //the first character of regex and word do not match, not a match
      }
    }
    else if (regex[1] == '*') { //STAR CASE
      printf("star case\n");
      if (word[0] == regex[0]) { //if word has the same letter as regex at the start
	printf("recurring with the first letter of word removed\n");
	return match(regex, word++, restriction); //uptick word and call again
      }
      else { //word does not have that letter at the start
	printf("Recurring with regex ticked up past the star\n");
	return match(regex+2, word, restriction); //regex gets upticked past the *, recursive call
      }
    }
    else if (regex[1] == '?') { //QUESTION CASE
      printf("question case\n");
      if (word[0] == regex[0]) { //If the letter is present
	printf("letter present, recurring with regex ticked up past ? and word ticked up once\n");
	return match(regex+2, word++, restriction); //uptick word, uptick regex past ?, recursive call
      }
      else { //letter not present
	printf("letter not present, recurring with regex ticked up past ?\n");
	return match(regex+2, word, restriction); //uptick regex past ?, recursive call
      }
    }
    else if (regex[0] == '~') { //TILDE CASE
      printf("Tilde case\n");
      if (regSize == 1) { //if tilde is the last character in regex
	printf("Tilde is the last character\n");
	if (wordSize > restriction) { //if the remainder of word is too big, false
	  printf("returning false because the remainder of word is longer than restriction\n");
	  return 0;
	}
	printf("returning true because the remainder of word is shorter than the restriction\n");
	return 1; //if the remainder of word fits within restriction, true
      }
      else { //A letter comes after ~ in regex
	printf("a letter comes after the tilde\n");
	char aft = regex[1];
	int lower = restriction;
	if (wordSize < restriction) {
	  lower = wordSize;
	}
	printf("working from lower = %d characters into word backwards\n", lower);
	int hold = tildeRec(word, aft, lower);
	if (hold == -1) {
	  printf("The letter after the tilde never came\n");
	  return 0;
	}
	else {
	  printf("returning ticking up regex past the ~ and word ticked up hold=%d\n", hold);
	  return match(regex++, word+hold, restriction); 
	}
      }
    }
    else {
      printf("UNKNOWN ERROR ABORT ABORT\n");
      return -1;
    }
  }
}

int tildeRec(const char* word, char* smolWord,  char aft, int i) {
  printf("tildeRec start\n");
  
  while (word[i] != aft) {
    if (i < 0) {
      printf("base case reached, tilde failed\n");
      return -1;
    }
    else {
      int wordSize = getWordSize(word);
      char* smolWord[wordSize];
      for (int j = 0; j < i; j++) {
	smolWord[j] = word[j];
	smolWord[j+1] = '\0';
      }
      printf("recurring tilderec with a shorter word (removed from the end backwards)\n");
      return tildeRec(word, smolWord, aft, i-1);
    }
  }
  printf("tildeRec found the latest matching character withing the restriction bounds at i=%d\n", i);
  return i;
}

int isWild(char c) {
  if (c == '*' || c == '?') {
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
char* getLettersUntilWild(parameters)

Have a method to get and save the string immeaditly preceeding  the wild card.
This updates regIdx as it goes.

If the wild card is a * or ?, the method chops off the last letter and RegIdx
is decreased by 1.

test whether the returned string matches word from wordIdx
update wordIdx as you go along

Then, perform the proper wild call the next letter in regIdx and the one after 
determining the type of call
 - this will updates wordIdx has letters are checked

This has since been modified to make use of recursion
*/



