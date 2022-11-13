#ifndef _CMD_H_
#define _CMD_H_

#define ARG_MAX 3
#define PRM_MAX 200

typedef struct _CMD_NODE_
{
    int id;
    char args[ARG_MAX][PRM_MAX];
}Command;

void fetchCmd(char * path);

#endif