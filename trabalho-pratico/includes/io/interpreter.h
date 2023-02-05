#ifndef _READ_H_
#define _READ_H_

#define MAX_LINE 200

int interUser(char args[][MAX_LINE], Global glob);
int interDriver(char args[][MAX_LINE], Global glob);
int interRide(char args[][MAX_LINE], Global glob);
int interCmd(char args[][MAX_LINE], Global glob, int cmd);

#endif