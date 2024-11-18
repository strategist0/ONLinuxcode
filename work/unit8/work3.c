#include <stdio.h>
#include <ctype.h>

int main()
{
    int lc = 0;
    int uc = 0;
    char ch;
    while((ch=getchar()) != EOF){
        if(ch >= 'A' && ch <= 'Z')
        uc++;
        if(ch >= 'a' && ch <= 'z')
        lc++;
    }
    printf("There are %d uppercase, and %d lowercase in that file!\n", uc, lc);
    return 0;
}