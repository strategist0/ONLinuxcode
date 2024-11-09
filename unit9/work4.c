#include <stdio.h>
double hm(double x, double y);
int main()
{
    double d1, d2;
    printf("Enter tow float number:");
    scanf("%lf %lf", &d1, &d2);
    printf("The HarMEAN of  %g and %g is %g", d1, d2, hm(d1, d2));
    return 0;
}

double hm(double x, double y)
{
    return 2/(1/x + 1/y);
}