#include "headers.h"
jmp_buf ct_buf;
char *global;
int dir_count = 0;
int latest_fg_pid = -1;
activity_node_ptr head_activity;
void ctrlc(int sig)
{
    if (latest_fg_pid != -1)
    {
        kill(latest_fg_pid, SIGINT);
        latest_fg_pid = -1;
    }
    printf("\n");
    longjmp(ct_buf, 1);
}

void ctrld(int sig)
{
    printf("\n");
    exit(0);
}
void ctrlz(int sig)
{
    if (head_activity == NULL || head_activity->next == NULL)
    {
        return;
    }
    activity_node_ptr iterator = head_activity;
    iterator = iterator->next;
    while (iterator != NULL)
    {
        if (iterator->back == 0)
        {
            kill(iterator->proid, SIGTSTP);
            kill(iterator->proid, SIGSTOP);
            iterator->back = 1;
        }
        iterator = iterator->next;
    }
    longjmp(ct_buf, 1);
    printf("\n");
}
int main()
{
    int o_st = dup(STDOUT_FILENO);
    signal(SIGINT, ctrlc);
    signal(SIGQUIT, ctrld);
    signal(SIGTSTP, ctrlz);
    queueptr q = init_queue();
    FILE *qpt = fopen("history.txt", "r");
    if (qpt != NULL)
    {
        char qinput[4097];
        while (fgets(qinput, 4097, qpt) != NULL)
        {
            int len = strlen(qinput);
            qinput[len] = '\0';
            enque(q, qinput, 0);
        }
        fclose(qpt);
    }
    char *username = (char *)calloc(4097, sizeof(char));
    char *systemname = (char *)calloc(4097, sizeof(char));
    char *homedir = (char *)calloc(4097, sizeof(char));
    char *prevdir = (char *)calloc(4097, sizeof(char));
    getlogin_r(username, 4097);
    gethostname(systemname, 4097);
    getcwd(homedir, 4097);
    getcwd(prevdir, 4097);
    nodeptr head = makenode(-5555, "invalid");
    int shell_id = getpid();
    head_activity = make_act(shell_id, "shell", 0);
    char *returned_value_from_token = (char *)calloc(4097, sizeof(char));
    sigsetjmp(ct_buf, 1);
    while (1)
    {
        dup2(o_st, STDOUT_FILENO);
        prompt(username, systemname, homedir, returned_value_from_token);
        char input[4097];
        if (fgets(input, 4097, stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n");
                exit(0);
            }
        }
        char in_c[4097];
        strcpy(in_c, input);
        enque(q, in_c, 1);
        returned_value_from_token = helpermain(in_c, username, systemname, homedir, prevdir, head, head_activity, q);
    }
}
