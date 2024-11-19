#include <stdio.h>
int inarray(const int sorted[],int size,int val);
#define SIZE 10
int main(void)
{
int nums[SIZE]={1,20,40,41,42,43,70,88,92,109};
int num;
int found;
printf("Enter an integer to search for:");
while(scanf("%d",&num)==1)
{
found=inarray(nums,SIZE,num);
printf("%d%sinthearray.\n",num,found?"is":"isn't");
printf("Nextvalue(qtoquit):");
}
printf("Bye.\n");
return 0;
}
int inarray(const int sorted[],int size,int val)
{
int min=0;
int max=size-1;
int mid;
int found=0;
while(min<max)
{
mid=(min+max)/2;
if(val<sorted[mid])
max=mid-1;
else if(val>sorted[mid])
min=mid+1;
else
{
found=1;
break;
}
}
if(sorted[min]==val)
found=1;
return found;
}