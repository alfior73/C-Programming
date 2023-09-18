/* Sample Exercise 3

   Given the a factorial is the product of consecutive
   integers 1 through n, write a program to calculate the
   first 10 factorial values

   2 factorial = 1 * 2

   3 factorial = 1 * 2 * 3

   4 factorial = 1 * 2 * 3 * 4

   Hint:  Perfect place to use any loop ...

*/

#include <stdio.h>

int main(void) {

  int n;

  printf("TABLE OF FACTORIAl NUMBERS\n\n");
  printf(" n!     Factorial \n");
  printf("----   ---------------\n");

  int factorialNumber = 1; /* current factorial value */
  
  for(n = 1; n <= 5; ++n) {
    factorialNumber *= n;  /* first factorial */
    printf ("%i! = %i \n", n, factorialNumber);
  }

    return (0); 
}

