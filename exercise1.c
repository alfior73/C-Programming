/* Sample Exercise 1

   Write a program to generate and display a table of
   n and n squared, for integer values ranging from 1
   to 10.  Be sure to print appropriate headings

   Hint:  Good use of a loop ... C has no operator for square ... so use num * num in the code

*/

#include <stdio.h>

int main(void) {

  int n, triangularNumber;

  printf("TABLE OF SQUARED NUMBERS\n\n");
  printf(" n     Sum from 1 to n\n");
  printf("----   ---------------\n");

  triangularNumber = 0;

  for ( n = 1; n <= 10; n = n + 1) {
    triangularNumber = n * n;
    printf("%2i      %i\n", n, triangularNumber);
  }
    

  return 0;
}
