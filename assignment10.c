//********************************************************
//
// Assignment 10 - Linked Lists, Typedef, and Macros
//
// Name: Alfio Raymond
//
// Class: C Programming, Fall 2023
//
// Date: 23 Nov 2023
//
// Description: Program which determines overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
// This assignment also adds the employee name, their tax state,
// and calculates the state tax, federal tax, and net pay.   It
// also calculates totals, averages, minimum, and maximum values.
//
// Array and Structure references have all been replaced with
// pointer references to speed up the processing of this code.
// A linked list has been created and deployed to dynamically
// allocate and process employees as needed.
//
// It will also take advantage of the C Preprocessor features,
// in particular with using macros, and will replace all 
// struct type references in the code with a typedef alias
// reference.
//
// Call by Reference design (using pointers)
//
//********************************************************

// necessary header files
#include <stdio.h>
#include <string.h>
#include <ctype.h>   // for char functions
#include <stdlib.h>  // for malloc

// define constants
#define STD_HOURS 40.0
#define OT_RATE 1.5
#define MA_TAX_RATE 0.05
#define NH_TAX_RATE 0.0
#define VT_TAX_RATE 0.06
#define CA_TAX_RATE 0.07
#define DEFAULT_STATE_TAX_RATE 0.08
#define NAME_SIZE 20
#define TAX_STATE_SIZE 3
#define FED_TAX_RATE 0.25
#define FIRST_NAME_SIZE 10
#define LAST_NAME_SIZE 10

// define macros
#define CALC_OT_HOURS(theHours) ((theHours > STD_HOURS) ? theHours - STD_HOURS : 0)
#define CALC_STATE_TAX(thePay,theStateTaxRate) (thePay * theStateTaxRate)

// TODO - Create a macro called CALC_FED_TAX.  It will be very similar
//        to the CALC_STATE_TAX macro above.  Then call your macro in the
//        the calcFedTax function (replacing the current code)
#define CALC_FED_TAX(thePay,theFedTaxRate) (thePay * theFedTaxRate)

#define CALC_NET_PAY(thePay,theStateTax,theFedTax) (thePay - (theStateTax + theFedTax))
#define CALC_NORMAL_PAY(theWageRate,theHours,theOvertimeHrs) \
(theWageRate * (theHours - theOvertimeHrs))
#define CALC_OT_PAY(theWageRate,theOvertimeHrs) (theOvertimeHrs * (OT_RATE * theWageRate))

// TODO - These two macros are missing the correct logic, they are just setting
//        things to zero at this point.  Replace the 0.0 value below with the
//        right logic to determine the min and max values. These macros would
//        work very similar to the CALC_OT_HOURS macro above using a 
//        conditional expression operator.  The calls to these macros in the 
//        calcEmployeeMinMax function are already correct
//        ... so no changes needed there.

#define CALC_MIN(theValue, currentMin) ((theValue < currentMin) ? theValue : currentMin)
#define CALC_MAX(theValue, currentMax) ((theValue > currentMax) ? theValue : currentMax)

// Define a global structure type to store an employee name
// ... note how one could easily extend this to other parts
// parts of a name:  Middle, Nickname, Prefix, Suffix, etc.
struct name
{
    char firstName[FIRST_NAME_SIZE];
    char lastName [LAST_NAME_SIZE];
};

// Define a global structure type to pass employee data between functions
// Note that the structure type is global, but you don't want a variable
// of that type to be global. Best to declare a variable of that type
// in a function like main or another function and pass as needed.

// Note the "next" member has been added as a pointer to structure employee.
// This allows us to point to another data item of this same type, 
// allowing us to set up and traverse through all the linked 
// list nodes, with each node containing the employee information below.

// Also note the use of typedef to create an alias for struct employee
typedef struct employee
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
    struct employee * next;
} EMPLOYEE;

// This structure type defines the totals of all floating point items
// so they can be totaled and used also to calculate averages

