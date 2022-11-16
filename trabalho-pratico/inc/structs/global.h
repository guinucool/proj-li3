#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "hashmap.h"

typedef struct _GLOBAL_
{
    Hashmap * users;
    Hashmap * drivers;
    Hashmap * rides;
    Hashmap * cities;
    Hashmap * driverId;
    Hashmap * dates;
}Global;

Global *  createGlobal();
void destroyGlobal(Global * glob);

#endif