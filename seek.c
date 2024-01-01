#include "headers.h"
void seekkar(char *targetdirectory,char *targetword,char ** token_list,int tok_count,int flag_count,int rest_count)
{   
    int d_flag=0;
    int f_flag=0;
    int e_flag=0;
    for(int i=1;i<=flag_count;i++)
    {   
        if(strlen(token_list[i])==1)
        {
        if(strcmp(token_list[i],"-d")==0)
        {
            d_flag=1;
        }
        if(strcmp(token_list[i],"-f")==0)
        {
            f_flag=1;
        }
        if(strcmp(token_list[i],"-e")==0)
        {
            e_flag=1;
        }
        }
        else
        {
            for(int j=1;j<strlen(token_list[i]);j++)
            {
                if(token_list[i][j]=='d')
                {
                    d_flag=1;
                }
                if(token_list[i][j]=='e')
                {
                    e_flag=1;
                }
                if(token_list[i][j]=='f')
                {
                    f_flag=1;
                }
            }
        }        
    }
    int count=0;
    char e_ans[4097];
    recursion(targetdirectory,targetdirectory,targetword,d_flag,e_flag,f_flag,&count,e_ans);
    if(e_flag==1 && count==1)
    {
        struct stat fd;
        if(stat(e_ans,&fd)==-1)
        {
            printf("\033[1;31mStat Error : Unable to get file details\n\033[0;0m");
            return ;
        }
        if(S_ISDIR(fd.st_mode))
        {
            chdir(e_ans);
        }
        else
        {
            FILE *file_ptr=fopen(e_ans,"r");
            if(file_ptr==NULL)
            {
                printf("\033[1;31mERROR : Unable to open the outputted file\n\033[0;0m");
                return ;
            }
            char c;
            while((c=getc(file_ptr))!=EOF)
            {
                printf("%c",c);
            }
            printf("\n");
            fclose(file_ptr);        
        }


    }

}