// Also note the use of typedef to create an alias for struct totals
typedef struct totals
{
    float total_wageRate;
    float total_hours;
    float total_overtimeHrs;
    float total_grossPay;
    float total_stateTax;
    float total_fedTax;
    float total_netPay;
} TOTALS;

// This structure type defines the min and max values of all floating
// point items so they can be display in our final report

// Also note the use of typedef to create an alias for struct min_max

// TODO - Add a typedef alias to this structure, call it: MIN_MAX
//        Then update all associated code (prototypes plus the main, 
//        printEmpStatistics and calcEmployeeMinMax functions) that reference 
//        "struct min_max".  Essentially, replacing "struct min_max" with the 
//        typedef alias MIN_MAX

typedef struct 
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
} MIN_MAX;

// Define prototypes here for each function except main
//
// Note the use of the typedef alias values throughout
// the rest of this program, starting with the fucntions
// prototypes
//
//     EMPLOYEE instead of struct employee
//     TOTALS instead of struct totals
//     MIN_MAX instead of struct min_max

EMPLOYEE * getEmpData (void);
int isEmployeeSize (EMPLOYEE * head_ptr);
void calcOvertimeHrs (EMPLOYEE * head_ptr);
void calcGrossPay (EMPLOYEE * head_ptr);
void printHeader (void);
void printEmp (EMPLOYEE * head_ptr);
void calcStateTax (EMPLOYEE * head_ptr);
void calcFedTax (EMPLOYEE * head_ptr);
void calcNetPay (EMPLOYEE * head_ptr);
void calcEmployeeTotals (EMPLOYEE * head_ptr,
                         TOTALS * emp_totals_ptr);

// TODO - Update these two prototypes with the MIN_MAX typedef alias                              
void calcEmployeeMinMax (EMPLOYEE * head_ptr,
                         MIN_MAX * emp_minMax_ptr);

void printEmpStatistics (TOTALS * emp_totals_ptr, 
                         MIN_MAX * emp_minMax_ptr,
                         int size);

int main ()
{

    // ******************************************************************
    // Set up head pointer in the main function to point to the
    // start of the dynamically allocated linked list nodes that will be 
    // created and stored in the Heap area.
    // ******************************************************************
    EMPLOYEE * head_ptr; // always points to first linked list node

    int theSize; // number of employees processed

    // set up structure to store totals and initialize all to zero
    TOTALS employeeTotals  = {0,0,0,0,0,0,0};

    // pointer to the employeeTotals structure
    TOTALS * emp_totals_ptr = &employeeTotals;

    // TODO - Update these two variable declarations to use
    //        the MIN_MAX typedef alias

    // set up structure to store min and max values and initialize all to zero
    MIN_MAX employeeMinMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // pointer to the employeeMinMax structure
    MIN_MAX * emp_minMax_ptr = &employeeMinMax;

    // ********************************************************************
    // Read the employee input and dynamically allocate and set up our 
    // linked list in the Heap area.  The address of the first linked
    // list item representing our first employee will be returned and
    // its value is set in our head_ptr. We can then use the head_ptr 
    // throughout the rest of this program anytime we want to get to get 
    // to the beginning of our linked list.
    // ********************************************************************

    head_ptr = getEmpData ();

    // ********************************************************************
    // With the head_ptr now pointing to the first linked list node, we
    // can pass it to any function who needs to get to the starting point
    // of the linked list in the Heap.  From there, functions can traverse 
    // through the linked list to access and/or update each employee.
    //
    // Important:  Don't update the head_ptr ... otherwise, you could lose
    //             the address in the heap of the first linked list node.
    //
    // ********************************************************************

    // determine how many employees are in our linked list

    theSize = isEmployeeSize (head_ptr);

    // Skip all the function calls to process the data if there
    // was no employee information to read in the input
    if (theSize <= 0)
    {
        // print a user friendly message and skip the rest of the processing
        printf("\n\n**** There was no employee input to process ***\n");
    }

    else // there are employees to be processed
    {    

        // *********************************************************
        // Perform calculations and print out information as needed
        // *********************************************************

        // Calculate the overtime hours
        calcOvertimeHrs (head_ptr);

        // Calculate the weekly gross pay
        calcGrossPay (head_ptr); 

        // Calculate the state tax                                       
        calcStateTax (head_ptr);

        // Calculate the federal tax                                                   
        calcFedTax (head_ptr);

        // Calculate the net pay after taxes   
        calcNetPay (head_ptr); 

        // *********************************************************
        // Keep a running sum of the employee totals
        //
        // Note the & to specify the address of the employeeTotals
        // structure.  Needed since pointers work with addresses.
        // Unlike array names, C does not see structure names
        // as address, hence the need for using the &employeeTotals
        // which the complier sees as "address of" employeeTotals
        // *********************************************************
        calcEmployeeTotals (head_ptr, 
                            &employeeTotals);

        // *****************************************************************                                  
        // Keep a running update of the employee minimum and maximum values
        //
        // Note we are passing the address of the MinMax structure
        // *****************************************************************
        calcEmployeeMinMax (head_ptr, 
                            &employeeMinMax);

        // Print the column headers
        printHeader();

        // print out final information on each employee
        printEmp (head_ptr); 

        // **************************************************
        // print the totals and averages for all float items
        //
        // Note that we are passing the addresses of the 
        // the two structures
        // **************************************************
        printEmpStatistics (&employeeTotals, 
                            &employeeMinMax, 
                            theSize);
    }

    // indicate that the program completed all processing
    printf ("\n\n *** End of Program *** \n");

    return (0); // success

} // main

