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

int isWild(char c) {
  return (c == '*' || c == '?');
}

int match(const char *regex, const char *word, int restriction) {
    // TODO: Implement me!
  printf("match start\n");
  
  
  int wordSize =  getWordSize(word);
  printf("The size of the word being assessed is %d\n", wordSize);

  int regSize = getRegexSize(regex);
  printf("The size of the regex being assessed is %d\n", regSize);
  if (regSize == 0 && wordSize == 0) {
    return 1;
  }
  else {
    return 0;
  }
  if (regSize == 1) { //if regex is size 1, bunch of base cases
    //    printf("reg size is 1\n");
    if (regex[0] == '~') { //if it's a tilde
      if (getWordSize(word) <= restriction) { //check word size and return accordingly
	return 1;
      }
      else {
	return 0;
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
    //  printf("reg size is 2+\n");
    if (isWild(regex[0]) == 0 && isWild(regex[1]) == 0 && regex[0] != '~') {
      //if neither the first nor second character of regex is a * or ?, and the first is not a ~ 
      if (regex[0] == word[0]) { //if the first character of regex and word match
	printf("The first characters of regex and word match, recurring\n");
	return match(regex+1, word+1, restriction); //recursion
      }
      else {
	printf("The first characters do not match, returning 0\n");
	return 0; //the first character of regex and word do not match, not a match
      }
    }
    else if (regex[1] == '*') { //STAR CASE
      printf("star case\n");
      if (word[0] == regex[0]) { //if word has the same letter as regex at the start
	printf("the first letter in word can be removed legally\n");
	int i = 0;
	//int worked = 0;
	while (word[i] == regex[0]) {
	  printf("the character at %d in word, %c, matches the tested character in regex, %c\n", i, word[i], regex[0]);
	  if ( match(regex+2, word+i, restriction) == 0) { //out of bounds issues potentially
	    printf("the removal of %d of that letter did not end in success, potentially trying to remove another\n", i);
	    i++;
	  }
	  else {
	    printf("a valid regex finale for star case was found after removing %d %c's\n", i, regex[0]);
	    // worked = 1;
	    // break;
	    return 1;
	  }
	}
	//	if (worked == 1) {
	// return match(regex,+2, word+i, restriction);
	//}
	return 0;
      }
      else { //word does not have that letter at the start
	printf("Recurring with regex ticked up past the star because 0 of that letter was present \n");
	return match(regex+2, word, restriction); //regex gets upticked past the *, recursive call
      }
    }
    else if (regex[1] == '?') { //QUESTION CASE
      printf("question case\n");
      if (word[0] == regex[0]) { //If the letter is present
	if (match(regex+2, word+1, restriction)) { //if the regex expression finds the word by accepting the present letter,
	    printf("there is a success if the letter before ?, %c, is accepted\n", regex[0]);
	    return 1;
	}
	else if (match(regex+2, word, restriction)){
     	  printf("accepting the letter before ?, %c, did not work. Trying continuing and keeping it around\n", regex[0]);
	  return 1; //try keeping the letter around and uptock regex
	}
	else {
	    return 0;
	}
      }
      else { //letter not present
	
	printf("letter not present, recurring with regex ticked up past ? (this can probably be moved to an if statement too)\n");
	return match(regex+2, word, restriction); //uptick regex past ?, recursive call
      }
    }
    else if (regex[0] == '~') { //TILDE CASE
      printf("Tilde case\n");
      /*   if (regSize == 1) { //if tilde is the last character in regex
	printf("Tilde is the last character\n");
	if (wordSize > restriction) { //if the remainder of word is too big, false
	  printf("returning false because the remainder of word is longer than restriction\n");
	  return 0;
	}
	printf("returning true because the remainder of word is shorter than the restriction\n");
	return 1; //if the remainder of word fits within restriction, true
      }
      else { //A letter OR A ~ comes after ~ in regex */ //This should be a base case already handeled
	for (int i = 0; i < restriction; i++) {
	  if (match(regex+1, word+i, restriction)) {
	      return 1;
	  }
	    //	}
        }
    }
    else {
      printf("UNKNOWN ERROR ABORT ABORT\n");
      return -1;
    }
  }
	printf("This should never be reached\n");
	return -2;
}

//TILDE TILDE CASE


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



