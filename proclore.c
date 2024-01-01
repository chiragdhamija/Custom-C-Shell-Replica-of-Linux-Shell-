#include "headers.h"
int st_to_number(char * st)
{
    int n=0;
    for(int i=0;i<strlen(st);i++)
    {
        n=n*10 + ((int)st[i]-48);
    }
    return n;
}
void proclorekar(char **token_list, int tok_count,char *homedir,int bg_check)
{   
    int pgrp;
    int tpgid;
    int giv_arg = -11111;
    int pid;
    int vm_size;
    char status;
    char fg_bg;
    if (tok_count == 2)
    {
        giv_arg = 0;
        for (int i = 0; i < strlen(token_list[1]); i++)
        {
            giv_arg = giv_arg * 10 + ((int)token_list[1][i] - 48);
        }
    }
    if (giv_arg != -11111)
    {
        pid = giv_arg;
    }
    else
    {
        pid = getpid();
    }
    char executable_path_dir[4097];
    snprintf(executable_path_dir,sizeof(executable_path_dir),"/proc/%d/exe",pid);
    char *executable_path=(char *)calloc(4097,sizeof(char));
    char *final_exe;
    ssize_t n_bytes=readlink(executable_path_dir,executable_path,4097-1);
    if(n_bytes==1)
    {           
        printf("\033[1;31mERROR : Process ID does not exist\n\033[0;0m");
        return;
    }
    else
    {
        final_exe=findfinalpath(homedir,executable_path);
    }
    char stat_path[4097];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    FILE *fid = fopen(stat_path, "r");
    if (fid == NULL)
    {
        printf("\033[1;31mERROR : Unable to open /proc/pid/stat file\n\033[0;0m");
        return;
    }
    char *stat_file=(char *)calloc(5000,sizeof(char));
    while (fgets(stat_file, 5000, fid))
    {

        char list[52][30];
        int to_count=0;
        char *delimiter = " :\t\n\0";
        char *token = strtok(stat_file, delimiter);
        while (token != NULL)
        {
            strcpy(list[to_count++],token);
            token = strtok(NULL, delimiter);
        }
        status=list[2][0];
        vm_size=st_to_number(list[22]);
        pgrp=st_to_number(list[4]);
        tpgid=st_to_number(list[7]);
    }
    fclose(fid);
    if(pgrp==tpgid)
    {
        fg_bg='+';
    }
    else if(bg_check==1)
    {
        fg_bg=' ';
    }   

    printf("pid : %d\n",pid);
    printf("process status : %c%c\n",status,fg_bg);
    printf("Process group : %d\n",pgrp);
    printf("Virtual Memory : %d KB\n",vm_size/1024);
    printf("Executable path : %s\n",final_exe);
    free(executable_path);
    free(stat_file);

}