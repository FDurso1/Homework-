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
  int endingSym = 0; //This is for detecting whether the user ends on a math symbol
  
  printf("Please enter the weather trend using + and - only:\n");
  
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
    else if (mathSym != '+') {
      //if they didn't enter a plus (malformed expression)
      printf("malformed expression\n");
      return 1;
    }
    
    totalTemp += temp;
    endingSym =  scanf(" %c", &mathSym);
   //the next + or - symbol (if any) is detected. A null provides -1, the end of the input
    
  }
  
  if (totalInput != 2) {
    if (totalInput != -1 || isInput == 0 || endingSym != -1) {
      printf("malformed expression\n");
      return 1;
    }
  }
    //This will run under three conditions:
    //The totalInput detected is not 2 (ie, there is not a number and a char AND either:
    //The totalInput is not -1  (which stops pressing enter mid-input from ruining the code
    //Or: there was no user input to begin with
    //Or, the user ended with a math symbol (+ or -)
  
  printf("%.2f F\n", totalTemp);
  return 0;
}
