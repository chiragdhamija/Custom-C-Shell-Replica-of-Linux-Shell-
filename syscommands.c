#include "headers.h"
void printll(nodeptr head)
{
    nodeptr temp=head;
    temp=temp->next;
    if(temp==NULL)
    {
        return;
    }
    while(temp!=NULL)
    {
        printf("%d %s\n",temp->p_id,temp->command_nam);
        temp=temp->next;
    }
}
nodeptr makenode(int p, char *n)
{
    nodeptr t = (nodeptr)malloc(sizeof(node));
    t->command_nam = (char *)calloc(31, sizeof(char));
    t->p_id = p;
    strcpy(t->command_nam, n);
    t->next = NULL;
    return t;
}
void insertinll(nodeptr head, nodeptr ins)
{   
    if (head->next == NULL)
    {
        head->next = ins;
    }
    else
    {
        nodeptr prev_h = head->next;
        ins->next = prev_h;
        head->next = ins;
    }
}
void removell(nodeptr head)
{
    nodeptr temp = head;
    nodeptr prev = head;
    temp = temp->next;
    if (temp == NULL)
    {
        return;
    }
    while (temp != NULL)
    {
        int status;
        int pid_end_check = waitpid(temp->p_id, &status, WNOHANG);
        if (pid_end_check > 0)
        {
            nodeptr rm;
            if (WIFEXITED(status))
            {
                printf("%s exitted normally (%d)\n", temp->command_nam, temp->p_id);
            }
            else if (WIFSIGNALED(status))
            {
                printf("%s exited abnormally (%d)\n", temp->command_nam, temp->p_id);
            }
            rm = temp;
            temp = temp->next;
            prev->next = temp;
            rm->next = NULL;
            free(rm);
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
}