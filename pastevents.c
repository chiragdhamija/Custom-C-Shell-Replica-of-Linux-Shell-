#include "headers.h"
queueptr init_queue()
{
    queueptr q = (queueptr)malloc(sizeof(queue));
    q->list_of_commands = (char **)malloc(sizeof(char *) * 15);
    q->max_capacity = 15;
    q->front_ptr = -1;
    q->rear_ptr = -1;
    for (int i = 0; i < 15; i++)
    {
        q->list_of_commands[i] = (char *)calloc(4097, sizeof(char));
    }
    return q;
}
int isqempty(queueptr q)
{
    return q->front_ptr == -1 && q->rear_ptr == -1;
}
void enque(queueptr q, char *input,int start)
{
    if (strstr(input, "pastevents") != NULL)
    {
        return;
    }
    if (q->front_ptr == -1 && q->rear_ptr == -1)
    {
        q->front_ptr++;
        q->rear_ptr++;
        strcpy(q->list_of_commands[q->front_ptr], input);
        if (start == 1)
        {
            FILE *qptr = fopen("history.txt", "w");
            if (qptr == NULL)
            {
                printf("\033[1;31mCannot open history.txt\n\033[0;0m");
                return;
            }
            else
            {
                if (!isqempty(q))
                {
                    int count = (q->max_capacity + q->rear_ptr - q->front_ptr) % (q->max_capacity) + 1;
                    for (int i = 0; i < count; i++)
                    {
                        int index = (q->front_ptr + i) % q->max_capacity;
                        fprintf(qptr, "%s", q->list_of_commands[index]);
                    }
                }
            }
            fclose(qptr);
        }
    }
    else
    {
        if (strcmp(q->list_of_commands[q->rear_ptr], input) == 0)
        {

            return;
        }
        q->rear_ptr++;
        strcpy(q->list_of_commands[q->rear_ptr % q->max_capacity], input);
        if (start == 1)
        {
            FILE *qptr = fopen("history.txt", "w");
            if (qptr == NULL)
            {
                printf("\033[1;31mCannot open history.txt\n\033[0;0m");
                return;
            }
            else
            {
                if (!isqempty(q))
                {
                    int count = (q->max_capacity + q->rear_ptr - q->front_ptr) % (q->max_capacity) + 1;
                    for (int i = 0; i < count; i++)
                    {
                        int index = (q->front_ptr + i) % q->max_capacity;
                        fprintf(qptr, "%s", q->list_of_commands[index]);
                    }
                }
            }
            fclose(qptr);
        }
    }
}
void deque(queueptr q)
{
    if (!isqempty(q))
    {
        q->front_ptr = (q->front_ptr + 1) % q->max_capacity;
    }
    return;
}
void printqueue(queueptr q)
{
    if (!isqempty(q))
    {
        int count = (q->max_capacity + q->rear_ptr - q->front_ptr) % (q->max_capacity) + 1;
        for (int i = 0; i < count; i++)
        {
            int index = (q->front_ptr + i) % q->max_capacity;
            printf("%s", q->list_of_commands[index]);
        }
    }
    return;
}
void del_q(queueptr q)
{
    for (int i = 0; i < 15; i++)
    {
        q->list_of_commands[i][0] = '\0';
    }
    q->front_ptr = -1;
    q->rear_ptr = -1;
    return;
}
char *replaceSubstring(char *str, char *oldSubstr, char *newSubstr)
{
    char *pos = strstr(str, oldSubstr);

    if (pos != NULL)
    {
        int oldLen = strlen(oldSubstr);
        int newLen = strlen(newSubstr);
        int tailLen = strlen(pos + oldLen);

        memmove(pos + newLen, pos + oldLen, tailLen + 1);
        memcpy(pos, newSubstr, newLen);
        int i = 0, c = 0;
        char *tmp = (char *)malloc(sizeof(char) * 4097);
        while (str[i] != '\0')
        {
            if (str[i] != '\n')
            {
                tmp[c++] = str[i];
            }
            i++;
        }
        tmp[c] = '\0';
        return tmp;
    }
}
