//********************************************************
//
// Assignment 6 - Structures
//
// Name: Alfio Raymond
//
// Class: C Programming, Fall 2023
//
// Date: 19 Oct 2023
//
// Description: Program which determines overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
// Call by reference design
//
//********************************************************

// Define and Includes

#include <stdio.h>

// Define Constants
#define SIZE 5
#define STD_HOURS 40.0
#define OT_RATE 1.5

// Define a global structure to pass employee data between functions
// Note that the structure type is global, but you don't want a variable
// of that type to be global. Best to declare a variable of that type
// in a function like main or another function and pass as needed.

struct employee
{
    long clockNumber;
    float wageRate;
    float hours;
    float overtimeHrs;
    float grossPay;
};

// define prototypes here for each function except main

void getHours (struct employee employeeData[], int theSize);
void printHeader (void);
void printEmp (struct employee employeeData[ ], int theSize);

// TODO: add your function prototypes here
void calcOT(struct employee employeeData[], int theSize);
void calcGross(struct employee employeeData[], int theSize);

void printTotals(struct employee employeeData[], int theSize);
void printAverages(struct employee employeeData[], int theSize);

int main ()
{
    // Set up a local variable and initialize the clock and wages of my employees
    struct employee employeeData [SIZE] = {
        { 98401, 10.60 },
        { 526488, 9.75 },
        { 765349, 10.50 },
        { 34645, 12.25 },
        { 127615, 8.35 }
    };

    // Call function needed to read hours
    getHours (employeeData, SIZE);

    // TODO: Call functions calculate ot hours and gross pay
    calcOT(employeeData, SIZE);
    calcGross(employeeData, SIZE);
   
    // Print a table header
    printHeader();

    // Function call to output results to the screen in table format
    printEmp (employeeData, SIZE);

    // Function call to output totals of all columns
    printTotals(employeeData, SIZE);

    // Function call to output averages of all columns
    printAverages(employeeData, SIZE);
  
  return(0); // success

} // main

//**************************************************************
// Function: getHours 
// 
// Purpose: Obtains input from user, the number of hours worked 
// per employee and stores the result in an array of structures
// that is passed back to the calling function by reference. 
// 
// Parameters:
// 
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to process
//
// Returns: Nothing (void)
//  
//**************************************************************

void getHours (struct employee employeeData[], int theSize ) 
{

    int i; // loop and array index

    // read hours in for each employee
    for (i = 0; i < theSize ; ++i)
    {
        printf("\nEnter hours worked by emp # %06li: ",
                employeeData[i].clockNumber);
        scanf ("%f", &employeeData[i].hours);
    } // for

} // getHours

//**************************************************************
// Function: printHeader
// 
// Purpose: Prints the initial table header information.
// 
// Parameters: none
// 
// Returns: void
//  
//**************************************************************

void printHeader (void) 
{ 

    printf ("\n\n*** Pay Calculator ***\n");

    // print the table header
    printf("\nClock#      Wage    Hours    OT      Gross\n");
    printf("------------------------------------------------\n");

} // printHeader

// ********************************************************************
// Function: printEmp
//
// Purpose: Outputs to screen in a table format the following
// information about an employee: Clock, Wage,
// Hours, Overtime Hours, and Gross Pay.
//
// Parameters:
//
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to process
//
// Returns: Nothing (void)
//
// *********************************************************************

void printEmp ( struct employee employeeData[], int theSize )
{
    int i; // loop and array index

    // print information about each employee
    for (i = 0; i < theSize ; ++i)
    {
        printf("\n %06li %9.2f %8.1f %7.2f %8.2f",
        employeeData[i].clockNumber, employeeData[i].wageRate, employeeData[i].hours,
        employeeData[i].overtimeHrs, employeeData[i].grossPay);
    } /* for */

} // printEmp

