#include <stdlib.h>

#include "../../inc/structs/date.h"

Date * createDate(short* date, void* key, char type){
    Date* d = (Date*) malloc(sizeof(Date));

    d->date[0] = date[0];
    d->date[1] = date[1];
    d->date[2] = date[2];
    d->keyRef = key;
    d->type = type;
    
    return d;
}

