#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 4096
#define SLEN 81
void append(FILE *source,FILE *dest);
intmain(int argc,char *argv[])
{
FILE *fa,*fs;
int files=0;
int fct;
if(argc<3)
{
printf("Usage:%s appendfile sourcefile[s]\n",argv[0]);
exit(EXIT_FAILURE);
}
if((fa=fopen(argv[1],"a"))==NULL)
{
fprintf(stderr,"Can't open %s\n",argv[1]);
exit(EXIT_FAILURE);
}
if(setvbuf(fa,NULL,_IOFBF,BUFSIZE)!=0)
{
fputs("Can't create out put buffer\n",stderr);
exit(EXIT_FAILURE);
}
for(fct=2;fct<argc;fct++)
{
if(strcmp(argv[fct],argv[1])==0)
fputs("Can't appendfile to itself\n",stderr);
elseif((fs=fopen(argv[fct],"r"))==NULL)
fprintf(stderr,"Can'topen%s\n",argv[fct]);
else
{
if(setvbuf(fs,NULL,_IOFBF,BUFSIZE)!=0)
{
fputs("Can'tcreateoutputbuffer\n",stderr);
continue;
}
append(fs,fa);
if(ferror(fs)!=0)
fprintf(stderr,"Errorinreadingfile%s.\n",
argv[fct]);
if(ferror(fa)!=0)
fprintf(stderr,"Errorinwritingfile%s.\n",
argv[1]);
fclose(fs);
files++;
printf("File%sappended.\n",argv[fct]);
}
}
printf("Done.%dfilesappended.\n",files);
fclose(fa);
return 0;
}
void append(FILE *source,FILE *dest)
{
size_tbytes;
static char temp[BUFSIZE];
while((bytes=fread(temp,sizeof(char),BUFSIZE,source))>0)
fwrite(temp,sizeof(char),bytes,dest);
}