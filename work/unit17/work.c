#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 45
struct film{
char title[TSIZE];
int rating;
struct film *next;
};
char*s_gets(char *st,int n);
void show_rec(const struct film *pf);
int main(void)
{
struct film *head=NULL;
struct film *prev,*current;
char input[TSIZE];
puts("Enter first movie title:");
while(s_gets(input,TSIZE)!=NULL&&input[0]!='\0')
{
current=(struct film*)malloc(sizeof(struct film));
if(head==NULL)
head=current;
else
prev->next=current;
current->next=NULL;
strcpy(current->title,input);
puts("Enter your rating<0-10>:");
scanf("%d",&current->rating);
while(getchar()!='\n')
continue;
puts("Enter next movie title(emptylinetostop):");
prev=current;
}
if(head==NULL)
printf("Nodataentered.");
else
printf("Hereisthemovielist:\n");
current=head;
while(current!=NULL)
{
printf("Movie:%sRating:%d\n",current->title,current->rating);
current=current->next;
}
if(head!=NULL)
{
printf("\nHere is the list in reverse order:\n");
show_rec(head);
}
printf("Bye!\n");
return 0;
}
char *s_gets(char*st,intn)
{
char *ret_val;
char *find;
ret_val=fgets(st,n,stdin);
if(ret_val)
{
find=strchr(st,'\n');
if(find)
*find='\0';
else
while(getchar()!='\n')
continue;
}
returnret_val;
}
void show_rec(const struct film *pf)
{
if(pf->next!=NULL)
show_rec(pf->next);
printf("Movie:%sRating:%d\n",pf->title,pf->rating);
}