//********************************************************
//
// Assignment 7 - Structures and Strings
//
// Name: Alfio Raymond
//
// Class: C Programming, Fall 2023
//
// Date: 31 Oct 2023
//
// Description: Program which determines overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
// This assignment also adds the employee name, their tax state,
// and calculates the state tax, federal tax, and net pay.   It
// also calculates totals, averages, minimum, and maximum values.
//
// Call by reference design
//
//********************************************************

// Define and Includes

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Define Constants
#define SIZE 5
#define STD_HOURS 40.0
#define OT_RATE 1.5
#define MA_TAX_RATE 0.05
#define NH_TAX_RATE 0.0
#define VT_TAX_RATE 0.06
#define CA_TAX_RATE 0.07
#define DEFAULT_TAX_RATE 0.08
#define NAME_SIZE 20
#define TAX_STATE_SIZE 3
#define FED_TAX_RATE 0.25
#define FIRST_NAME_SIZE 10
#define LAST_NAME_SIZE 10

// Define a structure type to store an employee name
// ... note how one could easily extend this to other parts
// parts of a name:  Middle, Nickname, Prefix, Suffix, etc.
struct name
{
    char firstName[FIRST_NAME_SIZE];
    char lastName [LAST_NAME_SIZE];
};

// Define a global structure to pass employee data between functions
// Note that the structure type is global, but you don't want a variable
// of that type to be global. Best to declare a variable of that type
// in a function like main or another function and pass as needed.

struct employee
{
    struct name empName;
    char taxState [TAX_STATE_SIZE];
    long int clockNumber;
    float wageRate;
    float hours;
    float overtimeHrs;
    float grossPay;
    float stateTax;
    float fedTax;
    float netPay;
};

// this structure type defines the totals of all floating point items
// so they can be totaled and used also to calculate averages
struct totals
{
    float total_wageRate;
    float total_hours;
    float total_overtimeHrs;
    float total_grossPay;
    float total_stateTax;
    float total_fedTax;
    float total_netPay;
};

// this structure type defines the min and max values of all floating
// point items so they can be display in our final report
struct min_max
{
    float min_wageRate;
    float min_hours;
    float min_overtimeHrs;
    float min_grossPay;
    float min_stateTax;
    float min_fedTax;
    float min_netPay;
    float max_wageRate;
    float max_hours;
    float max_overtimeHrs;
    float max_grossPay;
    float max_stateTax;
    float max_fedTax;
    float max_netPay;
};

// this structure type defines the standard deviation of all floating point items

struct standardDeviation
{
    float sd_wageRate;
    float sd_hours;
    float sd_overtimeHrs;
    float sd_grossPay;
    float sd_stateTax;
    float sd_fedTax;
    float sd_netPay;
};
// define prototypes here for each function except main

void getHours (struct employee employeeData[], int theSize);
void printHeader (void);
void printEmp (struct employee employeeData[ ], int theSize);

void calcOT(struct employee employeeData[], int theSize);
void calcGross(struct employee employeeData[], int theSize);

void printTotals(struct employee employeeData[], int theSize);
void printAverages(struct employee employeeData[], int theSize);

void calcStateTax (struct employee employeeData[], int theSize);
void calcFedTax (struct employee employeeData[], int theSize);
void calcNetPay (struct employee employeeData[], int theSize);
struct totals calcEmployeeTotals (struct employee employeeData[],
                                  struct totals employeeTotals,
                                  int theSize);
                                 
struct min_max calcEmployeeMinMax (struct employee employeeData[],
                                   struct min_max employeeMinMax,
                                   int theSize);
                                  
void printEmpStatistics (struct totals employeeTotals, 
                         struct min_max employeeMinMax,
                         int theSize);

void calculateSD(struct employee employeeData[], struct standardDeviation standardDeviation, int theSize);
void calculateMedian(struct employee employeeData[], int theSize);
void swap(float *value1, float *value2);

