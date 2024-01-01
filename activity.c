#include "headers.h"
void printact(activity_node_ptr head)
{
    activity_node_ptr temp = head;
    temp = temp->next;
    while (temp != NULL)
    {
        printf("%d %s\n", temp->proid, temp->name);
        temp = temp->next;
    }
}
activity_node_ptr make_act(int pid, char *input, int bg)
{
    activity_node_ptr t = (activity_node_ptr)malloc(sizeof(activity_node));
    t->proid = pid;
    t->name = (char *)calloc(300, sizeof(char));
    strcpy(t->name, input);
    t->name[strlen(t->name)] = '\0';
    t->next = NULL;
    t->back = bg;
    return t;
}
void insert_activity(activity_node_ptr head, activity_node_ptr ins)
{
    if (head->next == NULL)
    {
        head->next = ins;
    }
    else
    {
        int pi = ins->proid;
        if (head->next->next == NULL)
        {
            if (head->next->proid > pi)
            {
                ins->next = head->next;
                head->next = ins;
            }
            else
            {
                head->next->next = ins;
            }
        }
        else
        {
            activity_node_ptr temp = head->next;
            activity_node_ptr prev = head->next;
            while (temp != NULL && pi > temp->proid)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = ins;
            ins->next = temp;
        }
    }
}

void activitykar(activity_node_ptr head, char *homedir)
{
    activity_node_ptr temp = head;
    activity_node_ptr prev = head;
    temp = temp->next;
    if (temp == NULL)
    {
        return;
    }
    while (temp != NULL)
    {
        int status;
        int pid_end_check = waitpid(temp->proid, &status, WNOHANG);

        if (pid_end_check == 0)
        {
            char st_symbol;
            char status[10];
            char executable_path_dir[4097];
            snprintf(executable_path_dir, sizeof(executable_path_dir), "/proc/%d/exe", temp->proid);
            char *executable_path = (char *)calloc(4097, sizeof(char));
            char *final_exe;
            ssize_t n_bytes = readlink(executable_path_dir, executable_path, 4097 - 1);
            if (n_bytes == 1)
            {
                printf("error\n");
            }
            else
            {
                final_exe = findfinalpath(homedir, executable_path);
            }
            char stat_path[4097];
            snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", temp->proid);
            FILE *fid = fopen(stat_path, "r");
            if (fid == NULL)
            {
                printf("error opening file\n");
            }
            char stat_file[5000];
            while (fgets(stat_file, 5000, fid))
            {
                char list[52][30];
                int to_count = 0;
                char *delimiter = " :\t\n\0";
                char *token = strtok(stat_file, delimiter);
                while (token != NULL)
                {
                    strcpy(list[to_count++],token);
                    token = strtok(NULL, delimiter);
                }
                st_symbol = list[2][0];
            }
            fclose(fid);
            if (st_symbol == 'R' || st_symbol == 'S')
            {
                strcpy(status, "Running");
            }
            else if (st_symbol == 'T')
            {
                strcpy(status, "Stopped");
            }
            else
            {
                strcpy(status, " ");
            }
            printf("%d : %s - %s\n", temp->proid, temp->name, status);
            prev = temp;
            temp = temp->next;
        }
        else
        {
            activity_node_ptr rm;
            rm = temp;
            temp = temp->next;
            prev->next = temp;
            rm->next = NULL;
            free(rm);
        }
    }
}
