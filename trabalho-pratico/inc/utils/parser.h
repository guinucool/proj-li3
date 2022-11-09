#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../inc/utils/hashmap.h"

#define MAX_LINE 200

Hashmap * createCatalogue(char * path, char ctl, void (*)(Hashmap*,char(*)[200]));
void createAll(char * path);

#endif