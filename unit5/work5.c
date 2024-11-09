#include <stdio.h>

int main()
{
    int c = 0, sum = 0;
    printf("Enter the number of days you work:");
    scanf("%d", &c);
    while(c > 0){
        sum = sum + c--;
    }
    printf("Earned %d total!\n", sum);
    puts("done");
    return 0;
}