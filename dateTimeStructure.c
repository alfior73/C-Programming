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
    struct date sdate;
    struct time stime;
};

#include <stdio.h>
int main ()
{

    struct date_and_time event =
    {
        {2,1,1988}, /* date - month, day, year*/
        {3,30,0}    /* time - hour, minutes, and seconds*/
    };   

    event.sdate.month = 10;

    ++event.stime.seconds;

    printf ("\nDate:\t %i/%i/%i\n",
            event.sdate.month,
            event.sdate.day,
            event.sdate.year);

    printf ("Time:\t %i hour(s) %i minute(s) %i second(s)\n",
            event.stime.hour,
            event.stime.minutes,
            event.stime.seconds);

    return (0);

} /* main */
