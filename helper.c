#include "headers.h"
char *helpermain(char *input, char *username, char *systemname, char *homedir, char *prevdir, nodeptr head, activity_node_ptr head_activity, queueptr q)
{   
    char *ret=(char *)calloc(4097,sizeof(char));
    global = strdup(input);
    removell(head);
    char *d = ";\n";
    char *t = (char *)calloc(4097, sizeof(char));
    strcpy(t, input);
    char *tok = strtok(t, d);
    int n_t = 0;
    while (tok != NULL)
    {
        n_t++;
        tok = strtok(NULL, d);
    }
    char t_list[n_t][4097];
    char *tok_2 = strtok(input, d);
    int j = 0;
    while (tok_2 != NULL)
    {
        strcpy(t_list[j++],tok_2);
        tok_2 = strtok(NULL, d);
    }
    for (int i = 0; i < n_t; i++)
    {
        int amp = 0;
        for (int j = 0; j < strlen(t_list[i]); j++)
        {
            if (t_list[i][j] == '&')
            {
                amp++;
            }
        }
        if (amp == 0)
        {
            char pi[2] = "|";
            char *milgaya = strstr(t_list[i], pi);
            if (milgaya != NULL)
            {
                ret = pipefunc(username, systemname, homedir, t_list[i], prevdir, q, 0, head, head_activity);
            }
            else
            {
                ret= tokenize(username, systemname, homedir, t_list[i], prevdir, q, 0, head, head_activity);
            }
        }
        else
        {
            char *amp_d = "&\n";
            char *temp_input = (char *)calloc(4097, sizeof(char));
            strcpy(temp_input, t_list[i]);
            char *tok_3 = strtok(temp_input, amp_d);
            int amp_tok_count = 0;
            while (tok_3 != NULL)
            {
                amp_tok_count++;
                tok_3 = strtok(NULL, amp_d);
            }
            char amp_list[amp_tok_count][4097];
            char *tok_4 = strtok(t_list[i], amp_d);
            int m = 0;
            while (tok_4 != NULL)
            {
                strcpy(amp_list[m++],tok_4);
                tok_4 = strtok(NULL, amp_d);
            }
            for (int j = 0; j < amp_tok_count; j++)
            {

                if (amp != 0)
                {
                    char pi[2] = "|";
                    char *milgaya = strstr(amp_list[j], pi);
                    if (milgaya != NULL)
                    {
                        ret= pipefunc(username, systemname, homedir, amp_list[j], prevdir, q, 1, head, head_activity);
                    }
                    else
                    {
                        ret= tokenize(username, systemname, homedir, amp_list[j], prevdir, q, 1, head, head_activity);
                    }
                    amp--;
                }
                else
                {
                    char pi[2] = "|";
                    char *milgaya = strstr(amp_list[j], pi);
                    if (milgaya != NULL)
                    {
                        ret = pipefunc(username, systemname, homedir, amp_list[j], prevdir, q, 0, head, head_activity);
                    }
                    else
                    {
                        ret = tokenize(username, systemname, homedir, amp_list[j], prevdir, q, 0, head, head_activity);
                    }
                    amp--;
                }
            }
        }
    }
    return ret;
}