int main ()
{
    // Set up a local variable and initialize the clock and wages of my employees
    struct employee employeeData [SIZE] = {
        { {"Connie", "Cobol"}, "MA", 98401, 10.60},
        { {"Mary", "Apl"}, "NH", 526488, 9.75 },
        { {"Frank", "Fortran"}, "VT", 765349, 10.50 },
        { {"Jeff", "Ada"}, "NY", 34645, 12.25 },
        { {"Anton", "Pascal"},"CA",127615, 8.35 }
    };

    // set up structure to store totals and initialize all to zero
    struct totals employeeTotals  = {0,0,0,0,0,0,0};
    
    // set up structure to store min and max values and initialize all to zero
    struct min_max employeeMinMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // set up structure to store standard deviation and initialize all to zero
    struct standardDeviation standardDeviation  = {0,0,0,0,0,0,0};
  
    // Call function needed to read hours
    getHours (employeeData, SIZE);

    // Calculate the overtime hours and the weekly gross pay
    calcOT(employeeData, SIZE);
    calcGross(employeeData, SIZE);

    // Calculate the state tax                                       
    calcStateTax (employeeData, SIZE);

    // Calculate the federal tax                                                   
    calcFedTax (employeeData, SIZE);
 
    // Calculate the net pay after taxes   
    calcNetPay (employeeData, SIZE); 
        
    // Keep a running sum of the employee totals
    // Note:  This remains a Call by Value design
    employeeTotals = calcEmployeeTotals (employeeData, employeeTotals, SIZE);
                                             
    // Keep a running update of the employee minimum and maximum values
    // Note:  This remains a Call by Value design
    employeeMinMax = calcEmployeeMinMax (employeeData, 
                                         employeeMinMax,
                                         SIZE);
  
    // Print a table header
    printHeader();

    // Function call to output results to the screen in table format
    printEmp (employeeData, SIZE);

    // print the totals and averages for all float items
    printEmpStatistics (employeeTotals, employeeMinMax, SIZE);

    // print standard deviation
    calculateSD(employeeData, standardDeviation, SIZE);
    calculateMedian(employeeData, SIZE);
  
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
    printf("\n--------------------------------------------------------------");
    printf("-------------------");
    printf("\nName                Tax  Clock# Wage   Hours  OT   Gross ");
    printf("  State  Fed      Net");
    printf("\n                   State                           Pay   ");
    printf("  Tax    Tax      Pay");
    
    printf("\n--------------------------------------------------------------");
    printf("-------------------");

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

    // used to format the employee name
    char name [FIRST_NAME_SIZE + LAST_NAME_SIZE + 1];

    // read in hours for each employee
    for (i = 0; i < theSize; ++i)
    {
        // While you could just print the first and last name in the printf
        // statement that follows, you could also use various C string library
        // functions to format the name exactly the way you want it.  Breaking
        // the name into first and last members additionally gives you some 
        // flexibility in printing.  This also becomes more useful if we decide
        // later to store other parts of a person's name. I really did this just 
        // to show you how to work with some of the common string functions.
        strcpy (name, employeeData[i].empName.firstName);
        strcat (name, " "); // add a space between first and last names
        strcat (name, employeeData[i].empName.lastName);
    
        // Print out a single employee
        printf("\n%-20.20s %-2.2s  %06li %5.2f  %4.1f  %4.1f %7.2f %6.2f %7.2f %8.2f",
                 name, employeeData[i].taxState, employeeData[i].clockNumber, 
                 employeeData[i].wageRate, employeeData[i].hours,
                 employeeData[i].overtimeHrs, employeeData[i].grossPay, 
                 employeeData[i].stateTax, employeeData[i].fedTax, 
                 employeeData[i].netPay);
               
    } // for
          
} // printEmp

//************************************************************* 
// Function: printEmpStatistics 
// 
// Purpose: Prints out the summary totals and averages of all 
//          floating point value items for all employees
//          that have been processed.  It also prints
//          out the min and max values.
// 
// Parameters: 
//
//   employeeTotals - a structure containing a running total 
//                    of all employee floating point items 
//   employeeMinMax - a structure containing all the minimum 
//                    and maximum values of all employee 
//                    floating point items
//   theSize - the total number of employees processed, used 
//             to check for zero or negative divide condition.
// 
// Returns: void
//  
//**************************************************************

