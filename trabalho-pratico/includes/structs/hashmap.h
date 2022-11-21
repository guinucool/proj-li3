#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_MAX 100000

typedef struct _HASHMAP_NODE_ HashmapNode;

typedef struct _HASHMAP_ Hashmap;

HashmapNode * createNode(void *key, void *data, HashmapNode * next);
void destroyNode(HashmapNode * node, char mode);
Hashmap* createHashmap();
void destroyHashmap(Hashmap*);
int hashKey_Int(void *key);
int hashKey_Str(void* str);
int hashKey_date(void* date);
void put(Hashmap *hashmap, void *key, void *data, int(*)(void*));
void *get(Hashmap *hashmap, void *key,  int (*)(void*, void*), int(*)(void*), char mode);
void * node_Void(HashmapNode * node, char mode);
HashmapNode * node_Node(HashmapNode * node);

#endif