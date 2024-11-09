#include <stdio.h>
int main()
{
    float a;
    printf("Enter a float number;");
    scanf("%f", &a);
    printf("the input is %.1f or %.1e \n", a, a);
    return 0;
}