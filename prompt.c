#include "headers.h"

void prompt(char *username,char * systemname,char *homedir,char *rt) {
    // Do not hardcode the prmopt
    char *currdir=(char *)calloc(4097,sizeof(char));
    getcwd(currdir,4097);
    char *final=findfinalpath(homedir,currdir);
    printf("<\033[1;35m%s\033[1;0m@\033[1;35m%s:%s\033[0;32m%s\033[0;0m>",username,systemname,final,rt);
    free(currdir);
}
