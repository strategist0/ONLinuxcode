#include <stdio.h>
#define NAME "Gustav"
#define SURNAME "Mahler"

int main(void)
{
    printf("%s %s\n",NAME, SURNAME);
    printf("%s\n%s\n",NAME, SURNAME);
    printf("%s ", NAME);
    printf("%s\n", SURNAME);
    return 0;
}