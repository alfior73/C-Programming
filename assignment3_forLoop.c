//******************************************************* 
// 
// Homework: 3
// 
// Name: Alfio Raymond
// 
// Class: C Programming, Fall 2023
// 
// Date: 26 Sept 2023
// 
// Description: Program which determines gross pay
// and outputs are sent to standard output (the screen).
// 
// 
//******************************************************** 

#include <stdio.h>  
#define NUM_EMPLOYEES 5
#define STD_HOURS 40.0

int main ( ) 
{ 

    int clockNumber;    // employee clock number
    float grossPay;     // gross pay for week (wage * hours)
    float hours;        // number of hours worked per week
    float wageRate;     // hourly wage
    float normalPay;     // Standard weekly normal pay without overtime 
    float overtimeHrs;   // Overtime hours worked beyond a normal week (40 hours)
    float overtimePay;   // Any hours worked past the normal scheduled work week
  
    // TODO - Add two variables, one for a loop index, another for a loop test
    int i=0;

    printf ("             ***Pay Calculator*** \n\n");

    // TODO - Add a loop of your choice here (for, while, or do) to process each employee

    for(int i = 0; i < NUM_EMPLOYEES; i++) {

      // Prompt for input values from the screen
      printf ("\nEnter clock number for employee: "); 
      scanf ("%d", &clockNumber); 
      
      printf ("Enter hourly wage for employee: "); 
      scanf ("%f", &wageRate); 
      
      printf ("Enter the number of hours the employee worked: "); 
      scanf ("%f", &hours); 

      if (hours > STD_HOURS) {
        /* TODO: calculate the three values with overtime */
        overtimeHrs = hours - STD_HOURS;
        normalPay = STD_HOURS * wageRate;
        overtimePay = overtimeHrs * (1.5 * wageRate);
      }
      else {
        overtimeHrs = 0;
        overtimePay = 0.00;
        normalPay = hours * wageRate;
        
      }
      // calculate gross pay
      grossPay = normalPay + overtimePay;
  
      // print out employee information
      printf ("\n\n\t----------------------------------------------------------\n"); 
      printf ("\tClock #     Wage    Hours    OT     Gross\n"); 
      printf ("\t----------------------------------------------------------\n"); 
  
      // print the data for the current employee
      printf ("\t%06i %9.2f %8.1f %7.2f %8.2f\n",clockNumber, wageRate, hours, overtimeHrs, grossPay);
  
      // TODO - end your loop here
      
    }

    // Closing message
    printf ("\n Thank you for using UMass Payment System\n\n");
  
    return (0); // success

} // main
