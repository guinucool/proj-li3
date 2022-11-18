#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_MAX 100000

/// \struct Estrutura que define uma node do hashmap.
typedef struct _HASHMAP_NODE_ {
	void * key;							//!< Key do elemento da node
	void * data;						//!< Elemento da node
	struct _HASHMAP_NODE_ * next;		//!< Próxima node ligada à mesma posição do hashmap
} HashmapNode;

/// \struct Estrutura que define o hashmap.
typedef struct _HASHMAP_ {
	HashmapNode * array[HASHMAP_MAX];	//!< Array de nodes que definem o hashmap
} Hashmap;

HashmapNode * createNode(void *key, void *data, HashmapNode * next);
Hashmap* createHashmap();
void destroyHashmap(Hashmap*);
int hashKey_Int(void *key);
int hashKey_Str(void* str);
int hashKey_date(void* date);
void put(Hashmap *hashmap, void *key, void *data, int(*)(void*));
void *get(Hashmap *hashmap, void *key,  int (*)(void*, void*), int(*)(void*), char mode);

#endif