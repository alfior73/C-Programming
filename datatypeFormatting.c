#include <stdio.h>

int main(void) {
	// your code goes here
	int ivalue =7;
	float fvalue = 10.23;
	
	printf("%i \n", ivalue);
	printf("%3i \n", ivalue);
	printf("%03i \n", ivalue);
	printf("%f \n", fvalue);
	printf("%7.2f \n", fvalue);
	printf("%-7.2f \n", fvalue);
	
	return 0;
}
