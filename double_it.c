#include <stdio.h>

// ***********************************************
// Function: double_it
//
// Descriptions: Double the value of any given
//               integer value
//
// Parameters:  number - integer value to double
//
// Returns:     result - the number doubled
// ************************************************
int double_it (int number)
{
  int result; /* holds value of number doubled */

  result = number + number; /* double it */

  return (result);

} /* double it */

// ***********************************************
// Function: double_array
//
// Descriptions: Given an array, doubles the value
//               in each array element
//
// Parameters:  somearray - array of integer
//              size      - size of the array
//
// Returns:     void
// ************************************************
void double_array (int somearray[], int size)
{
    int i; /* index */

    for (i=0; i < size; ++i)
    {  

        /* contents changed in calling function */
        somearray [i] *= 2;          

    }

    /* no return needed */

} /* double_array */

int main ()
{
  int i;                          /* index */
  int myArray [3] = {10, 20, 30}; /* local Array */

  /* pass one element of array by value           */
  /* this is really just passing an integer value */
  /* The contents of MyArray[2] are unchanged     */

  printf ("%i doubled is %i \n", myArray[2], double_it (myArray[2]) );
  printf("After call to double_it \n\n");
  printf("myArray[2] = %i \n", myArray[2] );

  /* Simply pass double_it any integer value */ 
  printf("\n\n 5 doubled is %i \n\n", double_it (5) );
 
  /* If you pass an array name, you are passing the */ 
  /* the array address:  &myArray[0]                */

  /* Each array element in MyArray will get doubled */
  double_array(myArray, 3); 

  printf ("After call to double_array: \n\n");
  
 /* Verify each array element has been doubled */
 for (i=0; i < 3; ++i)  
 {      
     printf("myArray[%i] = %i \n", i, myArray[i] );  
 }  

 return(0);

} /* main */
