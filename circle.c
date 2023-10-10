/* A program to figure out the three defining aspects of a Circle */

#include <stdio.h>

/* Constants */
#define PI 3.1416

/* Function Prototypes */
float circleCircumference (float Diameter);
float circleRadius (float Circumference);
float circleDiameter (float Circumference);

int main ( )
{

    float circumference;  /* circumference of a circle */
    float diameter;          /* diameter of a circle */
    float radius;              /* radius of a circle */

    printf ("Enter the Circumference in Centimeters: ");
    scanf ("%f", &circumference);

    /* calculate the diameter and radius based on the circumference */
    diameter = circleDiameter (circumference);
    radius = circleRadius (circumference);

    printf ("\nThe Diameter of our Circle is: %5.1f \n", diameter);
    printf ("\nThe Radius of our Circle is %5.1f \n", radius);

    printf ("The Circumference given the Diameter %5.1f is %5.1f \n",
                diameter, circleCircumference (diameter));

    return (0);

} /* main */

// ***********************************************************************
// Function:  circleCircumference
//
// Description:  Calculates the Circumference of a Circle
//                      given the Diameter of a Circle
//
// Parameters:  Diameter - The Diameter of the Circle
//
// Returns:  Circumference - The Circumference of a Circle
// ***********************************************************************
float circleCircumference (float Diameter)
{
    return (PI * Diameter);
}

// ***********************************************************************
// Function:  circleRadius
//
// Description:  Calculates the Radius of a Circle
//                      given the Circumference of a Circle
//
// Parameters:  Circumference - The Circumference of the Circle
//
// Returns:  Radius - The Radius of a Circle
// ***********************************************************************
float circleRadius (float Circumference)
{
    return (Circumference / (2 * PI));
}

// ***********************************************************************
// Function:  circleDiameter
//
// Description:  Calculates the Diameter of a Circle
//                      given the Circumference of a Circle
//
// Parameters:  Circumference - The Circumference of the Circle
//
// Returns:  Diameter - The Diameter of a Circle
// ***********************************************************************
float circleDiameter (float Circumference)
{
    return (Circumference / PI);
}
