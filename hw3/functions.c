#include "functions.h"

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 128

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
 
  char curr[MAX_WORD_SIZE+1]= "";
  fgets(curr, MAX_WORD_SIZE+1, fp);
  //get rid of first line (which originally contained the number of lines)
  
  
  for (int i = 0; i < size; i++) {
    fgets(curr, MAX_WORD_SIZE+1, fp);

    for (int j = 0; j < MAX_WORD_SIZE && curr[j] != '\0'; j++) {
      words[i][j] = curr[j];
    }
  }
  return 0;
}

int isWild(char c) {
  return (c == '*' || c == '?');
}

int match(const char *regex, const char *word, int restriction) {
  
  int wordSize = strlen(word);
  int regSize = strlen(regex);

  if (regSize == 0 && wordSize == 0) { //Base Case: Both Regex and Word are empty (return true)
    return 1;
  }
  else if (regSize == 0 && wordSize != 0){ //Base Case: Regex is empty but Word is not (return false)
    return 0;
  }
  if (regSize == 1) { //if Regex is just one character
    if (regex[0] == '~') { //if that character's a ~
      if (wordSize <= restriction) { //check word size and return accordingly
	return 1;
      }
      else {
	return 0;
      }
    }
    else if (wordSize != 1) { //if that character's a letter, and word is 2+, return false
      return 0;
    }
    else if (wordSize == 1) { //if it's a letter and word is just one letter
      return regex[0] == word[0]; //return if they're the same character
    }
    else { //This should never happen
      return 0;
    }
  }
  else { //Regex is more than one character

    if (isWild(regex[0]) == 0 && isWild(regex[1]) == 0 && regex[0] != '~') {
      //if neither the first nor second character of regex is a * or ?, and the first is not a ~ 

      if (regex[0] == word[0]) { //if the first character of regex and word match
	return match(regex+1, word+1, restriction);
      }
      else {
	return 0; //the first character of regex and word do not match, return false
      }
    }
    else if (regex[1] == '*') { //STAR CASE
      
      if (word[0] == regex[0]) { //if word has the same letter as regex at the start

	if (match(regex+2, word, restriction) == 1) { //test the case where nothing is removed
	  return 1;
	}
	
	int idx = 1;
	while (idx <= wordSize && word[idx-1] == regex[0]) {
	  
	  if ( match(regex+2, word+idx, restriction) == 0) {
	    //if removing {idx} of the letter that starts word did not work, try removing idx+1 next
	    idx++;
	  }
	  else { //a successful number of letters can be removed
	    return 1;
	  }
	} //no matter how many letters were removed, no matching path was found.
	return 0;
      }
      else { //word does not begin with the letter before the *, return match() with an updated regex
	return match(regex+2, word, restriction); //regex gets upticked past the *, recursive call
      }
    }
    else if (regex[1] == '?') { //QUESTION CASE
      
      if (word[0] == regex[0]) { //If the letter is present
	if (match(regex+2, word+1, restriction)) { //try removing the letter and recurring
	  return 1;
	}
	else if (match(regex+2, word, restriction)){//try not removing the letter and recurring if removing it failed
	  return 1;
	}
	else {
	  return 0; //neither removing nor keeping the letter made a match, return false
	}
      }
      else if (match(regex+2, word, restriction)){ //the first letter in word is not the letter before the ?
	return 1; 
      }
      return 0;
    }
    else if (regex[0] == '~') { //TILDE CASE
      for (int i = 0; i < restriction && i <= wordSize; i++) {
	if (match(regex+1, word+i, restriction)) {
	  return 1;
	}
      }
      return 0; //no successful interpretation of the ~ was found to match the word
    }
    else {  //this should never be reached
      return 0;
    }
  }
  //This should never be reached
  return 0;
}
