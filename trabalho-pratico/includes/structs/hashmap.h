#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define INACTIVE 0
#define ACTIVE 1

#define HASHMAP_SIZE 11

// Estrutura
typedef struct _HASHMAP_ *Hashmap;

// Tratamentos
Hashmap createHashmap();
void destroyHashmap(Hashmap hashmap, void (*)(void*));
void debugPrintHashmap(Hashmap hashmap, void (*)(void*), void (*)(void*));
int put(Hashmap hashmap, void * key, void * data, int (*)(void*,int));
void * get(Hashmap hashmap, void * key, int (*)(void*,void*), int (*)(void*,int));
int map(Hashmap hashmap, int (*)(void*, void (*)(void*,void*), void*), void (*)(void*,void*), void * second);

#endif