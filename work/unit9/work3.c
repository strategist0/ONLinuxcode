#include <stdio.h>

void pc(char ch, int cols, int rows);
int main()
{
    char c;
    int x, y;
    printf("Enter the char:");
    scanf("%c", &c);
    printf("Enter the rows and cols:");
    scanf("%d %d", &x, &y);
    pc(c, x, y);
    return 0;
}

void pc(char ch, int cols, int rows)
{
    for(int m = 0;m < rows; m++){
        for(int n = 0;n < cols;n++)
            printf("%c", ch);
        printf("\n");
    }
}