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
  
  printf("Please enter the weather trend using + and 0 only:\n");
  
  while ((totalInput = scanf(" %f %c", &temp, &tempType)) == 2) {
    isInput = 1; //there was at least some input detected.
    
    // printf("1.The current temp being calculated / added is: %f\n", temp);
    
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
    
    // printf("2.The middle temp being calculated is: %f\n", temp);
    
    if (mathSym == '-' && temp > 0) {
      temp = -1 * temp; //for when the user inputs '- ' before the temperature
    }
    else if (mathSym != '+' && mathSym != 0) {
      //if they didn't enter a plus (or this was the end of the input stream)
      printf("malformed expression\n");
      return 1;
    }

    // printf("3.The final temp that is about to be added is: %f\n", temp);
    
    totalTemp += temp;
    endingSym =  scanf(" %c", &mathSym);
   //the next + or - symbol (if any) is detected. A null provides -1, the end of the input
   // printf("The value of the mathSym is %d\n", mathSym);
   // printf("The existence of the mathsym is %d\n", endingSym);
    
  }
  
  if (totalInput != 2) {
    if (totalInput != -1) {
      printf("malformed1 - there was not two expected values\n");
      return 1;
    }
    else if (isInput == 0) {
      printf("malformed2 - there was no user input");
      return 1;
    }
    else if (endingSym != -1) {
      printf("The user ended with a math symbol");
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