void printEmpStatistics (struct totals employeeTotals, 
                         struct min_max employeeMinMax,
                         int theSize)
{
    
    // print a separator line
    printf("\n--------------------------------------------------------------");
    printf("-------------------");
    
    // print the totals for all the floating point fields
    // TODO - replace the zeros below with the correct reference to the 
    //        reference to the member total item
    printf("\nTotals:                         %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
             employeeTotals.total_wageRate,
             employeeTotals.total_hours,
             employeeTotals.total_overtimeHrs,
             employeeTotals.total_grossPay,
             employeeTotals.total_stateTax,
             employeeTotals.total_fedTax,
             employeeTotals.total_netPay);
    
    // make sure you don't divide by zero or a negative number
    if (theSize > 0)       
    {
        // print the averages for all the floating point fields
        // TODO - replace the zeros below with the correct reference to the 
        //        the average calculation using with the correct total item
        printf("\nAverages:                       %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
                 employeeTotals.total_wageRate/theSize,
                 employeeTotals.total_hours/theSize,
                 employeeTotals.total_overtimeHrs/theSize,
                 employeeTotals.total_grossPay/theSize,
                 employeeTotals.total_stateTax/theSize,
                 employeeTotals.total_fedTax/theSize,
                 employeeTotals.total_netPay/theSize);
    } // if
    
    // print the min and max values
    // TODO - replace the zeros below with the correct reference to the 
    //        to the min member field
    printf("\nMinimum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
              employeeMinMax.min_wageRate,
              employeeMinMax.min_hours,
              employeeMinMax.min_overtimeHrs,
              employeeMinMax.min_grossPay,
              employeeMinMax.min_stateTax,
              employeeMinMax.min_fedTax,
              employeeMinMax.min_netPay);
    
    // TODO - replace the zeros below with the correct reference to the 
    //        to the max member field
    printf("\nMaximum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
              employeeMinMax.max_wageRate,
              employeeMinMax.max_hours,
              employeeMinMax.max_overtimeHrs,
              employeeMinMax.max_grossPay,
              employeeMinMax.max_stateTax,
              employeeMinMax.max_fedTax,
              employeeMinMax.max_netPay);

}  // printEmpStatistics

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
  
  int i;
  
  for (i = 0; i < theSize ; ++i)
  {
      normalPay = employeeData[i].wageRate * (employeeData[i].hours - employeeData[i].overtimeHrs);
      overtimePay = employeeData[i].overtimeHrs * (employeeData[i].wageRate * OT_RATE);
      employeeData[i].grossPay = normalPay + overtimePay;
  }
  
}

//*************************************************************
// Function: calcStateTax
//
// Purpose: Calculates the State Tax owed based on gross pay
//          for each employee.  State tax rate is based on the 
//          the designated tax state based on where the
//          employee is actually performing the work.  Each
//          state decides their tax rate.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void
//
//**************************************************************

