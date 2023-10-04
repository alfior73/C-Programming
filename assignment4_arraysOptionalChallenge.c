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
#define STD_HOURS 40.0
#define SIZE 5
#define OT_RATE 1.5

int main ( ) 
{ 
    // employee clock number array
    long int clockNumber[SIZE] = {98401, 526488,765349, 34645, 127615};
    // hourly wage rate array
    float wageRate [SIZE] = {10.6, 9.75, 10.5, 12.25, 8.35};
    // hours array
    float hours [SIZE] = {51.0, 42.5, 37.0, 45.0, 0.0};
    
    float grossPay;       // gross pay for week (wage * hours)
    float normalPay;      // Standard weekly normal pay without overtime 
    float overtimeHrs;    // Overtime hours worked beyond a normal week (40 hours)
    float overtimePay;    // Any hours worked past the normal scheduled work week
    float wageTotal = 0;      // Total of all wages
    float hoursTotal = 0;     // Total of all hours
    float overtimeTotal = 0;  // Total of all overtime
    float grossTotal = 0;     // Total of all final wages
    float avgWageTotal = 0;
    float avgHoursTotal = 0;
    float avgOvertimeTotal = 0;
    float avgGrossTotal = 0;

    printf ("             ***Pay Calculator*** \n\n");

    // TODO - Add a loop of your choice here (for, while, or do) to process each employee

    // print out employee information
    printf ("\n\t----------------------------------------------------------\n"); 
    printf ("\tClock #     Wage    Hours    OT     Gross\n"); 
    printf ("\t----------------------------------------------------------\n"); 
  
    for(int i = 0; i < SIZE; i++) {
      
        if (hours[i] > STD_HOURS) {
          /* TODO: calculate the three values with overtime */
          overtimeHrs = hours[i] - STD_HOURS;
          normalPay = STD_HOURS * wageRate[i];
          overtimePay = overtimeHrs * (OT_RATE * wageRate[i]);

          if(hoursTotal == 0)
            hoursTotal = hours[i];
          else
            hoursTotal += hours[i];

          if(overtimeTotal == 0)
            overtimeTotal = overtimeHrs;
          else
            overtimeTotal += overtimeHrs;
          
        }
        else {
          overtimeHrs = 0;
          overtimePay = 0.00;
          normalPay = hours[i] * wageRate[i];
          
            if(hoursTotal == 0)
              hoursTotal = hours[i];
            else
              hoursTotal += hours[i];
          
        }
      
        // calculate gross pay
        grossPay = normalPay + overtimePay;

        // calculate totals of wages, hours, overtime and gross
        wageTotal += wageRate[i];
        grossTotal += grossPay;

        // average totals of wages, hours, overtime and gross
        avgWageTotal = wageTotal / SIZE;
        avgHoursTotal = hoursTotal / SIZE;
        avgOvertimeTotal = overtimeTotal / SIZE;
        avgGrossTotal = grossTotal / SIZE;

        // print the data for the current employee
        printf ("\t%06i %9.2f %8.1f %7.2f %8.2f\n", clockNumber[i], wageRate[i], hours[i], overtimeHrs, grossPay);
        
      // TODO - end your loop here
      
    }
    printf ("\n\t----------------------------------------------------------\n"); 
    printf("\tTotal%11.2f %8.1f %7.2f %9.2f\n", wageTotal, hoursTotal, overtimeTotal, grossTotal);
    printf ("\tAverage %8.2f %8.1f %7.2f %9.2f\n\n", avgWageTotal, avgHoursTotal, avgOvertimeTotal, avgGrossTotal);
  
    // Closing message
    printf ("\n Thank you for using UMass Payment System\n\n");
  
    return (0); // success

} // main
