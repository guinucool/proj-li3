#include <string.h>
#include <math.h>
#include "../inc/utils.h"

void stringToDate(char* str,short int* date)
{    
    date[0] = (short)(10*(str[0]-48)+(str[1]-48));
    date[1] = (short)(10*(str[3]-48)+(str[4]-48));
    date[2] = (short)(1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48));
}

int equal(void* key1, void* key2)
{
    return *((int*) key1) == *((int*) key2);
}

int datecmp(short * dateA, short * dateB)
{
    for (int i = 2; i >= 0; i--)
    {
        if (dateA[i] < dateB[i]) return -1;
        if (dateA[i] > dateB[i]) return 1;
    }

    return 0;
}

int equal_date(void* key1, void* key2)
{
    return !datecmp((short*) key1, (short*) key2);
}

int equal_str(void* s1,void* s2)
{
    return !(strcmp(s1,s2));
}

void nextDay(short date[3])
{    
    short day = 31;
    if ((date[1] < 8 && date[1] % 2 == 0) || (date[1] >= 8 && date[1] % 2 == 1)) day = 30;
    if (date[1] == 2)
    {
        if (date[2] % 4 == 0) day = 29;
        else day = 28;
    }
    short month = 12;

    date[0]++;
    
    if (date[0] > day)
    {
        date[0] = 1;
        date[1]++;
    }
    
    if (date[1] > month)
    {
        date[1] = 1;
        date[2]++;
    }
}

int isId(char s[200]){
    int res = 1;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if(s[i]<48 || s[i]>57){
            res = 0;
        }
    }
    return res;
}