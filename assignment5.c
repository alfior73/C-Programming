//********************************************************
//
// Assignment 5 - Functions
//
// Name: Alfio Raymond
//
// Class: C Programming, Fall 2023
//
// Date: 11 Oct 2023
//
// Description: Program which determines overtime and
// gross pay for a set of employees with outputs sent
// to standard output (the screen).
//
// All functions are called by value
//
//********************************************************

#include <stdio.h>

// constants
#define SIZE 5
#define OVERTIME_RATE 1.5f
#define STD_WORK_WEEK 40.0f

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

  long int clockNumber[SIZE] = {98401, 526488, 765349, 34645, 127615}; // ID
  float grossPay[SIZE];    // gross pay
  float hours[SIZE];       // hours worked in a given week
  int i;                   // loop and array index
  float overtimeHrs[SIZE]; // overtime hours
  float wageRate[SIZE] = {10.60, 9.75, 10.50, 12.25, 8.35}; // hourly wage rate
  float wageTotal=0;
  float hoursTotal=0;
  float overtimeTotal=0;
  float grossPayTotal=0;

  // process each employee
  for (i = 0; i < SIZE; ++i) {

    // Read in hours for employee
    hours[i] = getHours(clockNumber[i]);

    // TODO: Function call to calculate overtime hours
    overtimeHrs[i] = calcOT(hours[i]);

    // TODO: Function call to calculate gross pay
    grossPay[i] = calcGross(hours[i], wageRate[i], overtimeHrs[i]);

    // Calculate totals
    wageTotal += wageRate[i];
    hoursTotal += hours[i];
    overtimeTotal += overtimeHrs[i];
    grossPayTotal += grossPay[i];
  }

  // print the header info
  printHeader();

  // print out each employee
  for (i = 0; i < SIZE; ++i) {

    // Print all the employees - call by value
    printEmp(clockNumber[i], wageRate[i], hours[i], overtimeHrs[i],
             grossPay[i]);

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
// Returns: void
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
// Returns: void
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