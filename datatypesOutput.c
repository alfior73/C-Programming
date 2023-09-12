#include <stdio.h>

int main(void) {
	// your code goes here
	int var1, var2 = 027;
	int var3 = 0xD;
	int var4;
	
	var4 = var2 + 5;
	var1 = 30;
  
	// The format characters are d for decimal, letter o for octal and x for hexadecimal.
	printf("%d %x %o\n", var1, var2, var3,var4);
	
	return 0;
}
