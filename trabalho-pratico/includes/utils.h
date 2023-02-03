#ifndef _UTILS_H_
#define _UTILS_H_

#define INT 'i'
#define DOUBLE 'd'

// Hashmaps
int equal(void* key1, void* key2);
int equal_str(void* s1, void* s2);
int hashKey_Int(void * key, int size);
int hashKey_Str(void * str, int size);

// Nulas
void null(void * element);
int nullMap(void * element, void (*)(void*,void*), void * second);

// Verificações
int isNumber(char s[200], char mode);
int isPrime(int num);

// Tratamentos
void strtop(char * str);
int intLen(int value);
void tokens(char * str, char * delim, char tok[][200]);

#endif