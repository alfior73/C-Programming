#include <stdio.h>
 
             #define PI 3.14      /* define the value of PI as a constant */
 
             float square   (float number)
             { 
                      float square_value;
 
                      square_value = number * number;
 
                      return (square_value);
 
             }    
 
             float area_of_circle (float radius)
             {
 
                      float area;   /* area of a circle */
 
                      /* compute area of a circle: PI * radius squared */
                      area  = PI * square(radius);
 
                      return (area);
             }
 
             main ()
             {
 
                   float area;       /* the area of the circle */
                   float radius;    /* radius of a circle to be entered */
 
                   printf ("Enter the circle radius: ");
                   scanf ("%f", &radius);
 
                  /* Pass value1 to the square function, process it and return the */
                  /* the squared value into the answer local variable */
                  area = area_of_circle (radius);
 
                  printf ("The Area of a Circle with a radius of %5.2f is %10.2f \n", radius, area);
 
                 return (0);
 
             }
