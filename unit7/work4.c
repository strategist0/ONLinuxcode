#include <stdio.h>

int main()
{
    int ct = 0;
    char ch;
    printf("Enter chars(# for exit):");
    while((ch = getchar()) != '#'){
        switch(ch){
            case '!':
            printf("!!");
            ct++;
            break;
            case '.':
            printf("!");
            ct++;
            break;
            default:
            printf("%c", ch);
        }
    }
    printf("\nTotal replace %d times\n", ct);
    puts("done");
    return 0;
}