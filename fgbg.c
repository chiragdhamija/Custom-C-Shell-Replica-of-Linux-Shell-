#include "headers.h"

void fgkar(char **token_list, int tok_count)
{
    int pid = 0;
    for (int i = 0; i < strlen(token_list[1]); i++)
    {
        pid = pid * 10 + ((int)token_list[1][i] - 48);
    }
    if (kill(pid, SIGCONT) == -1)
    {
        printf("\033[1;31m");
        perror("kill");
        printf("\033[0;0m");
    }

    if (waitpid(pid, NULL, WUNTRACED) == -1)
    {   
        printf("\033[1;31m");
        perror("waitpid");
        printf("\033[0;0m");
    }
}
void bgkar(char **token_list, int tok_count)
{
    int pid = 0;

    for (int i = 0; i < strlen(token_list[1]); i++)
    {
        pid = pid * 10 + ((int)token_list[1][i] - 48);
    }
     if (kill(pid, SIGCONT) == -1)
    {   
        printf("\033[1;31m");
        perror("kill");
        printf("\033[0;0m");
    }
}