//**************************************************************
// Function: getEmpData 
// 
// Purpose: Obtains input from user: employee name (first an last), 
//          tax state, clock number, hourly wage, and hours worked
//          in a given week.
//
//          Information in stored in a dynamically created linked
//          list for all employees.
//          
// Parameters: void
// 
// Returns:
//
//    head_ptr - a pointer to the beginning of the dynamically
//               created linked list that contains the initial
//               input for each employee.
//  
//**************************************************************

EMPLOYEE * getEmpData (void)
{

    char   answer[80];    // user prompt response
    int    more_data = 1; // a flag to indicate if another employee
                          // needs to be processed
    char   value;         // the first char of the user prompt response

    EMPLOYEE *current_ptr,   // pointer to current node
             *head_ptr;      // always points to first node

    // Set up storage for first node   
    head_ptr = (EMPLOYEE *) malloc (sizeof(EMPLOYEE));
    current_ptr = head_ptr;

    // process while there is still input
    while (more_data)
    {

        // read in employee first and last name
        printf ("\nEnter employee first name: ");
        scanf ("%s", current_ptr->empName.firstName);
        printf ("\nEnter employee last name: ");
        scanf ("%s", current_ptr->empName.lastName);

        // read in employee tax state
        printf ("\nEnter employee two character tax state: ");
        scanf ("%s", current_ptr->taxState);

        // read in employee clock number
        printf("\nEnter employee clock number: ");
        scanf("%li", & current_ptr -> clockNumber);

        // read in employee wage rate
        printf("\nEnter employee hourly wage: ");
        scanf("%f", & current_ptr -> wageRate);

        // read in employee hours worked
        printf("\nEnter hours worked this week: ");
        scanf("%f", & current_ptr -> hours);

        // ask user if they would like to add another employee
        printf("\nWould you like to add another employee? (y/n): ");
        scanf("%s", answer);

        // check first character for a 'Y' for yes
        // Ask user if they want to add another employee
        if ((value = toupper(answer[0])) != 'Y')
        {
           // no more employees to process
           current_ptr->next = (EMPLOYEE *) NULL;
           more_data = 0; 
        }
        else // Yes, another employee
        {
           // set the next pointer of the current node to point to the new node
           current_ptr->next = (EMPLOYEE *) malloc (sizeof(EMPLOYEE));
           // move the current node pointer to the new node
           current_ptr = current_ptr->next;
        }

    } // while

    return(head_ptr);

} // getEmpData

