struct date
{
    int month;
    int day;
    int year;
};

/* function prototype */
struct date nextDay (struct date dateval);

#include <stdio.h>
int main ()
{

    /* two structure variables */
    struct date today, tomorrow;

    /* set today to the proper date */
    today.day = 17;
    today.year = 1996;
    today.month = 10;

    /* This statement illustrates the ability to pass a  */
    /* structure to a function and to return one as well */

    tomorrow = nextDay (today); /* tomorrow updated */

    printf ("%d/%d/%d\n", tomorrow.month,
                          tomorrow.day,
                          tomorrow.year-1900);

    return (0);
}

/********************************************************
** Function:  nextDay
**
** Description:  Returns the next day given a date
**
** Parameters:  dateval - a given date
**
** Returns:     dateval - updated next day date
**
*********************************************************/

struct date nextDay (struct date dateval) 
{

    ++dateval.day; /* add a day */ 

    return (dateval); /* return updated structure */

} /* nextDay */
