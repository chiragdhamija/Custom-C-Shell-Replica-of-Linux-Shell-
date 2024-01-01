#ifndef __SEEKR_H
#define __SEEK_H
void recursion(char*orig_target,char *targetdir,char *targetword,int d,int e,int f,int *count,char *e_ans);
int check(char *input , char *targetword);
void printrelativepath(char *orig_target, char *ans);
#endif