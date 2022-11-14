#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "../../inc/structs/hashmap.h"

typedef struct _GLOBAL_
{
    Hashmap * users;
    Hashmap * drivers;
    Hashmap * rides;
}Global;


#endif