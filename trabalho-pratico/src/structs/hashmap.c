#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/hashmap.h"

/// @brief A função createNode cria um node (elemento) do Hashmap.
/**
 * A função createNode cria um node (elemento) do Hashmap, alocando
 * a memória necessária a sua criação.
 * 
 * Uma vez alocada a memória, associa os inputs da função às
 * propriedades da node criada.
 * 
 * @param key O void pointer da chave de procura da node.
 * 
 * @param data O void pointer da informação que será guardada na node.
 * 
 * @param next A próxima node a ser inserida na lista ligada (para o caso de colisões).
 * 
 * @return A node criada e alocada.
 */ 
HashmapNode * createNode(void *key, void *data, HashmapNode * next)
{
    HashmapNode * node = (HashmapNode*) malloc(sizeof(HashmapNode));

    node->key = key;
    node->data = data;
    node->next = next;

    return(node);
}

/// @brief A função destroyNode destroí um node (elemento) do Hashmap.
/**
 * 
 */ 
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

/// @brief A função createHashmap cria um Hashmap.
/**
 * A função createHashmap cria um Hashmap, alocando
 * a memória necessária paara este tipo de variável.
 * 
 * @return O Hashmap criado e alocado.
 */
Hashmap* createHashmap()
{
    Hashmap *hashmap = (Hashmap*) malloc(sizeof(Hashmap));
    return hashmap;
}

/// @brief A função destroyHashmap destroí um Hashmap.
/**
 * A função destroyHashmap destroí um Hashmap, libertando
 * o espaço reservado por esta variável, assim como
 * o espaço reservado por cada elemento da mesma.
 * 
 * @param hashmap O Hashmap a ser destruído.
 */ 
void destroyHashmap(Hashmap* hashmap)
{
    if (hashmap != NULL)
    {
        for (int i = 0; i < HASHMAP_MAX; i++)
            destroyNode(hashmap->array[i]);

        free(hashmap);
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

int hashKey_date(void* date)
{
    const short* d = (short*)date;
    const int n = 3;
    const int p = 111111, m = 99991;
    int hash = 0;
    long p_pow = 1;

    for (int i = 0; i < n; i++)
    {
        hash = (hash + d[i] * p_pow) % m;
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