void calcStateTax (struct employee employeeData[], int theSize)
{
    
    int i; // loop and array index
    
    // calculate state tax based on where employee works
    for (i=0; i < theSize; ++i)
    {
        // Make sure tax state is all uppercase
        if (islower(employeeData[i].taxState[0]))
            employeeData[i].taxState[0] = toupper(employeeData[i].taxState[0]);
        if (islower(employeeData[i].taxState[1]))
            employeeData[i].taxState[1] = toupper(employeeData[i].taxState[1]);
        
        // calculate state tax based on where employee resides
        if (strcmp(employeeData[i].taxState, "MA") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * MA_TAX_RATE;
        else if (strcmp(employeeData[i].taxState, "NH") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * NH_TAX_RATE;
            
        // TODO:  Fix the state tax calculations for VT and CA ... right now
        //        both are set to zero
        else if (strcmp(employeeData[i].taxState, "VT") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * VT_TAX_RATE;
        else if (strcmp(employeeData[i].taxState, "CA") == 0)
           employeeData[i].stateTax = employeeData[i].grossPay * CA_TAX_RATE;
        else
            // any other state is the default rate
            employeeData[i].stateTax = employeeData[i].grossPay * DEFAULT_TAX_RATE;
    } // for
       
} // calcStateTax

//*************************************************************
// Function: calcFedTax
//
// Purpose: Calculates the Federal Tax owed based on the gross 
//          pay for each employee
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void
//
//**************************************************************

void calcFedTax (struct employee employeeData[], int theSize)
{
    
    int i;  // loop and array index
    
    // calculate the federal tax for each employee
    for (i=0; i < theSize; ++i)
    {

        // TODO:  Fix the fedTax calculation to be the gross pay
        //        multiplied by the Federal Tax Rate (use constant
        //        provided.)

        // Fed Tax is the same for all regardless of state
        employeeData[i].fedTax = employeeData[i].grossPay * FED_TAX_RATE;
        
    } // for
    
} // calcFedTax

//*************************************************************
// Function: calcNetPay
//
// Purpose: Calculates the net pay as the gross pay minus any
//          state and federal taxes owed for each employee.
//          Essentially, their "take home" pay.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void
//
//**************************************************************

void calcNetPay (struct employee employeeData[], int theSize)
{
    int i;               // loop and array index
    float theTotalTaxes; // the total state and federal tax
    
    // calculate the take home pay for each employee
    for (i=0; i < theSize; ++i)
    {
        // calculate the total state and federal taxes
        theTotalTaxes = employeeData[i].stateTax + employeeData[i].fedTax;
    
        // TODO:  Fix the netPay calculation to be the gross pay minus the
        //        the total taxes paid

        // calculate the net pay
        employeeData[i].netPay = employeeData[i].grossPay - theTotalTaxes;

    } // for
    
} // calcNetPay

//*************************************************************
// Function: calcEmployeeTotals
//
// Purpose: Performs a running total (sum) of each employee
//          floating point member in the array of structures 
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   employeeTotals - structure containing a running totals 
//                    of all fields above
//   theSize - the array size (i.e., number of employees)
//
// Returns: employeeTotals - updated totals in the updated 
//                           employeeTotals structure
//
//**************************************************************

struct totals calcEmployeeTotals (struct employee employeeData[],
                                  struct totals employeeTotals,
                                  int theSize)
{
    
    int i;  // loop and array index
    
    // total up each floating point item for all employees
    for (i = 0; i < theSize; ++i)
    {
        // add current employee data to our running totals
        employeeTotals.total_wageRate += employeeData[i].wageRate;
        employeeTotals.total_hours += employeeData[i].hours;
        employeeTotals.total_overtimeHrs += employeeData[i].overtimeHrs;
        employeeTotals.total_grossPay += employeeData[i].grossPay;
        employeeTotals.total_stateTax += employeeData[i].stateTax;
        employeeTotals.total_fedTax += employeeData[i].fedTax;
        employeeTotals.total_netPay += employeeData[i].netPay;
        
    } // for
    
    return (employeeTotals);
    
} // calcEmployeeTotals

//*************************************************************
// Function: calcEmployeeMinMax
//
// Purpose: Accepts various floating point values from an
//          employee and adds to a running update of min
//          and max values
//
// Parameters:
//
//   employeeData   - array of employees (i.e., struct employee)
//   employeeTotals - structure containing a running totals 
//                               of all fields above
//   theSize - the array size (i.e., number of employees)
//
// Returns: employeeMinMax - updated employeeMinMax structure
//
//**************************************************************

struct min_max calcEmployeeMinMax (struct employee employeeData[],
                                   struct min_max employeeMinMax,
                                   int theSize)
{

    int i;  // array and loop index
    
    // if this is the first set of data items, set 
    // them to the min and max
    employeeMinMax.min_wageRate = employeeData[0].wageRate; 
    employeeMinMax.min_hours = employeeData[0].hours;
    employeeMinMax.min_overtimeHrs = employeeData[0].overtimeHrs; 
    employeeMinMax.min_grossPay = employeeData[0].grossPay;
    employeeMinMax.min_stateTax = employeeData[0].stateTax;
    employeeMinMax.min_fedTax = employeeData[0].fedTax;
    employeeMinMax.min_netPay = employeeData[0].netPay;
        
    // set the max to the first element members
    employeeMinMax.max_wageRate = employeeData[0].wageRate; 
    employeeMinMax.max_hours = employeeData[0].hours;
    employeeMinMax.max_overtimeHrs = employeeData[0].overtimeHrs; 
    employeeMinMax.max_grossPay = employeeData[0].grossPay;
    employeeMinMax.max_stateTax = employeeData[0].stateTax;
    employeeMinMax.max_fedTax = employeeData[0].fedTax;
    employeeMinMax.max_netPay = employeeData[0].netPay;
    
    // compare the rest of the items to each other for min and max
    for (i = 1; i < theSize; ++i)
    {
        
        // check if current Wage Rate is the new min and/or max
        if (employeeData[i].wageRate < employeeMinMax.min_wageRate)
        {
            employeeMinMax.min_wageRate = employeeData[i].wageRate;
        }
        
        if (employeeData[i].wageRate > employeeMinMax.max_wageRate)
        {
            employeeMinMax.max_wageRate = employeeData[i].wageRate;
        }
        
        // TODO: do the same checking for all the other min and max items
        //       ... just repeat the two "if statements" with the right
        //       reference between the specific min and max fields and
        //       employeeData array of structures item.
        // HOURS
        if (employeeData[i].hours < employeeMinMax.min_hours)
        {
            employeeMinMax.min_hours = employeeData[i].hours;
        }
        
        if (employeeData[i].hours > employeeMinMax.max_hours)
        {
            employeeMinMax.max_hours = employeeData[i].hours;
        }

        // OVERTIME
        if (employeeData[i].overtimeHrs < employeeMinMax.min_overtimeHrs)
        {
            employeeMinMax.min_overtimeHrs = employeeData[i].overtimeHrs;
        }
        
        if (employeeData[i].overtimeHrs > employeeMinMax.max_overtimeHrs)
        {
            employeeMinMax.max_overtimeHrs = employeeData[i].overtimeHrs;
        }

        // GROSS PAY
        if (employeeData[i].grossPay < employeeMinMax.min_grossPay)
        {
            employeeMinMax.min_grossPay = employeeData[i].grossPay;
        }
        
        if (employeeData[i].grossPay > employeeMinMax.max_grossPay)
        {
            employeeMinMax.max_grossPay = employeeData[i].grossPay;
        }

        // STATE TAX
        if (employeeData[i].stateTax < employeeMinMax.min_stateTax)
        {
            employeeMinMax.min_stateTax = employeeData[i].stateTax;
        }
        
        if (employeeData[i].stateTax > employeeMinMax.max_stateTax)
        {
            employeeMinMax.max_stateTax = employeeData[i].stateTax;
        }

        // FED TAX
        if (employeeData[i].fedTax < employeeMinMax.min_fedTax)
        {
            employeeMinMax.min_fedTax = employeeData[i].fedTax;
        }
        
        if (employeeData[i].fedTax > employeeMinMax.max_stateTax)
        {
            employeeMinMax.max_fedTax = employeeData[i].fedTax;
        }

        // NET PAY
        if (employeeData[i].netPay < employeeMinMax.min_netPay)
        {
            employeeMinMax.min_netPay = employeeData[i].netPay;
        }
        
        if (employeeData[i].netPay > employeeMinMax.max_netPay)
        {
            employeeMinMax.max_netPay = employeeData[i].netPay;
        }
        
    } // else if
    
    // return all the updated min and max values to the calling function
    return (employeeMinMax);
    
} // calcEmployeeMinMax

//*************************************************************
// Function: calculateSD
//
// Purpose: Calculate the standard deviation of the values
//
// Parameters:
//
//   employeeData   - array of employees (i.e., struct employee)
//   standardDeviation - structure containing the standard deviation of all the fields
//   theSize - the array size (i.e., number of employees)
//
//   wageRateSum - sum of all the wage rates
//   hoursSum - sum of all the hours
//   overtimeHrsSum - sum of all the overtime hours
//   grossPaySum - sum of all the gross pay
//   stateTaxSum - sum of all the state taxes
//   fedTaxSum - sum of all the federal taxes
//   netPaySum - sum of all the net pay
//
//   wageRateMean - mean of all the wage rates
//   hoursMean - mean of all the hours
//   overtimeHrsMean - mean of all the hours
//   grossPayMean - mean of all the gross pay
//   stateTaxMean - mean of all the state taxes
//   FedTaxMean - mean of all the Federal taxes
//   netPayMean - mean of all the net pay
//
// Returns: employeeMinMax - updated employeeMinMax structure
//
//**************************************************************
void calculateSD(struct employee employeeData[], struct standardDeviation standardDeviation, int theSize)
{

  float wageRateSum = 0.0;
  float hoursSum = 0.0;
  float overtimeHrsSum = 0.0;
  float grossPaySum = 0.0;
  float stateTaxSum = 0.0;
  float fedTaxSum = 0.0;
  float netPaySum = 0.0;

  float wageRateMean = 0.0;
  float hoursMean = 0.0;
  float overtimeHrsMean = 0.0;
  float grossPayMean = 0.0;
  float stateTaxMean = 0.0;
  float fedTaxMean = 0.0;
  float netPayMean = 0.0;
  
    int i;
    for (i = 0; i < theSize; ++i) {
        wageRateSum += employeeData[i].wageRate;
        hoursSum += employeeData[i].hours;
        overtimeHrsSum += employeeData[i].overtimeHrs;
        grossPaySum += employeeData[i].grossPay;
        stateTaxSum += employeeData[i].stateTax;
        fedTaxSum += employeeData[i].fedTax;
        netPaySum += employeeData[i].netPay;
    }
  
    wageRateMean = wageRateSum / theSize;
    hoursMean = hoursSum / theSize;
    overtimeHrsMean = overtimeHrsSum / theSize;
    grossPayMean = grossPaySum / theSize;
    stateTaxMean = stateTaxSum / theSize;
    fedTaxMean = fedTaxSum / theSize;
    netPayMean = netPaySum / theSize;
  
    for (i = 0; i < theSize; ++i) {
      standardDeviation.sd_wageRate += pow(employeeData[i].wageRate - wageRateMean, 2);
      standardDeviation.sd_hours += pow(employeeData[i].hours - hoursMean, 2);
      standardDeviation.sd_overtimeHrs += pow(employeeData[i].overtimeHrs - overtimeHrsMean, 2);
      standardDeviation.sd_grossPay += pow(employeeData[i].grossPay - grossPayMean, 2);
      standardDeviation.sd_stateTax += pow(employeeData[i].stateTax - stateTaxMean, 2);
      standardDeviation.sd_fedTax += pow(employeeData[i].fedTax - fedTaxMean, 2);
      standardDeviation.sd_netPay += pow(employeeData[i].netPay - netPayMean, 2);
    }

  printf("\nStd Deviation:                   %4.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
    standardDeviation.sd_wageRate = sqrt(standardDeviation.sd_wageRate / theSize),
    standardDeviation.sd_hours = sqrt(standardDeviation.sd_hours / theSize),
    standardDeviation.sd_overtimeHrs = sqrt(standardDeviation.sd_overtimeHrs / theSize),
    standardDeviation.sd_grossPay = sqrt(standardDeviation.sd_grossPay / theSize),
    standardDeviation.sd_stateTax = sqrt(standardDeviation.sd_stateTax / theSize),
    standardDeviation.sd_fedTax = sqrt(standardDeviation.sd_fedTax / theSize),
    standardDeviation.sd_netPay = sqrt(standardDeviation.sd_netPay / theSize)
    );
}// calculate standard deviation

//*************************************************************
// Function: calculateMedian
//
// Purpose: Calculate the Median of the values
//
// Parameters:
//
//   employeeData   - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
//
// Returns: employeeMinMax - updated employeeMinMax structure
//
//**************************************************************
void calculateMedian(struct employee employeeData[], int theSize)
{

    int i,j;

  
    float medianWageRate[5] = {0,0,0,0,0};
    float medianHours[5] = {0,0,0,0,0};
    float medianOvertimeHrs[5] = {0,0,0,0,0};
    float medianGrossPay[5] = {0,0,0,0,0};
    float medianStateTax[5] = {0,0,0,0,0};
    float medianFedTax[5] = {0,0,0,0,0};
    float medianNetPay[5] = {0,0,0,0,0};
  
    for (i = 0; i < theSize; ++i) {
        medianWageRate[i] = employeeData[i].wageRate;
        medianHours[i] = employeeData[i].hours;
        medianOvertimeHrs[i] = employeeData[i].overtimeHrs;
        medianGrossPay[i] = employeeData[i].grossPay;
        medianStateTax[i] = employeeData[i].stateTax;
        medianFedTax[i] = employeeData[i].fedTax;
        medianNetPay[i] = employeeData[i].netPay;
    }

    for(i = 0;i < theSize-1;++i) 
      {
          for(j = 0;j < theSize-i-1;++j) 
          {
             if(medianWageRate[j] > medianWageRate[j+1])
              swap(&medianWageRate[j],&medianWageRate[j+1]);
          }
      }

    for(i = 0;i < theSize-1;++i) 
      {
          for(j = 0;j < theSize-i-1;++j) 
          {
            if(medianHours[j] > medianHours[j+1])
              swap(&medianHours[j],&medianHours[j+1]);
          }
      }

    for(i = 0;i < theSize-1;++i) 
    {
        for(j = 0;j < theSize-i-1;++j) 
        {
          if(medianOvertimeHrs[j] > medianOvertimeHrs[j+1])
            swap(&medianOvertimeHrs[j],&medianOvertimeHrs[j+1]);
        }
    }

    for(i = 0;i < theSize-1;++i) 
    {
        for(j = 0;j < theSize-i-1;++j) 
        {
          if(medianGrossPay[j] > medianGrossPay[j+1])
            swap(&medianGrossPay[j],&medianGrossPay[j+1]);
        }
    }

    for(i = 0;i < theSize-1;++i) 
    {
        for(j = 0;j < theSize-i-1;++j) 
        {
          if(medianStateTax[j] > medianStateTax[j+1])
            swap(&medianStateTax[j],&medianStateTax[j+1]);
        }
    }

    for(i = 0;i < theSize-1;++i) 
    {
        for(j = 0;j < theSize-i-1;++j) 
        {
          if(medianFedTax[j] > medianFedTax[j+1])
            swap(&medianFedTax[j],&medianFedTax[j+1]);
        }
    }

    for(i = 0;i < theSize-1;++i) 
    {
        for(j = 0;j < theSize-i-1;++j) 
        {
          if(medianNetPay[j] > medianNetPay[j+1])
            swap(&medianNetPay[j],&medianNetPay[j+1]);
        }
    }
  
    printf("\nMedian:                   %11.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f", medianWageRate[theSize/2],medianHours[theSize/2],medianOvertimeHrs[theSize/2],medianGrossPay[theSize/2],medianStateTax[theSize/2],medianFedTax[theSize/2],medianNetPay[theSize/2]);

}

//*************************************************************
// Function: swap
//
// Purpose: used for a bubble sort operation used in the median function
//
// Parameters:
//
//   temp   - temporary value holder for bubble sort
//   *value1 - pointer to value1 passed in
//   *value2 - pointer to value2 passed in
//
//
// Returns: employeeMinMax - updated employeeMinMax structure
//
//**************************************************************
void swap(float *value1, float *value2)
{
  float temp;

  temp = *value1;
  *value1 = *value2;
  *value2 = temp;
  
}