//*************************************************************
// Function: isEmployeeSize
//
// Purpose: Traverses the linked list and keeps a running count
//          on how many employees are currently in our list. 
//
// Parameters:
//
//   head_ptr - pointer to the initial node in our linked list
//
// Returns:
//
//   theSize - the number of employees in our linked list
//
//**************************************************************

int isEmployeeSize (EMPLOYEE * head_ptr)
{

    EMPLOYEE * current_ptr;   // pointer to current node
    int theSize;              // number of link list nodes
                              // (i.e., employees)

    theSize = 0; // initialize

    // assume there is no data if the first node does
    // not have an employee name
    if (head_ptr->empName.firstName[0] != '\0')
    {

        // traverse through the linked list, keep a running count of nodes
        for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
        {  

            ++theSize;  // employee node found, increment

        } // for
    }

    return (theSize);  // number of nodes (i.e., employees)


} // isEmployeeSize

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

//************************************************************* 
// Function: printEmp 
// 
// Purpose: Prints out all the information for each employee
//          in a nice and orderly table format.
// 
// Parameters: 
//
//   head_ptr - pointer to the beginning of our linked list
// 
// Returns: void
//  
//**************************************************************

void printEmp (EMPLOYEE * head_ptr)
{


    // Used to format the employee name
    char name [FIRST_NAME_SIZE + LAST_NAME_SIZE + 1];

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to process each employee
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // While you could just print the first and last name in the printf
        // statement that follows, you could also use various C string library
        // functions to format the name exactly the way you want it.  Breaking
        // the name into first and last members additionally gives you some 
        // flexibility in printing.  This also becomes more useful if we decide
        // later to store other parts of a person's name. I really did this just 
        // to show you how to work with some of the common string functions.
        strcpy (name, current_ptr->empName.firstName);
        strcat (name, " "); // add a space between first and last names
        strcat (name, current_ptr->empName.lastName);

        // Print out current employee in the current linked list node
        printf("\n%-20.20s %-2.2s  %06li %5.2f  %4.1f  %4.1f %7.2f %6.2f %7.2f %8.2f",
               name, current_ptr->taxState, current_ptr->clockNumber, 
               current_ptr->wageRate, current_ptr->hours,
               current_ptr->overtimeHrs, current_ptr->grossPay, 
               current_ptr->stateTax, current_ptr->fedTax, 
               current_ptr->netPay);

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
//   emp_totals_ptr - pointer to a structure containing a running total 
//                    of all employee floating point items
//
//   emp_minMax_ptr - pointer to a structure containing
//                    the minimum and maximum values of all
//                    employee floating point items
//
//   tjeSize - the total number of employees processed, used 
//             to check for zero or negative divide condition.
// 
// Returns: void
//  
//**************************************************************

// TODO - Update the emp_MinMax_ptr parameter below to use the MIN_MAX 
//        typedef alias

void printEmpStatistics (TOTALS  * emp_totals_ptr,
                         MIN_MAX * emp_minMax_ptr,
                         int theSize)
{

    // print a separator line
    printf("\n--------------------------------------------------------------");
    printf("-------------------");

    // print the totals for all the floating point items
    printf("\nTotals:                         %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_totals_ptr->total_wageRate,
           emp_totals_ptr->total_hours,
           emp_totals_ptr->total_overtimeHrs,
           emp_totals_ptr->total_grossPay,
           emp_totals_ptr->total_stateTax,
           emp_totals_ptr->total_fedTax,
           emp_totals_ptr->total_netPay);

    // make sure you don't divide by zero or a negative number
    if (theSize > 0)       
    {
        // print the averages for all the floating point items
        printf("\nAverages:                       %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
               emp_totals_ptr->total_wageRate/theSize,
               emp_totals_ptr->total_hours/theSize,
               emp_totals_ptr->total_overtimeHrs/theSize,
               emp_totals_ptr->total_grossPay/theSize,
               emp_totals_ptr->total_stateTax/theSize,
               emp_totals_ptr->total_fedTax/theSize,
               emp_totals_ptr->total_netPay/theSize);

    } // if

    // print the min and max values for each item

    printf("\nMinimum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_minMax_ptr->min_wageRate,
           emp_minMax_ptr->min_hours,
           emp_minMax_ptr->min_overtimeHrs,
           emp_minMax_ptr->min_grossPay,
           emp_minMax_ptr->min_stateTax,
           emp_minMax_ptr->min_fedTax,
           emp_minMax_ptr->min_netPay);

    printf("\nMaximum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_minMax_ptr->max_wageRate,
           emp_minMax_ptr->max_hours,
           emp_minMax_ptr->max_overtimeHrs,
           emp_minMax_ptr->max_grossPay,
           emp_minMax_ptr->max_stateTax,
           emp_minMax_ptr->max_fedTax,
           emp_minMax_ptr->max_netPay);

    // print out the total employees process
    printf ("\n\nThe total employees processed was: %i\n", theSize);

}  // printEmpStatistics

//*************************************************************
// Function: calcOvertimeHrs
//
// Purpose: Calculates the overtime hours worked by an employee
//          in a given week for each employee.
//
// Parameters:
//
//   head_ptr - pointer to the beginning of our linked list
//
// Returns: void (the overtime hours gets updated by reference)
//
//**************************************************************

void calcOvertimeHrs (EMPLOYEE * head_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate overtime hours
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {  
        current_ptr->overtimeHrs = CALC_OT_HOURS(current_ptr->hours);

    } // for


} // calcOvertimeHrs

//*************************************************************
// Function: calcGrossPay
//
// Purpose: Calculates the gross pay based on the the normal pay
//          and any overtime pay for a given week for each
//          employee.
//
// Parameters:
//
//   head_ptr - pointer to the beginning of our linked list
//
// Returns: void (the gross pay gets updated by reference)
//
//**************************************************************

void calcGrossPay (EMPLOYEE * head_ptr)
{

    float theNormalPay;   // normal pay without any overtime hours
    float theOvertimePay; // overtime pay

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate gross pay
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // calculate normal pay and any overtime pay
        theNormalPay = CALC_NORMAL_PAY(current_ptr->wageRate,
                                       current_ptr->hours,
                                       current_ptr->overtimeHrs);
        theOvertimePay = CALC_OT_PAY(current_ptr->wageRate,
                                     current_ptr->overtimeHrs);

        // calculate gross pay for employee as normalPay + any overtime pay
        current_ptr->grossPay = theNormalPay + theOvertimePay;

    }

} // calcGrossPay

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
//   head_ptr - pointer to the beginning of our linked list
//
// Returns: void (the state tax gets updated by reference)
//
//**************************************************************

