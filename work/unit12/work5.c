#include <stdio.h>
#include <stdlib.h>
void print(const int array[],int limit);
void sort(int array[],int limit);
#define SIZE 100
int main(void)
{
int i;
int arr[SIZE];
for(i=0;i<SIZE;i++)
arr[i]=rand()%10+1;
puts("initialarray");
print(arr,SIZE);
sort(arr,SIZE);
puts("\nsortedarray");
print(arr,SIZE);
return 0;
}
void sort(int array[],int limit)
{
int top,search,temp;
for(top=0;top<limit-1;top++)
for(search=top+1;search<limit;search++)
if(array[search]>array[top])
{
temp=array[search];
array[search]=array[top];
array[top]=temp;
}
}
void print(const int array[],int limit)
{
int index;
for(index=0;index<limit;index++)
{
printf("%2d",array[index]);
if(index%10==9)
putchar('\n');
}
if(index%10!=0)
putchar('\n');
}