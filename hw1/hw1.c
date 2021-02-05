//Francis Durso
//FDurso1

#include  <stdio.h>

int main(void) {
  printf("Please enter the weather trend using + and - only:\n");
  float temp = 0;
  char tempType = 'f';
  float totalTemp = 0;
  int totalInput = 0;
  printf("The start char is %c\n", tempType);
  while ((totalInput = scanf(" %f %c", &temp, &tempType)) == 2) {
    printf("the char / tempType is %c\n", tempType);

    switch (tempType) {
      case 'c':
	printf("c detected");
        temp = (temp*1.8) + 32;
        totalTemp += temp;
        break;
        //I wanted to not include the totalTemp += temp line and just let it fall through
        //But that produced a warning so I put it back
      case 'f':
        totalTemp += temp;
        break;
      default:
        printf("invalid unit\n");
	return 1;
        break;
    }
  }
  
  printf("%.2f F\n", totalTemp);
  return 0;
}
