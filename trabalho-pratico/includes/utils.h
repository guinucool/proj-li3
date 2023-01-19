#ifndef _UTILS_H_
#define _UTILS_H_

typedef struct _HASHMAP_NODE_ HashmapNode;
typedef struct _GLOBAL_ Global;

#define REF_DATE "09/10/2022"

int equal(void* key1, void* key2);
int equal_date(void* key1, void* key2);
int equal_str(void* s1, void* s2);
short age(short[]);
short calculateAge(short[]);
HashmapNode * betweenDates(short * inf, short * up, char type, Global * glob);
void double_to_string(double num, char* str, int precision);

#endif