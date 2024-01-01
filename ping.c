#include "headers.h"
void pingkar(char **token_list, int tok_count)
{   

    int pid = atoi(token_list[1]);
    int sign = atoi(token_list[2]);
    if (kill(pid, 0) == 0)
    {
        if (kill(pid, sign) == 0)
        {
            printf("Sent signal %d to process with pid %d\n", sign, pid);
        }
        else
        {   
            printf("\033[1;31m");
            perror("Kill");
            printf("\033[0;0m");
        }
    }
    else
    {
        printf("\033[1;31mNo such process exists\033[0;0m");
    }
}