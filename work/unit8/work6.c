#include <stdio.h>

char gt(void);
int main()
{
    char ch;
    ch = gt();
    printf("%c\n", ch);
    return 0;
}

char gt(void)
{
    char ch;
    do{
        ch = getchar();
    }while(ch == ' '|| ch == '\n' || ch == '\t');
    return ch;
}