#include <stdio.h>
#define fc 30.48
#define ic 2.54

int main()
{
    int ft;
    float in, cm;
    printf("Enter cm:");
    scanf("%f", &cm);
    while(cm > 0){
        ft =cm/fc;
        in = (cm -ft * fc)/ic;
        printf("%.1f cm = %d feet, %.1f inches\n", cm, ft, in);
        printf("Enter cm:");
        scanf("%f", &cm);
    }
    printf("Done\n");
    return 0;
}