//*************************************************************
// Function: calcOT
//
// Purpose: Calculate overtime hours
//
// Parameters:
//
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to proces 
//
//
// Returns: void
//
//**************************************************************
// TODO: add your functions here
void calcOT(struct employee employeeData[], int theSize)
{
    int i;

  // Calculate Overtime Hours
  for (i = 0; i < theSize ; ++i)
    {
      if (employeeData[i].hours > STD_HOURS)
      {
        employeeData[i].overtimeHrs = employeeData[i].hours - STD_HOURS;
      }
      else
      {
        employeeData[i].overtimeHrs = 0;
      }
    }
}

//*************************************************************
// Function: calcGross
//
// Purpose: Calculate Gross Pay
//
// Parameters:
//
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to proces
//
//     normalPay - normal amount which is 40hrs times wageRate
//     overtimePay - Any hours over 40; so wageRate times 1.5 times overtime hours
//     grossPayReturn - return value of normal pay and overtime pay added together.
//     i - index for looping through structure
//
// Returns: void
//
//**************************************************************
void calcGross(struct employee employeeData[], int theSize)
{
  float normalPay = 0.0;
  float overtimePay = 0.0;
  float grossPayReturn = 0.0;
  int i;
  
  for (i = 0; i < theSize ; ++i)
  {
    if (employeeData[i].overtimeHrs > 0)
    {
      normalPay = STD_HOURS * employeeData[i].wageRate;
      overtimePay = employeeData[i].overtimeHrs * (employeeData[i].wageRate * 1.5);
      employeeData[i].grossPay = normalPay + overtimePay;
    }
    else
    {
      employeeData[i].grossPay = employeeData[i].wageRate * employeeData[i].hours;
    }
  }
  
}

//*************************************************************
// Function: printTotals
//
// Purpose: Prints out the averages of the columns
//
// Parameters:
//
//     wageTotal - total of all wages
//     hoursTotal - total of all hours
//     overtimeHrsTotal - overtime hours totalled
//     grossPayTotal - gross pay total
//
//
// Returns: void
//
//**************************************************************
void printTotals(struct employee employeeData[], int theSize)
{
  int i;
  float wageTotal =0.0;
  float hoursTotal = 0.0;
  float overtimeHrsTotal = 0.0;
  float grossPayTotal = 0.0;

  for (i = 0; i < theSize ; ++i)
    {
      wageTotal += employeeData[i].wageRate;
      hoursTotal += employeeData[i].hours;
      overtimeHrsTotal += employeeData[i].overtimeHrs;
      grossPayTotal += employeeData[i].grossPay;
    }

  // print the totals
  printf("\n-------------------------------------------------\n");

  printf("Totals: %9.2f %8.1f %7.2f %8.2f\n", wageTotal, hoursTotal,
         overtimeHrsTotal, grossPayTotal);
};

//*************************************************************
// Function: printAverages
//
// Purpose: Prints out the averages of the columns
//
// Parameters:
//
//     wageAverage - Average of all wages
//     hoursAverage - Average of all hours
//     overtimeHrsAverage - Average of overtime hours 
//     grossPayAverage - Average of all gross pay 
//
// Returns: void
//
//**************************************************************
void printAverages(struct employee employeeData[], int theSize)
{
  int i;
  float wageAverage =0.0;
  float hoursAverage = 0.0;
  float overtimeHrsAverage = 0.0;
  float grossPayAverage = 0.0;

  for (i = 0; i < theSize ; ++i)
    {
      wageAverage += employeeData[i].wageRate;
      hoursAverage += employeeData[i].hours;
      overtimeHrsAverage += employeeData[i].overtimeHrs;
      grossPayAverage += employeeData[i].grossPay;
    }

    wageAverage /= theSize;
    hoursAverage /= theSize;
    overtimeHrsAverage /= theSize;
    grossPayAverage /= theSize;
  
  // print the averages
  printf("Averages: %7.2f %8.1f %7.2f %8.2f\n", wageAverage, hoursAverage,
     overtimeHrsAverage, grossPayAverage);
};
