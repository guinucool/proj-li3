#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/hashmap.h"

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

HashmapNode * createNode(void *key, void *data, HashmapNode * next)
{
    HashmapNode * node = (HashmapNode*) malloc(sizeof(HashmapNode));

    node->key = key;
    node->data = data;
    node->next = next;

    return(node);
}

void destroyNode(HashmapNode * node)
{
    HashmapNode * hold = node;

    while (hold != NULL)
    {
        HashmapNode * temp = hold->next;
        free(hold);
        hold = temp;
    }
}

int hashKey_Int(void *key)
{
    int *true_Key = ((int*) key);

    return(*true_Key % HASHMAP_MAX);
}

int hashKey_Str(void* str)
{
    const char * s = str;
    const int n = strlen(s);
    const int p = 111111, m = 99991;
    int hash = 0;
    long p_pow = 1;

    for (int i = 0; i < n; i++)
    {
        hash = (hash + s[i] * p_pow) % m;
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
            hashmap->array[pos] = createNode(key, data, NULL);
        else
            hashmap->array[pos] = createNode(key, data, hashmap->array[pos]);
    }
}

void * get(Hashmap *hashmap, void *key, int (*equal)(void*, void*), int (*hashFunc)(void*), char mode)
{
    if (hashmap != NULL)
    {
        int pos = hashFunc(key);

        HashmapNode * node = hashmap->array[pos];

        while (node != NULL)
        {
            if(equal(node->key, key))
            {
                if(mode)
                    return(node->data);
                else
                    return((void*)node);
            }
            
            node = node->next;
        }
    }

    return NULL;
}