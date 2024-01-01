#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H
queueptr init_queue();
void enque(queueptr q, char *input,int start);
void deque(queueptr q);
void del_q(queueptr q);
void printqueue(queueptr q);
int isqempty(queueptr q);
char *replaceSubstring(char *str, char *oldSubstr, char *newSubstr);
#endif