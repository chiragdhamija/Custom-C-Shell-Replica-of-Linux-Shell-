#ifndef __TOKEN_H
#define __TOKEN_H
typedef struct queue* queueptr;
char *tokenize(char *username, char *systemname, char *homedir, char *input, char *prevdir, queueptr q, int bg_check,nodeptr head,activity_node_ptr head_activity);
void restore_output(int a_r, int o_r, int o);
#endif