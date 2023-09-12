//******************************************************* 
// 
// Homework: 1 (Chapter 4/5) 
// 
// Name: Alfio Raymond
// 
// Class: C Programming, Fall 2023
// 
// Date: 12 Sept 2023 
// 
// Description: Program which determines gross pay and outputs 
// to the screen.  
//
// Non file pointer solution 
// 
//******************************************************** 
 
#include <stdio.h>  
int main () 
{ 
 
    int clockNumber; // employee clock number 
    float gross;     // gross pay for week (wage * hours) 
    float hours;     // number of hours worked per week 
    float wageRate;  // hourly wage 
 
    printf ("\n\t*** Pay Calculator ***\n");
 
    // Prompt for input values from the screen 
    printf ("\n\tEnter clock number for employee: "); 
    scanf ("%d", &clockNumber); 
    printf ("\n\tEnter hourly wage for employee: "); 
    scanf ("%f", &wageRate); 
    printf ("\n\tEnter the number of hours the employee worked: "); 
    scanf ("%f", &hours); 
 
    // calculate gross pay
    gross = wageRate * hours; 
 
    // print out employee information
    /* 
    	Added a bit more space for cosmetic look and feel
		so data can be read a little clearer - ARaymond
	*/
    printf ("\n\n\t----------------------------------------------------------\n"); 
    printf ("\tClock #    Wage     Hours     Gross\n"); 
    printf ("\t----------------------------------------------------------\n"); 
 
	// Added a bit more space between columns for readability
    printf ("\t%06i %9.2f %7.1f %10.2f\n", clockNumber, wageRate, hours, gross); 
 
    return (0); // success
 
} // main
