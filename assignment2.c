//******************************************************* 
// 
// Homework: 2
// 
// Name: Alfio Raymond
// 
// Class: C Programming, Fall 2023
// 
// Date: 18 Sept 2023
// 
// Description: Program which determines gross pay
// and outputs are sent to standard output (the screen).
// 
// 
//******************************************************** 

#include <stdio.h>  
int main ( ) 
{ 

    int clockNumber;    // employee clock number
    float grossPay;     // gross pay for week (wage * hours)
    float hours;        // number of hours worked per week
    float wageRate;     // hourly wage

    // TODO - Add two variables, one for a loop index, another for a loop test
    int i, loop_count;

    printf ("             ***Pay Calculator*** \n\n");
  
    // TODO - Add your prompt to capture how many employees to process
    printf ("Enter the number of employees to process: ");
    scanf ("%i", &loop_count);
    // TODO - Add a loop of your choice here (for, while, or do) to process each employee

    for(i=0; i < loop_count; ++i){
      
      // Prompt for input values from the screen
      printf ("\nEnter clock number for employee: "); 
      scanf ("%d", &clockNumber); 
      printf ("Enter hourly wage for employee: "); 
      scanf ("%f", &wageRate); 
      printf ("Enter the number of hours the employee worked: "); 
      scanf ("%f", &hours); 
  
      // calculate gross pay
      grossPay = wageRate * hours; 
  
      // print out employee information
      printf ("\n\n\t----------------------------------------------------------\n"); 
      printf ("\tClock #     Wage     Hours     Gross\n"); 
      printf ("\t----------------------------------------------------------\n"); 
  
      // print the data for the current employee
      printf ("\t%06i %9.2f %7.1f %10.2f\n",clockNumber, wageRate, hours, grossPay);
  
      // TODO - end your loop here
    }

    // Closing message
    printf ("\n Thank you for using UMass Payment System\n\n");
  
    return (0); // success

} // main
