#ifndef _UTILS_H_
#define _UTILS_H_

#define REF_DATE "09/10/2022"

void stringToDate(char* str,short int* date);
int equal(void* key1, void* key2);
int datecmp(short * dateA, short * dateB);
int equal_date(void* key1, void* key2);
int equal_str(void* s1, void* s2);
void nextDay(short date[3]);
short age(short[]);
short calculateAge(short[]);

#endif