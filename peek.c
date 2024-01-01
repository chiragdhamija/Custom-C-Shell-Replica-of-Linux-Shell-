#include "headers.h"
void peekkar(char **token_list, int num_tokens, int flag_tokens, int path_tokents, char *prevdir, char *homedir)
{
    int l_flag = 0;
    int a_flag = 0;
    char *curr = (char *)calloc(4097, sizeof(char));
    getcwd(curr, 4097);
    for (int i = 1; i <= flag_tokens; i++)
    {
        if (strcmp(token_list[i], "-a") == 0 || strcmp(token_list[i], "-al") == 0 || strcmp(token_list[i], "-la") == 0)
        {
            a_flag = 1;
        }
        if (strcmp(token_list[i], "-l") == 0 || strcmp(token_list[i], "-al") == 0 || strcmp(token_list[i], "-la") == 0)
        {
            l_flag = 1;
        }
    }
    struct dirent **listofdir;
    int scan;
    int i = 0;
    char *targetdir = (char *)calloc(4097, sizeof(char));
    for (int i = 1 + flag_tokens; i < num_tokens; i++)
    {
        if (strcmp(token_list[i], "~") == 0)
        {
            strcat(targetdir, homedir);
        }
        else if (token_list[i][0] == '~' && token_list[i][1] == '/')
        {
            strcat(targetdir, homedir);
            char *rest = (char *)calloc(4097, sizeof(char));
            int k = 0;
            for (int j = 1; j < strlen(token_list[i]); j++)
            {
                rest[k++] = token_list[i][j];
            }
            strcat(targetdir, rest);
            free(rest);
        }
        else if (path_tokents == 1)
        {
            strcpy(targetdir, token_list[i]);
        }
    }
    if (path_tokents == 0)
    {
        strcpy(targetdir, curr);
    }
    scan = scandir(targetdir, &listofdir, NULL, alphasort);
    if (scan == -1)
    {   printf("\033[0;34m");
        perror("scandir");
        printf("\033[0;0m");
        return;
    }
    if (l_flag == 1)
    {
        for (int i = 0; i < scan; i++)
        {
            if (!a_flag && listofdir[i]->d_name[0] == '.')
            {
                free(listofdir[i]);
                continue;
            }
            char full_path[4097];
            snprintf(full_path, sizeof(full_path), "%s/%s", targetdir, listofdir[i]->d_name);
            struct stat file_details;
            if (stat(full_path, &file_details) == -1)
            {
                printf("\033[1;31mStat Error : Unable to get file details\n\033[0;0m");
                free(listofdir[i]);
                continue;
            }
            // 1. iS DIRECTORY
            if (S_ISDIR(file_details.st_mode))
            {
                printf("%s ", "d");
            }
            else
            {
                printf("%s ", "-");
            }

            // 2. PERMISSIONS
            if (file_details.st_mode & S_IRUSR)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IRGRP)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IROTH)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }

            if (file_details.st_mode & S_IXOTH)
            {
                printf("x ");
            }
            else
            {
                printf("- ");
            }
            printf("\t");
            // HARD LINKS
            printf("%ld ", (long)file_details.st_nlink);
            printf("\t");

            struct passwd *uname = getpwuid(file_details.st_uid);
            struct group *gname = getgrgid(file_details.st_gid);
            // username and groupname
            if (uname)
            {
                printf("%s\t", uname->pw_name);
            }
            else
            {
                printf("unknown\t");
            }
            if (gname)
            {
                printf("%s\t", gname->gr_name);
            }
            else
            {
                printf("unknown\t");
            }

            // size
            printf("%lld\t", (long long)file_details.st_size);

            char *mod_time = ctime(&file_details.st_mtime);
            mod_time[strlen(mod_time) - 1] = '\0';
            printf("%s\t", mod_time);
            if (S_ISDIR(file_details.st_mode))
            {
                printf("\033[0;34m%s\033[0;0m\n", listofdir[i]->d_name);
            }
            else if (file_details.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\033[0;0m\n", listofdir[i]->d_name);
            }
            else
            {
                printf("%s\n", listofdir[i]->d_name);
            }
            free(listofdir[i]);
        }
    }
    else if (l_flag == 0)
    {
        for (int i = 0; i < scan; i++)
        {
            if (!a_flag && listofdir[i]->d_name[0] == '.')
            {
                free(listofdir[i]);
                continue;
            }
            char full_path[4097];
            snprintf(full_path, sizeof(full_path), "%s/%s", targetdir, listofdir[i]->d_name);
            struct stat file_details;
            if (stat(full_path, &file_details) == -1)
            {
                printf("\033[1;31mStat Error : Unable to get file details\n\033[0;0m");
                free(listofdir[i]);
                continue;
            }
            if (S_ISDIR(file_details.st_mode))
            {
                printf("\033[0;34m%s\033[0;0m\n", listofdir[i]->d_name);
            }
            else if (file_details.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\033[0;0m\n", listofdir[i]->d_name);
            }
            else 
            {   
                printf("%s\n", listofdir[i]->d_name);
            }
            free(listofdir[i]);
        }
    }
    free(listofdir);
    free(curr);
    free(targetdir);
}