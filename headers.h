#ifndef HEADERS_H_
#define HEADERS_H_

extern int dir_count;
extern char *global;
extern int latest_fg_pid;
typedef struct node
{
    char *command_nam;
    int p_id;
    struct node *next;
}node;
typedef struct node * nodeptr;

typedef struct activity_node
{
    int proid;
    char *name;
    int back;
    struct activity_node * next;
}activity_node;
typedef struct activity_node * activity_node_ptr;

extern activity_node_ptr head_activity;

typedef struct queue
{
    int front_ptr;
    int rear_ptr;
    char ** list_of_commands;
    int max_capacity;
}queue;
typedef struct queue* queueptr;
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include<sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <ctype.h>
#include <termios.h>
#include <setjmp.h>
#include "helper.h"
#include "activity.h"
#include "syscommands.h"
#include "prompt.h"
#include "path.h"
#include "warp.h"
#include "token.h"
#include "peek.h"
#include "proclore.h"
#include "pastevents.h"
#include "seek.h"
#include "seekr.h"
#include "piping.h"
#include "iman.h"
#include "ping.h"
#include "fgbg.h"
#include "neonate.h"

#endif