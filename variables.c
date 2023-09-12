#include <stdio.h>

int main(void) {
	// your code goes here
	int var1 = 42;
	int var2 = 014;
	int var3 = 0x4A6;
	char var4 = '8';
	char var5 = 'a';
	char var6 = '#';
	char var7 = 'A';
	float var8 = 5.2;
	float var9 = 2.0;
	float varA = 2;
	float varB = 0.07;
	float varC = 7.0e-2;
	double varD = 5.2;
	double varE = 12.33434343;
	double varF = 5.667744544e3;
	
	printf("Integers: %i %i %i \n", var1, var2,var3);
	printf("Characters: %c %c %c %c \n", var4, var5, var6, var7);
	printf("Floats: %f %f %f %f %f \n", var8, var9, varA, varB, varC);
	printf("Doubles: %g %g %g \n", varD, varE, varF);
	printf("Hello World \n");
	
	return 0;
}
