#include "../../inc/utils/utilities.h"

void stringToDate(short date[3], char * str)
{
    date[0] = 10*(str[0]-48)+(str[1]-48);
    date[1] = 10*(str[3]-48)+(str[4]-48);
    date[2] = 1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48);
}

int equal(void* key1, void* key2)
{
    return *((int*) key1) == *((int*) key2);
}