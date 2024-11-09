#include <stdio.h>

int main()
{
    float h;
    char name[40];
    printf("your name:");
    scanf("%s", name);
    printf("hi %s, how tall you are(inch):", name);
    scanf("%f",&h);
    printf("%s, you are %.3f feet tall \n", name, h/12.0);
    return 0;
}