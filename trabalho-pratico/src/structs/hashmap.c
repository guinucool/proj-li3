#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/hashmap.h"

/// \struct Estrutura que define uma node do hashmap.
typedef struct _HASHMAP_NODE_ {
	void * key;							//!< Key do elemento da node
	void * data;						//!< Elemento da node
    char status;                        //!< Estado da node
} HashmapNode;

/// \struct Estrutura que define o hashmap.
typedef struct _HASHMAP_ {
	HashmapNode * map;	                //!< Array de nodes que definem o hashmap
    int size;                           //!< Tamanho atual do hashmap
    int max;                            //!< Tamanho máximo do hashmap
}*Hashmap, NPHashmap;

/// @brief A função createNode cria uma node do Hashmap.
/**
 * A função createNode cria uma node do Hashmap.
 * 
 * Uma vez criada, associa os inputs da função às
 * propriedades da node criada.
 * 
 * @param key O void pointer da chave de procura da node.
 * @param data O void pointer da informação que será guardada na node.
 * 
 * @return A node criada.
 */ 
HashmapNode createNode(void * key, void * data, char status)
{
    HashmapNode node;

    node.key = key;
    node.data = data;
    node.status = status;

    return(node);
}

/// @brief A função destroyNode destroí uma node do Hashmap.
/**
 * A função destroyNode destroí uma node do Hashmap,
 * libertando o espaço ocupado pelos seus
 * elementos na memória.
 * 
 * @param node A node a ser destruída.
 */ 
void destroyNode(HashmapNode node, void (*destroy)(void *))
{
    if (node.key)
    {
        free(node.key);         //!< Liberta a chave do elemento
        //destroy(node.data);     //!< Liberta a data do elemento
    }
}

void debugPrintNode(HashmapNode node, void (*keyPrinter)(void*), void (*elemPrinter)(void*))
{
    printf("(HashmapNode) {\n    [%p]key: ", node.key);
    keyPrinter(node.key);
    printf("\n    [%p]data: ", node.data);
    elemPrinter(node.data);
    printf("\n    status: %d\n}\n", node.status);
}

/// @brief A função createHashmap cria um Hashmap.
/**
 * A função createHashmap cria um Hashmap, alocando
 * a memória necessária para guardar os seus elementos.
 * 
 * @return O Hashmap criado e alocado.
 */
Hashmap createHashmap()
{
    Hashmap hashmap = (Hashmap) malloc(sizeof(NPHashmap));

    hashmap->map = malloc(sizeof(HashmapNode) * HASHMAP_SIZE);
    hashmap->size = 0;
    hashmap->max = HASHMAP_SIZE;

    return hashmap;
}

int isPrime(int num)
{
    int res = 1;

    if (num <= 1) res = 0;

    if (num % 2 == 0 && num > 2) res = 0;

    for(int i = 3; i < num / 2 && res; i+= 2) if (num % i == 0) res = 0;

    return res;
}

void put(Hashmap hashmap, void * key, void * data, int (*hashFunc)(void*,int));

void resizeHashmap(Hashmap hashmap, int (*hashFunc)(void*,int))
{
    int ini = hashmap->max;

    for (int i = 0; i < hashmap->max; i++)
        if (hashmap->map[i].key) hashmap->map[i].status = INACTIVE;

    hashmap->max = hashmap->max * 2;

    while (!isPrime(hashmap->max)) hashmap->max++;

    hashmap->map = realloc(hashmap->map, sizeof(HashmapNode) * hashmap->max);
    hashmap->map[ini] = createNode(NULL, NULL, INACTIVE);
    hashmap->size = 0;

    for (int i = 0; i < ini; i++)
    {
        if (hashmap->map[i].key && !hashmap->map[i].status)
        {
            void * reKey = hashmap->map[i].key;
            void * reData = hashmap->map[i].data;

            hashmap->map[i] = createNode(NULL, NULL, INACTIVE);

            put(hashmap, reKey, reData, hashFunc);
        }
    }
}

