#include <stdlib.h>

#include "../include/hashmap.h"

//Devolver o endereço de HashMap
Hashmap* createHashmap() {
    Hashmap *hashmap = (Hashmap*) malloc(sizeof(Hashmap));
    hashmap->size = 0;

    return hashmap;
}

//Quando se fechar o programa, paralisa e destroi (vai libertar o data)
void destroyHashmap(Hashmap* hashmap) {

    if (hashmap != NULL) {

        for (int i = 0; i < hashmap->size && HASHMAP_MAX; i++) {
            free (hashmap->array[i]);
        }

        free(hashmap);
    }
}

void put(Hashmap *hashmap, void *key, void *data) {

    if (hashmap != NULL && hashmap->size + 1 < HASHMAP_MAX ) {

        hashmap->array[hashmap->size] = (HashmapNode*) malloc(sizeof(HashmapNode)); 
    
        hashmap->array[hashmap->size]->key = key;
        hashmap->array[hashmap->size]->data = data;
        hashmap->size++;
    }
}

void *get(Hashmap *hashmap, void *key, int (*equal)(void*, void*)) {

    if (hashmap != NULL) {

        for (int i = 0; i < hashmap->size && HASHMAP_MAX; i++) {
            if (equal(hashmap->array[i]->key, key)) {
                return hashmap->array[i]->data;
            }
        }
    }

    return NULL;
}