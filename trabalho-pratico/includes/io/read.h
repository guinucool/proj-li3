#ifndef _READ_H_
#define _READ_H_

#define MAX_LINE 200

typedef struct _GLOBAL_ Global;

void interUser(char args[][MAX_LINE], Global * glob);
void interDriver(char args[][MAX_LINE], Global * glob);
void interRide(char args[][MAX_LINE], Global * glob);
void interCmd(char args[][MAX_LINE], Global * glob, int cmd);

#endif