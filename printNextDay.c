#include <stdio.h>


/* Its OK to make the type global, that way all functions can use it */ 
/* Note that "struct date" is NOT a global variable */ 
struct date 
{ 
    int month; 
    int day; 
    int year; 
}; 

void printNextDay (struct date dateval);  /* function prototype */


int main () 
{  
    struct date today; /* local variable to main */ 

    /* Set up a date to pass to the printNextDay function */
    today.day = 17;
    today.year = 1996; 
    today.month = 10; 

    /* pass by value the information to our function*/  
    printNextDay (today);   
  
    /* The value of today will be unchanged - still the 17th */  
    printf ("%d/%d/%d \n", today.month, today.day, today.year-1900);


    return (0); 

} /* main */ 

/**************************************************************************
**
** Function: printNextDay
**
** Description: Simply prints the next day of a given 20th century date 
** in MM/DD/YYYY format. Does not check for last day in the month (known
** issue to be addressed in the future)
**
** Parameters: dataval - a structure with month, day, and year
**
** Returns: void
**
**********************************************************************/ 
void printNextDay (struct date dateval) 
{ 

    ++dateval.day; /* add a day to the value passed into this function */ 

    printf ("%d/%d/%d\n", dateval.month, dateval.day, dateval.year-1900); 

    return; /* optional, no value returned since it returns void */ 

} /* printNextDay */
