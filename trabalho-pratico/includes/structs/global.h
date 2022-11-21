#ifndef _GLOBAL_H_
#define _GLOBAL_H_

typedef struct _HASHMAP_ Hashmap;
typedef struct _GLOBAL_ Global;

Global *  createGlobal();
void destroyGlobal(Global * glob);
Hashmap * global_Hashmap(Global * glob, char mode);

#endif