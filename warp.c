#include "headers.h"
void warpkar(char *username, char *systemname, char **warp_input, char *homedir, char *prevdir, int num_tokens)
{
    if (num_tokens == 1)
    {
        chdir(homedir);
        char *cur = (char *)calloc(4097, sizeof(char));
        getcwd(cur, 4097);
        printf("%s\n", cur);
        free(cur);
    }
    if (strcmp(warp_input[1], "-") == 0)
    {
        if (dir_count == 0)
        {
            printf("OLPWD not set\n");
        }
        else
        {
            char *temp_2 = (char *)calloc(4097, sizeof(char));
            getcwd(temp_2, 4097);
            chdir(prevdir);
            strcpy(prevdir, temp_2);
            free(temp_2);
            char *cur = (char *)calloc(4097, sizeof(char));
            getcwd(cur, 4097);
            printf("%s\n", cur);
            free(cur);
        }
    }
    else
    {
        char *temp = (char *)calloc(4097, sizeof(char));
        getcwd(temp, 4097);
        strcpy(prevdir, temp);
        free(temp);
        if (strncmp(warp_input[1], "~/", 2) == 0)
        {
            dir_count++;

            chdir(homedir);
            char *rest = (char *)calloc(4097, sizeof(char));
            int j = 0;
            for (int i = 2; i < strlen(warp_input[1]); i++)
            {
                rest[j++] = warp_input[1][i];
            }
            if (chdir(rest) != 0)
            {
                printf("\033[1;31mDirectory does not exists\n\033[0;0m");
            }
            free(rest);
            char *cur = (char *)calloc(4097, sizeof(char));
            getcwd(cur, 4097);
            printf("%s\n", cur);
            free(cur);
        }
        else if (strcmp(warp_input[1], "~") == 0)
        {
            dir_count++;
            chdir(homedir);
            char *cur = (char *)calloc(4097, sizeof(char));
            getcwd(cur, 4097);
            printf("%s\n", cur);
            free(cur);
        }
        else
        {
            int l = 1;
            while (l < num_tokens)
            {
                if (strcmp(warp_input[l], "~") == 0)
                {
                    dir_count++;
                    chdir(homedir);
                    char *cur = (char *)calloc(4097, sizeof(char));
                    getcwd(cur, 4097);
                    printf("%s\n", cur);
                    free(cur);
                    l++;
                }
                else if (warp_input[l][0] == '~' && warp_input[l][1] == '/')
                {
                    dir_count++;

                    chdir(homedir);
                    char *rest = (char *)calloc(4097, sizeof(char));
                    int j = 0;
                    for (int i = 2; i < strlen(warp_input[l]); i++)
                    {
                        rest[j++] = warp_input[l][i];
                    }
                    if (chdir(rest) != 0)
                    {
                        printf("\033[1;31mDirectory does not exists\n\033[0;0m");
                    }
                    free(rest);
                    char *cur = (char *)calloc(4097, sizeof(char));
                    getcwd(cur, 4097);
                    printf("%s\n", cur);
                    free(cur);
                    l++;
                }
                else
                {

                    dir_count++;
                    if (chdir(warp_input[l]) != 0)
                    {
                        printf("\033[1;31mDirectory does not exists\n\033[0;0m");
                    }
                    char *cur = (char *)calloc(4097, sizeof(char));
                    getcwd(cur, 4097);
                    printf("%s\n", cur);
                    free(cur);
                    l++;
                }
            }
        }
    }
}