void calcStateTax (EMPLOYEE * head_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate the state tax
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // Make sure tax state is all uppercase
        if (islower(current_ptr->taxState[0]))
            current_ptr->taxState[0] = toupper(current_ptr->taxState[0]);
        if (islower(current_ptr->taxState[1]))
            current_ptr->taxState[1] = toupper(current_ptr->taxState[1]);

        // calculate state tax based on where employee resides
        if (strcmp(current_ptr->taxState, "MA") == 0)
            current_ptr->stateTax = CALC_STATE_TAX(current_ptr->grossPay,
                                                   MA_TAX_RATE);
        else if (strcmp(current_ptr->taxState, "VT") == 0)
            current_ptr->stateTax = CALC_STATE_TAX(current_ptr->grossPay,
                                                   VT_TAX_RATE);
        else if (strcmp(current_ptr->taxState, "NH") == 0)
            current_ptr->stateTax = CALC_STATE_TAX(current_ptr->grossPay,
                                                   NH_TAX_RATE);
        else if (strcmp(current_ptr->taxState, "CA") == 0)
            current_ptr->stateTax = CALC_STATE_TAX(current_ptr->grossPay,
                                                   CA_TAX_RATE);
        else
            // any other state is the default rate
            current_ptr->stateTax = CALC_STATE_TAX(current_ptr->grossPay,
                                                   DEFAULT_STATE_TAX_RATE);

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
//   head_ptr - pointer to the beginning of our linked list
//
// Returns: void (the federal tax gets updated by reference)
//
//**************************************************************

void calcFedTax (EMPLOYEE * head_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate the federal tax
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {

        // TODO - Replace the below statement after the "=" with
        //        a call to the CALC_FED_TAX macro you created

        // Fed Tax is the same for all regardless of state
        current_ptr->fedTax = CALC_FED_TAX(current_ptr->grossPay, FED_TAX_RATE);

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
//   head_ptr - pointer to the beginning of our linked list
//
// Returns: void (the net pay gets updated by reference)
//
//**************************************************************

void calcNetPay (EMPLOYEE * head_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate the net pay
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // calculate the net pay
        current_ptr->netPay = CALC_NET_PAY(current_ptr->grossPay,
                                           current_ptr->stateTax,
                                           current_ptr->fedTax);
    } // for

} // calcNetPay

//*************************************************************
// Function: calcEmployeeTotals
//
// Purpose: Performs a running total (sum) of each employee
//          floating point member item stored in our linked list 
//
// Parameters:
//
//   head_ptr - pointer to the beginning of our linked list
//   emp_totals_ptr - pointer to a structure containing the 
//                    running totals of each floating point
//                    member for all employees in our linked
//                    list
//
// Returns: 
//
//   void (the employeeTotals structure gets updated by reference)
//
//**************************************************************

void calcEmployeeTotals (EMPLOYEE * head_ptr,
                         TOTALS   * emp_totals_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // traverse through the linked list to calculate a running 
    // sum of each employee floating point member item
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // add current employee data to our running totals
        emp_totals_ptr->total_wageRate += current_ptr->wageRate;
        emp_totals_ptr->total_hours += current_ptr->hours;
        emp_totals_ptr->total_overtimeHrs += current_ptr->overtimeHrs;
        emp_totals_ptr->total_grossPay += current_ptr->grossPay;
        emp_totals_ptr->total_stateTax += current_ptr->stateTax;
        emp_totals_ptr->total_fedTax += current_ptr->fedTax;
        emp_totals_ptr->total_netPay += current_ptr->netPay;

        // Note:  We don't need to increment emp_totals_ptr

    } // for

    // no need to return anything since we used pointers and have
    // been referencing the linked list stored in the Heap area. 
    // Since we used a pointer as well to the totals structure,
    // all values in it have been updated.

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
//   head_ptr - pointer to the beginning of our linked list
//   emp_minMax_ptr - pointer to the min/max structure
//
// Returns: 
//
//   void (employeeMinMax structure updated by reference)
//
//**************************************************************

// TODO - Update the emp_minMax_ptr parameter below to use the
//        the MIN_MAX typedef alias

void calcEmployeeMinMax (EMPLOYEE * head_ptr,
                         MIN_MAX  * emp_minMax_ptr)
{

    EMPLOYEE * current_ptr; // pointer to current node

    // *************************************************
    // At this point, head_ptr is pointing to the first
    // employee .. the first node of our linked list
    //
    // As this is the first employee, set each min 
    // min and max value using our emp_minMax_ptr
    // to the associated member fields below.  They
    // will become the initial baseline that we  
    // can check and update if needed against the 
    // remaining employees in our linked list.
    // *************************************************


    // set to first employee, our initial linked list node
    current_ptr = head_ptr;

    // set the min to the first employee members
    emp_minMax_ptr->min_wageRate = current_ptr->wageRate; 
    emp_minMax_ptr->min_hours = current_ptr->hours;
    emp_minMax_ptr->min_overtimeHrs = current_ptr->overtimeHrs; 
    emp_minMax_ptr->min_grossPay = current_ptr->grossPay;
    emp_minMax_ptr->min_stateTax = current_ptr->stateTax;
    emp_minMax_ptr->min_fedTax = current_ptr->fedTax;
    emp_minMax_ptr->min_netPay = current_ptr->netPay;

    // set the max to the first employee members
    emp_minMax_ptr->max_wageRate = current_ptr->wageRate; 
    emp_minMax_ptr->max_hours = current_ptr->hours;
    emp_minMax_ptr->max_overtimeHrs = current_ptr->overtimeHrs;
    emp_minMax_ptr->max_grossPay = current_ptr->grossPay;
    emp_minMax_ptr->max_stateTax = current_ptr->stateTax;
    emp_minMax_ptr->max_fedTax = current_ptr->fedTax;
    emp_minMax_ptr->max_netPay = current_ptr->netPay;

    // ******************************************************
    // move to the next employee
    //
    // if this the only employee in our linked list
    // current_ptr will be NULL and will drop out the 
    // the for loop below, otherwise, the second employee
    // and rest of the employees (if any) will be processed
    // ******************************************************
    current_ptr = current_ptr->next;

    // traverse the linked list
    // compare the rest of the employees to each other for min and max
    for (; current_ptr; current_ptr = current_ptr->next) 
    {

        // check if current Wage Rate is the new min and/or max
        emp_minMax_ptr->min_wageRate = 
           CALC_MIN(current_ptr->wageRate,emp_minMax_ptr->min_wageRate);
        emp_minMax_ptr->max_wageRate = 
           CALC_MAX(current_ptr->wageRate,emp_minMax_ptr->max_wageRate);

        // check if current Hours is the new min and/or max
        emp_minMax_ptr->min_hours = 
           CALC_MIN(current_ptr->hours,emp_minMax_ptr->min_hours);
        emp_minMax_ptr->max_hours = 
           CALC_MAX(current_ptr->hours,emp_minMax_ptr->max_hours);       

        // check if current Overtime Hours is the new min and/or max
        emp_minMax_ptr->min_overtimeHrs = 
           CALC_MIN(current_ptr->overtimeHrs,emp_minMax_ptr->min_overtimeHrs);
        emp_minMax_ptr->max_overtimeHrs = 
           CALC_MAX(current_ptr->overtimeHrs,emp_minMax_ptr->max_overtimeHrs);

        // check if current Gross Pay is the new min and/or max
        emp_minMax_ptr->min_grossPay = 
           CALC_MIN(current_ptr->grossPay,emp_minMax_ptr->min_grossPay);
        emp_minMax_ptr->max_grossPay = 
           CALC_MAX(current_ptr->grossPay,emp_minMax_ptr->max_grossPay);

        // check if current State Tax is the new min and/or max
        emp_minMax_ptr->min_stateTax = 
           CALC_MIN(current_ptr->stateTax,emp_minMax_ptr->min_stateTax);
        emp_minMax_ptr->max_stateTax = 
           CALC_MAX(current_ptr->stateTax,emp_minMax_ptr->max_stateTax);

        // check if current Federal Tax is the new min and/or max
        emp_minMax_ptr->min_fedTax = 
           CALC_MIN(current_ptr->fedTax,emp_minMax_ptr->min_fedTax);
        emp_minMax_ptr->max_fedTax = 
           CALC_MAX(current_ptr->fedTax,emp_minMax_ptr->max_fedTax);

        // check if current Net Pay is the new min and/or max
        emp_minMax_ptr->min_netPay = 
           CALC_MIN(current_ptr->netPay,emp_minMax_ptr->min_netPay);
        emp_minMax_ptr->max_netPay = 
           CALC_MAX(current_ptr->netPay,emp_minMax_ptr->max_netPay);

    } // for

    // no need to return anything since we used pointers and have
    // been referencing all the nodes in our linked list where
    // they reside in memory (the Heap area)

} // calcEmployeeMinMax
