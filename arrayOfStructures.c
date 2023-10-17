struct time
{
    int hour, minutes, seconds;
};

struct date
{
    int month, day, year;
};

struct date_and_time
{
    struct date sdate;   /* stores date values */
    struct time stime;   /* stores time values */
};

#include <stdio.h>
int main ( )
{
    struct date_and_time event [3] =
    {
        { {2,1,1988}, {3,39,10} }, /* first date, then time values */
        { {5,6,1989}, {3,56,20} },
        { {8,5,1996}, {6,40,44} }
    };

    event [1].sdate.month = 10;  /* change a month value */

    ++event [1].stime.seconds; /* Add one second */

    for (int i=0; i < 3; ++i)
    {

        printf ("\nDate:\t %i/%i/%i\n",
                event[i].sdate.month,
                event[i].sdate.day,
                event[i].sdate.year);


        printf ("Time:\t %i hour(s) %i minute(s) %i second(s)\n",
                event[i].stime.hour,
                event[i].stime.minutes, 
                event[i].stime.seconds);
    }

    return (0);
}
