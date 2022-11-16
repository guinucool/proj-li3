#ifndef _UTILS_H_
#define _UTILS_H_

void stringToDate(char* str,short int* date);
int equal(void* key1, void* key2);
int datecmp(short * dateA, short * dateB);
int equal_date(void* key1, void* key2);
void nextDay(short date[3]);

#endif