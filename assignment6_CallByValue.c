//********************************************************
//
// Assignment 6 - Structures
//
// Name: Alfio Raymond
//
// Class: C Programming, Fall 2023
//
// Date: 18 Oct 2023
//
// Description: Program which determines overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
// Call by Value design
//
//********************************************************

#include <stdio.h>

// constants
#define SIZE 5
#define OVERTIME_RATE 1.5
#define STD_WORK_WEEK 40.0

struct employee
{
  long int clockNumber;
  float wageRate;
  float hours;
  float overtimeHrs;
  float grossPay;
};

// function prototypes
float getHours(long int clockNumber);
void printHeader(void);
void printEmp(long int clockNumber, float wageRate, float hours,
              float overtimeHrs, float grossPay);

// TODO:  Add other function prototypes here as needed
float calcOT(float hours);
float calcGross(float hours, float wageRate, float overtimeHrs);
void printTotals(float wageTotal, float hoursTotal, float overtimeTotal, float grossPayTotal);
void printAverages(float wageTotal, float hoursTotal, float overtimeTotal, float grossPayTotal);

int main() {

  /* Variable Declarations */
  // Set up a local variable to store the employee information
    struct employee employeeData[SIZE] = {
        { 98401, 10.60 },
        { 526488, 9.75 },
        { 765349, 10.50 }, // initialize clock and wage values
        { 34645, 12.25 },
        { 127615, 8.35 }
    };

  int i;  // loop and array index
  
  float wageTotal=0;        // wage total of all employees
  float hoursTotal=0;       // hours total of all employees
  float overtimeTotal=0;    // overtime total of all employees
  float grossPayTotal=0;    // gross total of all employees

  // process each employee
  for (i = 0; i < SIZE; ++i) {

    // Prompt for the number of hours worked by the employee
      employeeData[i].hours = getHours (employeeData[i].clockNumber); 

    // TODO: Add other function calls as needed to calculate overtime and gross
      employeeData[i].overtimeHrs = calcOT(employeeData[i].hours);
      
      employeeData[i].grossPay = calcGross(employeeData[i].hours, employeeData[i].wageRate, employeeData[i].overtimeHrs);

    // Calculate totals
    wageTotal += employeeData[i].wageRate;
    hoursTotal += employeeData[i].hours;
    overtimeTotal += employeeData[i].overtimeHrs;
    grossPayTotal += employeeData[i].grossPay;
  }

  // print the header info
  printHeader();

  // print out each employee
  for (i = 0; i < SIZE; ++i) {

    // Print all the employees - call by value
    printEmp(employeeData[i].clockNumber, 
             employeeData[i].wageRate,
             employeeData[i].hours,
             employeeData[i].overtimeHrs,
             employeeData[i].grossPay);

  } // for

  printTotals(wageTotal, hoursTotal, overtimeTotal, grossPayTotal);
  printAverages(wageTotal, hoursTotal, overtimeTotal, grossPayTotal);
  
  return (0);

} // main

//**************************************************************
// Function: getHours
//
// Purpose: Obtains input from user, the number of hours worked
// per employee and stores the result in a local variable
// that is passed back to the calling function.
//
// Parameters: clockNumber - The unique employee ID
//
// Returns: hoursWorked - hours worked in a given week
//
//**************************************************************

float getHours(long int clockNumber) {

  float hoursWorked; // hours worked in a given week

  // Read in hours for employee
  printf("\nEnter hours worked by emp # %06li: ", clockNumber);
  scanf("%f", &hoursWorked);

  // return hours back to the calling function
  return (hoursWorked);

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

void printHeader(void) {

  printf("\n\n*** Pay Calculator ***\n");

  // print the table header
  printf("\nClock#      Wage    Hours    OT      Gross\n");
  printf("------------------------------------------------\n");

} // printHeader

//*************************************************************
// Function: printEmp
//
// Purpose: Prints out all the information for an employee
// in a nice and orderly table format.
//
// Parameters:
//
//     clockNumber - unique employee ID
//     wageRate - hourly wage rate
//     hours - Hours worked for the week
//     overtimeHrs - overtime hours worked in a week
//     grossPay - gross pay for the week
//
// Returns: void
//
//**************************************************************

void printEmp(long int clockNumber, float wageRate, float hours,
              float overtimeHrs, float grossPay)

{

  // print the employee

  // TODO: add code to print out a single employee  %9.2f
  printf("%06i %9.2f %8.1f %7.2f %8.2f\n", clockNumber, wageRate, hours,
         overtimeHrs, grossPay);
}

// TODO: Add other functions here as needed
// ... remember your comment block headers for each function

//*************************************************************
// Function: calcOT
//
// Purpose: Calculate overtime hours
//
// Parameters:
//
//     STD_WORK_WEEK - value of standard hours(40)
//     hours - hours worked in a week
//     overtimeHrsReturn - return value 
//
//
// Returns: float
//
//**************************************************************

float calcOT(float hours) {

  float overtimeHrsReturn;

  if (hours > STD_WORK_WEEK) {
    /* TODO: calculate the three values with overtime */
    overtimeHrsReturn = hours - STD_WORK_WEEK;

  } else {
    overtimeHrsReturn = 0;
  }

  // return hours back to the calling function
  return (overtimeHrsReturn);

} // getHours

//*************************************************************
// Function: calcGross
//
// Purpose: Calculate Gross Pay
//
// Parameters:
//
//     STD_WORK_WEEK - value of standard hours(40)
//     overtimeHrs - overtime hours worked in a week
//     hours - hours worked in a week
//     wageRate - wage employee makes per hour
//
//     normalPay - normal amount which is 40hrs times wageRate
//     overtimePay - Any hours over 40; so wageRate times 1.5 times overtime hours
//     grossPayReturn - return value of normal pay and overtime pay added together.
//
// Returns: float
//
//**************************************************************

float calcGross(float hours, float wageRate, float overtimeHrs) {

  float normalPay = 0.0;
  float overtimePay = 0.0;
  float grossPayReturn = 0.0;

  if (overtimeHrs > 0) {

    normalPay = STD_WORK_WEEK * wageRate;
    overtimePay = overtimeHrs * (OVERTIME_RATE * wageRate);

  } else {

    normalPay = hours * wageRate;
  }

  // calculate gross pay
  grossPayReturn = normalPay + overtimePay;

  return (grossPayReturn);

} // calcGross

void printTotals(float wageTotal, float hoursTotal, float overtimeHrsTotal,
                 float grossPayTotal)

{

  // print the totals
  printf("\n-------------------------------------------------\n");

  printf("Totals: %9.2f %8.1f %7.2f %8.2f\n", wageTotal, hoursTotal,
         overtimeHrsTotal, grossPayTotal);
}

//*************************************************************
// Function: printAverages
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
//     wageAverage - Average of all wages
//     hoursAverage - Average of all hours
//     overtimeHrsAverage - Average of overtime hours 
//     grossPayAverage - Average of all gross pay 
//
// Returns: void
//
//**************************************************************
void printAverages(float wageTotal, float hoursTotal, float overtimeHrsTotal, float grossPayTotal)

{
  float wageAverage = wageTotal / SIZE;
  float hoursAverage = hoursTotal / SIZE;
  float overtimeHrsAverage = overtimeHrsTotal / SIZE;
  float grossPayAverage = grossPayTotal / SIZE;
  
  // print the Averages
  printf("Averages: %7.2f %8.1f %7.2f %8.2f\n", wageAverage, hoursAverage,
         overtimeHrsAverage, grossPayAverage);
}
