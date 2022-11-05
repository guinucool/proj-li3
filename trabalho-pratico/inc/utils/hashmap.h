#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_MAX 100

typedef struct _HASHMAP_NODE_ {
	void* key;
	void* data;
} HashmapNode;

typedef struct _HASHMAP_ {
	HashmapNode *array[HASHMAP_MAX];
	int size;
} Hashmap;


Hashmap* createHashmap();
void destroyHashmap(Hashmap*);
void put(Hashmap *hashmap, void *key, void *data);
void *get(Hashmap *hashmap, void *key,  int (*)(void*, void*));

#endif