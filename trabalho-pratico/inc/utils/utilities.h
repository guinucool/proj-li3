#ifndef _UTILITIES_H_
#define _UTILITIES_H_

typedef struct _DATA_{
    short data[3];
    void* key;
    char type;
}Data;

void stringToDate(char* str,short int* date);
int equal(void* key1, void* key2);

#endif