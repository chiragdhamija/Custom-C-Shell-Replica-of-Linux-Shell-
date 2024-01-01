#include "headers.h"
void restore_output(int a_r, int o_r, int o)
{
    if (a_r == 1 || o_r == 1)
    {
        if (dup2(o, STDOUT_FILENO) == -1)
        {
            printf("\033[1;31mERROR :  Unable to restore output back to terminal\n\033[0;0m");
            return;
        }
    }
}
char *tokenize(char *username, char *systemname, char *homedir, char *input, char *prevdir, queueptr q, int bg_check, nodeptr head, activity_node_ptr head_activity)
{
    char *inp_enq = (char *)calloc(4097, sizeof(char));
    char *inp_act = (char *)calloc(4097, sizeof(char));
    strcpy(inp_enq, input);
    strcpy(inp_act, input);
    char *delimiter = " \t\n\0";
    char *token = strtok(input, delimiter);
    char **token_list = (char **)malloc(sizeof(char *) * 50);
    for (int i = 0; i < 50; i++)
    {
        token_list[i] = (char *)calloc(4097, sizeof(char));
    }
    int tok_count = 0;
    int peek_flag_count = 0;
    int peek_path_count = 0;
    int seek_flag_count = 0;
    int seek_path_target_count = 0;
    int in_redirect = 0;
    int out_redirect = 0;
    int app_redirect = 0;
    int redirect_flags;
    int original_stdout = dup(STDOUT_FILENO);
    int original_stdin = dup(STDIN_FILENO);
    char output_redirect_name[4097];
    char *nu = (char *)calloc(5, sizeof(char));
    strcpy(nu, "\0");
    while (token != NULL)
    {
        token_list[tok_count++] = token;
        token = strtok(NULL, delimiter);
    }
    for (int i = 0; i < tok_count; i++)
    {
        if (strcmp(token_list[i], ">") == 0)
        {
            out_redirect = 1;
            redirect_flags = O_WRONLY | O_CREAT | O_TRUNC;
            strcpy(output_redirect_name, token_list[i + 1]);
            strcpy(token_list[i], "");
            strcpy(token_list[i + 1], "");
            tok_count = tok_count - 2;
        }
        if (strcmp(token_list[i], ">>") == 0)
        {
            app_redirect = 1;
            redirect_flags = O_WRONLY | O_CREAT | O_APPEND;
            strcpy(output_redirect_name, token_list[i + 1]);
            strcpy(token_list[i], "");
            strcpy(token_list[i + 1], "");
            tok_count = tok_count - 2;
        }
        if (strcmp(token_list[i], "<") == 0)
        {
            in_redirect = 1;
            if (strcmp(token_list[0], "pastevents") == 0 || strcmp(token_list[0], "warp") == 0 || strcmp(token_list[0], "peek") == 0 || strcmp(token_list[0], "proclore") == 0 || strcmp(token_list[0], "seek") == 0 || strcmp(token_list[0], "exit") == 0 || strcmp(token_list[0], "iMan") == 0 || strcmp(token_list[0], "ping") == 0 || strcmp(token_list[0], "activities") == 0 || strcmp(token_list[0], "fg") == 0 || strcmp(token_list[0], "bg") == 0 || strcmp(token_list[0], "neonate") == 0)
            {
                FILE *input_file_opener = fopen(token_list[i + 1], "r");
                if (input_file_opener == NULL)
                {
                    perror("Error Opening file");
                }
                fseek(input_file_opener, 0, SEEK_END);
                long in_size = ftell(input_file_opener);
                rewind(input_file_opener);
                char buffer[in_size + 1];
                fread(buffer, 1, in_size, input_file_opener);
                buffer[in_size] = '\0';
                fclose(input_file_opener);
                char *inp_tok = strtok(buffer, delimiter);
                char **inp_redir_list = (char **)malloc(sizeof(char *) * 50);
                for (int j = 0; j < 50; j++)
                {
                    inp_redir_list[i] = (char *)calloc(4097, sizeof(char));
                }
                int inp_redir_Count = 0;
                while (inp_tok != NULL)
                {
                    inp_redir_list[inp_redir_Count++] = inp_tok;
                    inp_tok = strtok(NULL, delimiter);
                }
                strcpy(token_list[i], "\0");

                token_list[i] = (char *)calloc(4097, sizeof(char));
                token_list[i + 1] = (char *)calloc(4097, sizeof(char));

                strcpy(token_list[i + 1], "\0");
                tok_count += inp_redir_Count;
                for (int j = i + 2; j < tok_count; j++)
                {
                    token_list[j - 2 + inp_redir_Count] = token_list[j];
                }
                for (int j = i, k = 0; j <= inp_redir_Count; j++, k++)
                {
                    strcpy(token_list[j], inp_redir_list[k]);
                }
                tok_count = tok_count - 2;
            }
        }
    }
    int out_fd;
    if (out_redirect == 1 || app_redirect == 1)
    {
        out_fd = open(output_redirect_name, redirect_flags, 0644);
        if (out_fd == -1)
        {
            printf("\033[1;31mERROR : Unable to open file descriptor for Output redirection\033[0;0m");
            return nu;
        }
        if (dup2(out_fd, STDOUT_FILENO) == -1)
        {
            printf("\033[1;31mERROR : Unable to change Output Stream\033[0;0m");
            return nu;
        }
        close(out_fd);
    }
    if (strcmp(token_list[0], "warp") == 0)
    {
        warpkar(username, systemname, token_list, homedir, prevdir, tok_count);
    }
    else if (strcmp(token_list[0], "peek") == 0)
    {
        for (int i = 0; i < tok_count; i++)
        {
            if (strcmp(token_list[i], "-a") == 0 || strcmp(token_list[i], "-l") == 0 || strcmp(token_list[i], "-al") == 0 || strcmp(token_list[i], "-la") == 0)
            {
                peek_flag_count++;
            }
            if(token_list[i][0]=='-')
            {
                for(int h=1;h<strlen(token_list[i]);i++)
                {
                    if(token_list[i][h]!='a' && token_list[i][h]!='l')
                    {
                        restore_output(app_redirect,out_redirect,original_stdout);
                        {
                          printf("\033[1;31mINVALID FLAG\n\033[0;0m");   
                          return nu;
                        }
                    }
                }
            }
        }
        peek_path_count = tok_count - peek_flag_count - 1;
        peekkar(token_list, tok_count, peek_flag_count, peek_path_count, prevdir, homedir);
    }
    else if (strcmp(token_list[0], "proclore") == 0)
    {
        proclorekar(token_list, tok_count, homedir, bg_check);
    }
    else if (strcmp(token_list[0], "seek") == 0)
    {
        if (tok_count < 2)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            return nu;
        }
        for (int i = 0; i < tok_count; i++)
        {
            if (strcmp(token_list[i], "-d") == 0 || strcmp(token_list[i], "-f") == 0 || strcmp(token_list[i], "-e") == 0)
            {
                seek_flag_count++;
            }
        }
        seek_path_target_count = tok_count - seek_flag_count - 1;
        if (seek_flag_count == 2)
        {
            if ((strcmp(token_list[1], "-d") == 0 && strcmp(token_list[2], "-f") == 0) || (strcmp(token_list[1], "-f") == 0 && strcmp(token_list[2], "-d") == 0))
            {
                restore_output(app_redirect, out_redirect, original_stdout);
                printf("INVALID FLAGS\n");
                return nu;
            }
        }
        if (seek_path_target_count == 0)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            return nu;
        }
        char *targetdirectory = (char *)calloc(4097, sizeof(char));
        char *targetword = (char *)calloc(4097, sizeof(char));
        if (seek_path_target_count == 1)
        {
            getcwd(targetdirectory, 4097);
            strcpy(targetword, token_list[tok_count - 1]);
        }
        else
        {
            strcpy(targetdirectory, token_list[tok_count - 1]);
            strcpy(targetword, token_list[tok_count - 2]);
        }
        seekkar(targetdirectory, targetword, token_list, tok_count, seek_flag_count, seek_path_target_count);
    }

    else if (strcmp(token_list[0], "pastevents") == 0 && tok_count == 1)
    {
        printqueue(q);
    }

    else if (strcmp(token_list[0], "pastevents") == 0 && tok_count > 1 && strcmp(token_list[1], "purge") == 0)
    {
        del_q(q);
    }
    else if (strcmp(token_list[0], "pastevents") == 0 && tok_count > 1 && strcmp(token_list[1], "execute") == 0)
    {
        int command_from_last = 0;
        for (int i = 0; i < strlen(token_list[2]); i++)
        {
            command_from_last = command_from_last * 10 + (int)token_list[2][i] - 48;
        }
        int index_at_q_to_be_ex;
        char pe[] = "pastevents execute ";
        strcat(pe, token_list[2]);
        if (q->rear_ptr - command_from_last + 1 >= 0)
        {
            index_at_q_to_be_ex = q->rear_ptr - command_from_last + 1;
        }
        else
        {
            index_at_q_to_be_ex = (q->max_capacity + (q->rear_ptr - command_from_last + 1)) % q->max_capacity;
        }
        char *to_be_ex = (char *)calloc(4097, sizeof(char));
        char *gg = strdup(global);
        strcpy(to_be_ex, q->list_of_commands[index_at_q_to_be_ex]);
        gg = replaceSubstring(gg, pe, to_be_ex);
        strcat(gg, "\n");
        enque(q, gg, 1);
        char *r = helpermain(to_be_ex, username, systemname, homedir, prevdir, head, head_activity, q);
        free(to_be_ex);
    }
    else if (strcmp(token_list[0], "exit") == 0)
    {
        strcat(token_list[0], " ");
        chdir(homedir);
        restore_output(app_redirect, out_redirect, original_stdout);
        exit(1);
        return nu;
    }
    else if (strcmp(token_list[0], "iMan") == 0)
    {
        if (tok_count == 1)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mERROR : give a command for which you want to see the man page\n\033[0;0m");
            return nu;
        }
        iman(token_list, tok_count);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else if (strcmp(token_list[0], "ping") == 0)
    {
        if (tok_count != 3)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mERROR : Invalid set of Arguments\n\033[0;0m");
            return nu;
        }
        pingkar(token_list, tok_count);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else if (strcmp(token_list[0], "activities") == 0)
    {
        if (tok_count != 1)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mERROR : Invalid command\n\033[0;0");
            return nu;
        }
        activitykar(head_activity, homedir);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else if (strcmp(token_list[0], "fg") == 0)
    {
        if (tok_count != 2)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mINVALID ARGUMENTS : No process ID provided\n\033[0;0m");
            return nu;
        }
        fgkar(token_list, tok_count);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else if (strcmp(token_list[0], "bg") == 0)
    {
        if (tok_count != 2)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mINVALID ARGUMENTS : No process ID provided\n\033[0;0m");
            return nu;
        }
        bgkar(token_list, tok_count);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else if (strcmp(token_list[0], "neonate") == 0)
    {
        if (tok_count != 3)
        {
            restore_output(app_redirect, out_redirect, original_stdout);
            printf("\033[1;31mINVALID ARGUMENTS\n\033[0;0m");
            return nu;
        }
        neonatekar(token_list, tok_count, homedir);
        restore_output(app_redirect, out_redirect, original_stdout);
        return nu;
    }
    else
    {
        int in_pos = -1;
        char **lin_command = (char **)malloc(sizeof(char *) * (tok_count + 1));
        for (int i = 0; i < tok_count; i++)
        {
            lin_command[i] = (char *)calloc(4097, sizeof(char));
        }
        for (int i = 0; i < tok_count; i++)
        {
            if (in_redirect == 1 && strcmp(token_list[i], "<") == 0)
            {
                in_pos = i;
            }
            strcpy(lin_command[i], token_list[i]);
        }
        if (in_redirect == 1)
        {
            int inp_fil_des = open(lin_command[in_pos + 1], O_RDONLY);
            if (inp_fil_des == -1)
            {
                perror("error in inp_fil_des");
            }
            if (dup2(inp_fil_des, STDIN_FILENO) == -1)
            {
                perror("error in redirecting");
            }
            close(inp_fil_des);
            free(lin_command[in_pos]);
            free(lin_command[in_pos + 1]);
            tok_count = tok_count - 2;
        }
        lin_command[tok_count] = NULL;
        int status;
        int pid = fork();
        if (pid > 0)
        {
            activity_node_ptr daalo = make_act(pid, inp_act, bg_check);
            insert_activity(head_activity, daalo);
            latest_fg_pid = pid;
        }
        int final_t;
        struct timespec end_t;
        struct timespec start_t;
        if (bg_check == 0)
        {

            clock_gettime(CLOCK_MONOTONIC, &start_t);
            if (pid == 0)
            {
                int e = execvp(lin_command[0], lin_command);
                if (e == -1)
                {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
            else if (pid > 0)
            {
                wait(&status);

                if (out_redirect == 1 || app_redirect == 1)
                {

                    if (dup2(original_stdout, STDOUT_FILENO) == -1)
                    {
                        perror("dup2 error");
                    }
                }
                if (in_redirect == 1)
                {
                    if (dup2(original_stdin, STDIN_FILENO) == -1)
                    {
                        perror("error redirecting back to terminal");
                    }
                }
                clock_gettime(CLOCK_MONOTONIC, &end_t);
            }
            else
            {
                perror("fork");
            }
            double net_t = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_nsec - start_t.tv_nsec) / 1.0e9;
            int final_t = (int)net_t;
            if (final_t > 2)
            {
                char *ret = (char *)calloc(4097, sizeof(char));
                strcpy(ret, " ");
                strcat(ret, lin_command[0]);
                char n[5000];
                sprintf(n, " : %ds", final_t);
                strcat(ret, n);
                if (out_redirect == 1 || app_redirect == 1)
                {

                    if (dup2(original_stdout, STDOUT_FILENO) == -1)
                    {
                        perror("dup2 error");
                    }
                }
                if (in_redirect == 1)
                {
                    if (dup2(original_stdin, STDIN_FILENO) == -1)
                    {
                        perror("error redirecting back to terminal");
                    }
                }
                return ret;
            }
            else
            {
                if (out_redirect == 1 || app_redirect == 1)
                {

                    if (dup2(original_stdout, STDOUT_FILENO) == -1)
                    {
                        perror("dup2 error");
                    }
                }
                if (in_redirect == 1)
                {
                    if (dup2(original_stdin, STDIN_FILENO) == -1)
                    {
                        perror("error redirecting back to terminal");
                    }
                }
                return nu;
            }
        }
        else
        {
            if (pid == 0)
            {
                execvp(lin_command[0], lin_command);
                perror("execvp");
            }
            else if (pid > 0)
            {
                printf("%d\n", pid);
                nodeptr t = makenode(pid, lin_command[0]);
                insertinll(head, t);
            }
            if (out_redirect == 1 || app_redirect == 1)
            {

                if (dup2(original_stdout, STDOUT_FILENO) == -1)
                {
                    perror("dup2 error");
                }
            }
            if (in_redirect == 1)
            {
                if (dup2(original_stdin, STDIN_FILENO) == -1)
                {
                    perror("error redirecting back to terminal");
                }
            }
            return nu;
        }
    }
    restore_output(app_redirect, out_redirect, original_stdout);
    if (in_redirect == 1)
    {
        if (dup2(original_stdin, STDIN_FILENO) == -1)
        {
            perror("error redirecting back to terminal");
        }
    }
    return nu;
}