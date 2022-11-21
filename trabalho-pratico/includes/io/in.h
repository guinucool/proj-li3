#ifndef _INPUT_H_
#define _INPUT_H_

#define MAX_LINE 200

typedef struct _GLOBAL_ Global;

void readFile(char * path, char mode, Global * glob);

#endif