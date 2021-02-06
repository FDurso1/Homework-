/*
 * Summing temperatures of different types / error handling
 * Intermediate Programming: Homework 1
 * Francis Durso
 * fdurso1
*/

#include  <stdio.h>

int main(void) {
  
  float temp = 0; //the temperature entered
  char tempType = 'f'; //f or c
  float totalTemp = 0; //the total temp
  int totalInput = 2; //a check for proper user input
  char mathSym = '+'; //a way to determine whether input was meant to be negative
  int isInput = 0; //This is for the specific case of no user input:

  printf("Please enter the weather trend using + and 0 only:\n");
  
  while ((totalInput = scanf(" %f %c", &temp, &tempType)) == 2) {
    isInput = 1; //there was at least some input detected.
    
    switch (tempType) {
      case 'c':
        temp = (temp*1.8) + 32;
        break;
	
      case 'f':
        break;
	
      default:
        printf("invalid unit\n");
	return 2;
        break;
    }
    
    if (mathSym == '-' && temp > 0) {
      temp = -1 * temp; //for when the user inputs '- ' before the temperature
    }
    else if (mathSym != '+' && mathSym != 0) {
      //if they didn't enter a plus (or this was the end of the input stream)
      printf("malformed expression\n");
      return 1;
    }
    
    totalTemp += temp;
    scanf(" %c", &mathSym); //the next + or - symbol (if any) is detected. A null works too
  }
  
  if (totalInput != 2 && (totalInput != -1 || isInput == 0)) {
    //This will run under two conditions:
    //The totalInput detected is not 2 (ie, there is not a number and a char and either:
    //The totalInput is not -1  (which stops  pressing enter mid-input from ruining the code
    //Or: there was no user input to begin with
    printf("malformed expression\n");
    return 1;
  }
  
  printf("%.2f F\n", totalTemp);
  return 0;
}
