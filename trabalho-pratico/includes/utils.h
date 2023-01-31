#ifndef _UTILS_H_
#define _UTILS_H_

// Hashmaps
int equal(void* key1, void* key2);
int equal_str(void* s1, void* s2);
int hashKey_Int(void * key, int size);
int hashKey_Str(void * str, int size);

// Nulas
void null(void * element);
int nullMap(void * element, void (*)(void*,void*), void * second);

// Verificações
int isId(char s[200]);
int isPrime(int num);

// Tratamentos
void strtop(char * str);

#endif