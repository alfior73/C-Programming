//******************************************************* 
// 
// Homework: 4
// 
// Name: Alfio Raymond
// 
// Class: C Programming, Fall 2023
// 
// Date: 3 Oct 2023
// 
// Description: Program which determines gross pay
// and outputs are sent to standard output (the screen).
// 
// 
//******************************************************** 

#include <stdio.h>  
#define NUM_EMPLOYEES 5
#define STD_HOURS 40.0
#define SIZE 5
#define OT_RATE 1.5

int main ( ) 
{ 
    // employee clock number array
    long int clockNumber[SIZE] = {98401, 526488,765349, 34645, 127615};
    // hourly wage rate array
    float wageRate [SIZE] = {10.6, 9.75, 10.5, 12.25, 8.35};
  
    float grossPay;       // gross pay for week (wage * hours)
    float hours;          // number of hours worked per week
    float normalPay;      // Standard weekly normal pay without overtime 
    float overtimeHrs;    // Overtime hours worked beyond a normal week (40 hours)
    float overtimePay;    // Any hours worked past the normal scheduled work week
  
    float wageTotal = 0;      // Total of all wages
    float hoursTotal = 0;     // Total of all hours
    float overtimeTotal = 0;  // Total of all overtime
    float grossTotal = 0;     // Total of all final wages
    float normalPayTotal = 0;  // Total of all normal wages
    float overtimePayTotal = 0; // Total of all overtime wages
  
    float avgWageTotal = 0;
    float avgHoursTotal = 0;
    float avgOvertimeTotal = 0;
    float avgGrossTotal = 0;
    float avgNormalPayTotal = 0;
    float avgOTPayTotal = 0;

    printf ("             ***Pay Calculator*** \n\n");

    // TODO - Add a loop of your choice here (for, while, or do) to process each employee

    for(int i = 0; i < NUM_EMPLOYEES; i++) {
      
        printf ("Enter the number of hours the employee worked: "); 
        scanf ("%f", &hours); 
  
        if (hours > STD_HOURS) {
          /* TODO: calculate the three values with overtime */
          overtimeHrs = hours - STD_HOURS;
          normalPay = STD_HOURS * wageRate[i];
          overtimePay = overtimeHrs * (OT_RATE * wageRate[i]);

          if(hoursTotal == 0)
            hoursTotal = hours;
          else
            hoursTotal += hours;

          if(overtimeTotal == 0)
            overtimeTotal = overtimeHrs;
          else
            overtimeTotal += overtimeHrs;
          
        }
        else {
          overtimeHrs = 0;
          overtimePay = 0.00;
          normalPay = hours * wageRate[i];
          
            if(hoursTotal == 0)
              hoursTotal = hours;
            else
              hoursTotal += hours;
          
        }
      
        // calculate gross pay
        grossPay = normalPay + overtimePay;

        // calculate normal pay total
        normalPayTotal += normalPay;

        // calculate OT pay total
        overtimePayTotal += overtimePay;
      
        // calculate totals of wages, hours, overtime and gross
        wageTotal += wageRate[i];
        grossTotal += grossPay;

        // average totals of wages, hours, overtime and gross
        avgWageTotal = wageTotal / SIZE;
        avgHoursTotal = hoursTotal / SIZE;
        avgOvertimeTotal = overtimeTotal / SIZE;
        avgGrossTotal = grossTotal / SIZE;
        avgNormalPayTotal = normalPayTotal / SIZE;
        avgOTPayTotal = overtimePayTotal / SIZE;

      
        // print out employee information
        printf ("\n\t------------------------------------------------------------------\n"); 
        printf ("\tClock #     Wage    Hours    OT     Gross    Normal Pay    OT Pay\n"); 
        printf ("\t-----------------------------------------------------------------\n"); 
    
        // print the data for the current employee
        printf ("\t%06i %9.2f %8.1f %7.2f %8.2f %9.2f %12.2f\n", clockNumber[i], wageRate[i], hours, overtimeHrs, grossPay, normalPay, overtimePay);
        printf ("\n\t------------------------------------------------------------------\n"); 
        printf("\tTotal%11.2f %8.1f %7.2f %9.2f %9.2f %10.2f\n", wageTotal, hoursTotal, overtimeTotal, grossTotal, normalPayTotal, overtimePayTotal);
        printf ("\tAverage %8.2f %8.1f %6.2f %9.2f %9.2f %10.2f\n\n", avgWageTotal, avgHoursTotal, avgOvertimeTotal, avgGrossTotal, avgNormalPayTotal, avgOTPayTotal);
        /* 
          
        */
      // TODO - end your loop here
      
    }

    // Closing message
    printf ("\n Thank you for using UMass Payment System\n\n");
  
    return (0); // success

} // main
