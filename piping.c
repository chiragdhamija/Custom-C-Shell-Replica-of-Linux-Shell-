#include "headers.h"

char *pipefunc(char *username, char *systemname, char *homedir, char *input, char *prevdir, queueptr q, int bg_check, nodeptr head,activity_node_ptr head_activity)
{
    char *return_from_tokenize = (char *)calloc(4097, sizeof(char));
    int pipe_count = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '|')
        {
            pipe_count++;
        }
    }

    char pipe_list[pipe_count+1][4097];

    int tok_count = 0;
    char *pipe_token = strtok(input, "|");

    while (pipe_token != NULL)
    {
        strcpy(pipe_list[tok_count++], pipe_token);
        pipe_token = strtok(NULL, "|");
    }
    char *nullstri = (char *)calloc(5, sizeof(char));
    strcpy(nullstri, "\0");
    int original_output = dup(STDOUT_FILENO);
    int original_input = dup(STDIN_FILENO);
    int current_pipe[2];
    int previous_pipe[2];

    for (int i = 0; i < pipe_count; i++)
    {
        if (pipe(current_pipe) == -1)
        {
            printf("\033[1;31mError in creating pipe\n\033[0;0m");
            return nullstri;
        }

        pid_t pid;

        if ((pid = fork()) == -1)
        {
            printf("\033[1;31mUnable to create a child process\n\033[0;0m");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {                   
            close(current_pipe[0]); 

            
            if (i > 0)
            {
                if (dup2(previous_pipe[0], STDIN_FILENO) == -1)
                {
                    printf("\033[1;31mError in redirecting input\n\033[0;0m");
                    exit(EXIT_FAILURE);
                }
                close(previous_pipe[0]);
            }

            if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
            {
                printf("\033[1;31mError in redirecting output\n\033[0;0m");
                exit(EXIT_FAILURE);
            }

            return_from_tokenize = tokenize(username, systemname, homedir, pipe_list[i], prevdir, q, bg_check, head,head_activity);
            exit(EXIT_SUCCESS); 
        }
        else
        {                           
            wait(NULL);
            close(current_pipe[1]); 
            if (i > 0)
            {
                close(previous_pipe[0]); 
            }

            previous_pipe[0] = current_pipe[0];
            previous_pipe[1] = current_pipe[1];

        }
    }


    if (dup2(original_output, STDOUT_FILENO) == -1)
    {
        printf("\033[1;31mError in redirecting output\n\033[0;0m");
        return nullstri;
    }

    if (dup2(previous_pipe[0], STDIN_FILENO) == -1)
    {
        printf("\033[1;31mError in redirecting input\n\033[0;0m");
        return nullstri;
    }
    close(previous_pipe[0]);
    return_from_tokenize=tokenize(username, systemname, homedir, pipe_list[pipe_count], prevdir, q, bg_check, head,head_activity);

    if (dup2(original_input, STDIN_FILENO) == -1)
    {
        printf("\033[1;31mError in redirecting input\n\033[0;0m");
        return nullstri;
    }

    return return_from_tokenize;
}
