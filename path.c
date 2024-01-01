#include "headers.h"

char* findfinalpath(char *homedir, char *currdir)
{

    char *final=(char *)calloc(4097,sizeof(char));
    if(strcmp(currdir,homedir)==0)
    {
        final[0]='~';
        final[1]='\0';
    }
    else if(strlen(currdir)<strlen(homedir))
    {
        strcpy(final,currdir);
    }
    else
    {
        char *temp=(char *)malloc(sizeof(char)*strlen(currdir));
        strcpy(temp,currdir);
        temp[strlen(homedir)]='\0';
        int j=1;
        final[0]='~';
        
        for(long int i=strlen(homedir);i<strlen(currdir);i++)
        {
            final[j++]=currdir[i];
        }
        free(temp);
    }
    return final;
}