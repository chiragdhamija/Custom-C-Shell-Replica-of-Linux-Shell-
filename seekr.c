#include "headers.h"
void printrelativepath(char *orig_target, char *ans)
{
    printf(".");
    for (int i = strlen(orig_target); i < strlen(ans); i++)
    {
        printf("%c", ans[i]);
    }
    printf("\n");
}
int check(char *input , char *targetword)
{
    char *temp=(char *)calloc(4097,sizeof(char));
    strcpy(temp,input);
    for(int i=0;i<strlen(temp);i++)
    {
        if(temp[i]=='.')
        {
            temp[i]='\0';
            break;
        }
    }
    int comp=strcmp(temp,targetword);
    free(temp);
    return comp;
}
void recursion(char *orig_target, char *targetdir, char *targetword, int d, int e, int f,int *count,char *e_ans)
{
    struct dirent **listofdir;
    int scan;
    scan = scandir(targetdir, &listofdir, NULL, alphasort);
    if (scan == -1)
    {
        printf("\033[1;31mERROR : Unable to get the contents of the directory\n\033[0;0m");
        return;
    }
    for (int i = 0; i < scan; i++)
    {   
        if(strcmp(listofdir[i]->d_name,"..")==0 || strcmp(listofdir[i]->d_name,".")==0)
        {
            continue;
        }
        char full_path[4097];
        snprintf(full_path, sizeof(full_path), "%s/%s", targetdir, listofdir[i]->d_name);
        struct stat file_details;
        if (stat(full_path, &file_details) == -1)
        {
            printf("\033[1;31mERROR : Unable to get the details of a File\n\033[0;0m");
            free(listofdir[i]);
            continue;
        }
        int rm_dot=check(listofdir[i]->d_name,targetword);

        if (strcmp(listofdir[i]->d_name, targetword) == 0 || !rm_dot)            
        {   
            if (d == 1 && S_ISDIR(file_details.st_mode))
            {   
                *count=*count+1;
                strcpy(e_ans,full_path);
                printf("\033[0;34m");
                printrelativepath(orig_target, full_path);
                printf("\033[0;0m");

            }
            if (f == 1 && !S_ISDIR(file_details.st_mode) )
            {   
                *count=*count+1;
                strcpy(e_ans,full_path);
                printf("\033[0;32m");
                printrelativepath(orig_target, full_path);
                printf("\033[0;0m");
            }
            if(f==0 && d==0)
            {   
                *count=*count+1;
                strcpy(e_ans,full_path);
                if(S_ISDIR(file_details.st_mode))
                {
                    printf("\033[0;34m");
                }
                else
                {
                    printf("\033[0;32m");
                }
                printrelativepath(orig_target,full_path);
                printf("\033[0;0m");
            }
            
        }
        if (S_ISDIR(file_details.st_mode))
        {
            recursion(orig_target,full_path, targetword, d, e, f,count,e_ans);
        }
    }
}