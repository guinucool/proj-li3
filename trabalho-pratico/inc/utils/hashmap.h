#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_MAX 100000

typedef struct _HASHMAP_NODE_ {
	void * key;
	void * data;
	struct _HASHMAP_NODE_ * next;
} HashmapNode;

typedef struct _HASHMAP_ {
	HashmapNode * array[HASHMAP_MAX];
} Hashmap;


Hashmap* createHashmap();
void destroyHashmap(Hashmap*);
int hashKey_Int(void *key);
int hashstr_get(void* str);
void put(Hashmap *hashmap, void *key, void *data, int(*)(void*));
void *get(Hashmap *hashmap, void *key,  int (*)(void*, void*), int(*)(void*));

#endif