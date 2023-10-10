#include <stdio.h>

/* Function prototypes */
long int calculate_power (int number, int power);

/******************************************************/
/* Function: calculate_power                          */
/*                                                    */
/* Overview: Raises an integer to a positive integer  */
/*           power.                                   */
/*                                                    */
/* Parameters:  number - a integer                    */
/*              power  - a positive power to raise    */
/*                                                    */
/* Written by:  Timothy Niesen                        */
/*                                                    */
/* Date Written: 10/22/91                             */
/******************************************************/

long int calculate_power (int number, int power)
{
    long int result = 1; /* final result */
  
    /* anything to the zero power is 1 */
    if (power == 0)
        return(result);

    else
    {
        /* Recursive call: a function calling itself */
        result =  number * calculate_power(number, power - 1);
    } /* else */

    return (result); /* to calling function */

} /* calculate_power */

int main (void)
{

    /* Call this function with 4 different arguments */
   
    printf("Passed with 5,0 is %li\n", calculate_power(5,0));
    printf("Passed with 5,1 is %li\n", calculate_power(5,1));
    printf("Passed with 5,2 is %li\n", calculate_power(5,2));
    printf("Passed with 5,3 is %li\n", calculate_power(5,3));

    return(0);

} /* main */
