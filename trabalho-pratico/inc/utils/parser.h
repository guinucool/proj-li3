#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../inc/utils/hashmap.h"

#define MAX_LINE 200

typedef struct _DATA_BASE_ {
    Hashmap * users, * drivers, * rides;
}Data;

Data * createAll(char * path);

#endif