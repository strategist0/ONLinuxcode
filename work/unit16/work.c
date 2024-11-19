#include <stdio.h>
#define LEN 100

int main()
{
    int cm,m;
    scanf("%d", &m);
    cm = m*LEN;
    printf("%d m = %d cm", m, cm);
    return 0;
}