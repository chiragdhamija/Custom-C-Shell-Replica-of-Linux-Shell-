#ifndef __ACTIVITY_H
#define __ACTIVITY_H
activity_node_ptr make_act(int pid,char *input,int bg);
void insert_activity(activity_node_ptr head,activity_node_ptr ins);
void activitykar(activity_node_ptr head, char *homedir);
#endif