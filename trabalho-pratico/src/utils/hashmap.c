#include <stdlib.h>

#include "../../inc/users/users.h"
#include "../../inc/utils/hashmap.h"

//Devolver o endereço de HashMap
Hashmap* createHashmap()
{
    Hashmap *hashmap = (Hashmap*) malloc(sizeof(Hashmap));
    return hashmap;
}

//Quando se fechar o programa, paralisa e destroi (vai libertar o data)
void destroyHashmap(Hashmap* hashmap)
{
    if (hashmap != NULL)
    {
        for (int i = 0; i < HASHMAP_MAX; i++)
            free(hashmap->array[i]);

        free(hashmap);
    }
}

HashmapNode * createNode(void *key, void *data)
{
    HashmapNode * node = (HashmapNode*) malloc(sizeof(HashmapNode));

    node->key = key;
    node->data = data;
    node->next = NULL;

    return(node);
}

int hashKey_Int(void *key)
{
    int *true_Key = ((int*) key);

    return(*true_Key % HASHMAP_MAX);
}

int hashstr_get(const char* s,const int n){
    
    const int p = 29791, m = 100003;
    int hash = 0;
    long p_pow = 1;

    for (int i = 0; i < n; i++)
    {
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash;
}

void put(Hashmap *hashmap, void *key, void *data, int (*hashFunc)(void*))
{
    if (hashmap != NULL)
    {
        int pos = hashFunc(key);

        if (hashmap->array[pos] == NULL)
            hashmap->array[pos] = createNode(key, data);
        else
            hashmap->array[pos]->next = createNode(key, data); 
    }
}

void *get(Hashmap *hashmap, void *key, int (*equal)(void*, void*), int (*hashFunc)(void*)) {

    if (hashmap != NULL)
    {
        int pos = hashFunc(key);

        HashmapNode * node = hashmap->array[pos];

        while (node != NULL)
        {
            if(equal(node->key, key))
                return(node->data);
            
            node = node->next;
        }
    }

    return NULL;
}