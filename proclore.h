#ifndef __PROCLORE_H
#define __PROCLORE_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
void proclorekar(char **token_list,int tok_count,char *homedir,int bg_check);
int st_to_number(char * st);
#endif
