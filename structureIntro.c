/* user defined structure type for a date */
struct date
{
    int month;
     int day;
    int year;
};

#include <stdio.h>
int main ()
{

    struct date today;   /* defines a variable of type struct date */

    today.month = 3;
    today.day = 23;
    today.year = 1996;

    printf ("%d/%d/%d \n", today.month, today.day, today.year - 1900);  /* Y2K Issue ? */

    return (0);

}
