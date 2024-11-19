#include <stdio.h>
#define LEN 10
intmax_arr(constintar[],intn);
void show_arr(constintar[],intn);
int main(void)
{
int orig[LEN]={1,2,3,4,12,6,7,8,9,10};
int max;
show_arr(orig,LEN);
max=max_arr(orig,LEN);
printf("%d=largestvalue\n",max);
return0;
}
intmax_arr(constintar[],intn)
{
inti;
intmax=ar[0];
/*don'tuse0asinitialmaxvalue--failsifallarrayvaluesareneg*/
for(i=1;i<n;i++)
if(max<ar[i])
max=ar[i];
returnmax;
}
voidshow_arr(constintar[],intn)
{
inti;
for(i=0;i<n;i++)
printf("%d",ar[i]);
putchar('\n');
}