/// @brief A função destroyHashmap destroí um Hashmap.
/**
 * A função destroyHashmap destroí um Hashmap, libertando
 * o espaço reservado por cada elemento da mesma.
 * 
 * @param hashmap O Hashmap a ser destruído.
 */ 
void destroyHashmap(Hashmap hashmap, void (*destroy)(void*))
{
    if (hashmap)
        for (int i = 0; i < hashmap->max; i++)
            destroyNode(hashmap->map[i], destroy);
}

void debugPrintHashmap(Hashmap hashmap, void (*keyPrinter)(void*), void (*elemPrinter)(void*))
{
    printf("[%p](Hashmap) {\n    max: %d\n    size: %d\n    [%p]elements:\n",
        hashmap,
        hashmap->max,
        hashmap->size,
        hashmap->map
    );
    for (int i = 0; i < hashmap->max; i++)
    {
        printf("    [%d]", i);
        debugPrintNode(hashmap->map[i], keyPrinter, elemPrinter);
    }
    printf("}\n");
}

/// @brief A função hashKey_Int cria uma hash de procura, cuja chave é um Int.
/**
 * A função hashKey_Int cria uma hash de procura, cuja chave é um Int, usando
 * o módulo (chave mod tamanho do hashmap) para criar a hash que
 * corresponderá à posição do elemento na hashmap.
 * 
 * @param key O void pointer da chave do elemento pretendido.
 */
int hashKey_Int(void * key, int size)
{
    int *true_Key = ((int*) key);

    return(*true_Key % size);
}

/// @brief A função hashKey_Str cria uma hash de procura, cuja chave é uma String.
/**
 * A função hashKey_Str cria uma hash de procura, cuja chave é uma String, usando 
 * o somatorio do modulo do resultado da multiplicação dos caracteres com as respetivas posições 
 * na string. O resultado deste somatorio será a posição do elemento na hashmap.
 * 
 * @param str O void pointer da chave do elemento pretendido.
 */
int hashKey_Str(void * str, int size)
{
    const char * s = str;
    const int n = strlen(s);
    const int p = 111111;
    int hash = 0;
    long p_pow = 1;

    for (int i = 0; i < n; i++)
    {
        hash = (hash + s[i] * p_pow) % size;
        p_pow = (p_pow * p) % size;
    }

    // return hash < 0 ? hash * -1 : hash;
    return hash;
}

/// @brief A função put insere um elemento no hashmap.
/**
 * A função put insere um elemento no hashmap, usando a função hashFunc
 * para saber em que posição inserir o mesmo.
 * 
 * Após descobrir a posição, esta irá verificar se ocorreu alguma
 * colisão. Caso não tenha ocorrido, insere o elemento numa nova
 * node nesta posição. Caso contrário, insere o elemento no topo
 * da lista ligada de nodes que se encontra nessa posição.
 * 
 * @param hashmap O hashmap onde irá ser inserido o elemento.
 * 
 * @param key O void pointer da chave do elemento a ser inserido.
 * 
 * @param data O void pointer do elemento a ser inserido.
 * 
 * @param hashFunc A função que irá dar hash à chave.
 */
void put(Hashmap hashmap, void * key, void * data, int (*hashFunc)(void*,int))
{
    if (hashmap)
    {
        double a = (double) hashmap->size / hashmap->max;

        if (a >= 0.8f) resizeHashmap(hashmap, hashFunc);

        int pos = hashFunc(key, hashmap->max);
        int or = pos;

        for (int i = 1; hashmap->map[pos].key && hashmap->map[pos].status && i <= hashmap->size; i++)
            pos = (or + i * i) % hashmap->max;
        
        if (hashmap->map[pos].key && hashmap->map[pos].status)
        {
            resizeHashmap(hashmap, hashFunc);
            put(hashmap, key, data, hashFunc);
            return;
        }
        
        if (hashmap->map[pos].key && !hashmap->map[pos].status)
        {
            void * reKey = hashmap->map[pos].key;
            void * reData = hashmap->map[pos].data;

            hashmap->map[pos] = createNode(NULL, NULL, INACTIVE);

            put(hashmap, reKey, reData, hashFunc);
            put(hashmap, key, data, hashFunc);
            return;
        }
        
        hashmap->map[pos] = createNode(key, data, ACTIVE);
        hashmap->size++;
    }
}

