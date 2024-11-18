#include <stdio.h>

int main()
{
    char ch;
    int ct = 0;
    printf("Input chars (# for exist):");
    while((ch = getchar()) != '#'){
        if(ct++%8 == 0)
        printf("\n");
        if(ch == '\n')
        printf("'\\n'-%03d.", ch);
        else if(ch == 't')
        printf("'\\t'-%03d.", ch);
        else printf("'%c' - %03d.", ch, ch);
    }
    printf("done\n");
    return 0;
}