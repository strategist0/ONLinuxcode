#include <stdio.h>
void critic(int*u);
int main(void)
{
int units;
printf("Howmanypoundstoafirkinofbutter?\n");
scanf("%d",&units);
while(units!=56)
critic(&units);
printf("Youmusthavelookeditup!\n");
return 0;
}
void critic(int *u)
{
printf("Noluck,myfriend.Tryagain.\n");
scanf("%d",u);
}