/// @brief A função get encontra e devolve o void pointer de um elemento no hashmap.
/**
 * A função get encontra e devolve o void pointer de um elemento no hashmap,
 * usando a função hash da chave para encontrar a posição do respetivo.
 * 
 * Encontrando a posição desejada, irá precorrer a lista de nodes (se necessário)
 * nessa posição até encontrar a chave, e respetivamente o elemento, desejada.
 * 
 * Alternativamente e se desejado, a função poderá devolver a node, e respetivas
 * ligações, apartir da qual é encontrada a chave (útil para estruturas auxiliares
 * de procura).
 * 
 * @param hashmap O hashmap onde será feita a procura.
 * 
 * @param key O void pointer da chave do elemento desejado.
 * 
 * @param equal A função de igualdade para o tipo de chave fornecido.
 * 
 * @param hashFunc A função de hash para o tipo de chave fornecido.
 * 
 * @return O void pointer do elemento/cabeça da lista desejado.
 */
void * get(Hashmap hashmap, void * key, int (*equal)(void*, void*), int (*hashFunc)(void*,int))
{
    if (hashmap)
    {
        int pos = hashFunc(key, hashmap->max);
        int or = pos;

        for (int i = 1; hashmap->map[pos].key && !equal(hashmap->map[pos].key, key) && i <= hashmap->size; i++)
            pos = (or + i * i) % hashmap->max;
        
        if(hashmap->map[pos].key && equal(hashmap->map[pos].key, key))
            return hashmap->map[pos].data;
    }

    return NULL;
}

void printerInt(void * i)
{
    int * a = (int *) i;

    if(a) printf("%d", *a);
    else printf("NULL");
}

int equal(void* key1, void* key2)
{
    return *((int*) key1) == *((int*) key2);
}

int main()
{
    int * data = (int*) malloc(sizeof(int));

    *data = 10;

    int * data1 = (int*) malloc(sizeof(int));

    *data1 = 21;

    int * data2 = (int*) malloc(sizeof(int));

    *data2 = 32;

    int * data3 = (int*) malloc(sizeof(int));

    *data3 = 3;

    int * data4 = (int*) malloc(sizeof(int));

    *data4 = 1;

    int * data5 = (int*) malloc(sizeof(int));

    *data5 = 23;

    int * data6 = (int*) malloc(sizeof(int));

    *data6 = 31;

    int * data7 = (int*) malloc(sizeof(int));

    *data7 = 7;

    int * data8 = (int*) malloc(sizeof(int));

    *data8 = 19;

    int * data9 = (int*) malloc(sizeof(int));

    *data9 = 6;

    int * data10 = (int*) malloc(sizeof(int));

    *data10 = 29;

    int * data11 = (int*) malloc(sizeof(int));

    *data11 = 52;

    int * data12 = (int*) malloc(sizeof(int));

    *data12 = 75;

    Hashmap hashmap = createHashmap();

    put(hashmap, data, data, hashKey_Int);

    put(hashmap, data1, data1, hashKey_Int);

    put(hashmap, data2, data2, hashKey_Int);

    put(hashmap, data3, data3, hashKey_Int);

    put(hashmap, data4, data4, hashKey_Int);

    put(hashmap, data5, data5, hashKey_Int);

    put(hashmap, data6, data6, hashKey_Int);

    put(hashmap, data7, data7, hashKey_Int);

    put(hashmap, data8, data8, hashKey_Int);

    put(hashmap, data9, data9, hashKey_Int);

    put(hashmap, data10, data10, hashKey_Int);

    put(hashmap, data11, data11, hashKey_Int);

    put(hashmap, data12, data12, hashKey_Int);

    debugPrintHashmap(hashmap, printerInt, printerInt);

    //destroyHashmap(hashmap, free);

    int * key = malloc(sizeof(int));

    *key = 75;

    int * val = get(hashmap, key, equal, hashKey_Int);

    printf("%d\n", *val);

    return 0;
}
