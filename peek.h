#ifndef __PEEK_H
#define __PEEK_H
#include<dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
void print_file_details(const char *filename);
void peekkar(char **token_list, int num_tokens,int flag_tokens,int path_tokents,char *prevdir, char *homedir);

#endif