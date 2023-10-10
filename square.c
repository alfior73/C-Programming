#include <stdio.h>

// *********************************************************
// Function: square
//
// Description: Takes a floating point number and returns
//              its square
//
// Parameters: number - a floating point number to square
//
// Returns:    square_value - the square of the number
//
// **********************************************************
float square (float number)
{
    float square_value; /* number squared */

    /* square the number and store it in square_value */
    square_value = number * number;

    return (square_value); /* return to calling function */
}

int main ()
{

    float value1; /* the number to be squared */

    float answer; /* holds the square value */ 

    /* Prompt the user for a number to be squared */
    printf ("\n Enter a number: ");
    scanf ("%f", &value1);

    /* Pass value1 to the square function, process it and return the */
    /* the squared value into the answer local variable */
    answer = square ( value1 );

    printf ("\n The square of %5.2f is %8.2f \n", value1, answer);

    return (0);
}

