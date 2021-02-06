//Francis Durso
//FDurso1

#include  <stdio.h>

int main(void) {
  printf("Please enter the weather trend using + and - only:\n");
  float temp = 0;
  char tempType = 'f';
  float totalTemp = 0;
  int totalInput = 2;
  char mathsym = '+';
  // printf("The start char is %c\n", tempType);
  while ((totalInput = scanf(" %f %c", &temp, &tempType)) == 2) {
    // printf("the char / tempType is %c\n", tempType);
    printf("input currently valid (%d), continuing\n", totalInput);
    switch (tempType) {
      case 'c':
	//	printf("c detected\n");
        temp = (temp*1.8) + 32;
	//printf("adjusted temp is now: %f\n", temp);
        break;
        //I wanted to not include the totalTemp += temp line and just let it fall through
        //But that produced a warning so I put it back
      case 'f':
        break;
      default:
        printf("invalid unit\n");
	return 2;
        break;
    }
    if (mathsym == '-' && temp > 0) {
      temp = -1 * temp;
    }
    else if (mathsym != '+' && mathsym != 0) {
      printf("malformed expression 1\n");
      return 1;
    }
    totalTemp += temp;
    scanf(" %c", &mathsym);
    printf("The math symbol is: %c\n", mathsym);
    printf("Now at the end of the while loop, the totalinput is %d\n", totalInput);
  }
  if (totalInput != 2 && totalInput != -1) {
    printf("malformed expression 2\n");
    printf("total input calculated to be %d\n", totalInput);
    // return 1;
  }
  printf("%.2f F\n", totalTemp);
  return 0;
}
