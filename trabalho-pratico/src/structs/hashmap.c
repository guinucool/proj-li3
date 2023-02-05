#include <stdio.h>
#include <stdlib.h>
#include "../../includes/utils.h"
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
 * A função createNode cria uma node do Hashmap,
 * associando os inputs da função às
 * propriedades da node criada.
 * 
 * @param key O void pointer da chave de procura da node.
 * @param data O void pointer da informação que será guardada na node.
 * @param status O status da node (ativa ou desativa(necessidade de reposicionar)).
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
 * @param destroy A função que destroí um elemento da node.
 */ 
void destroyNode(HashmapNode node, void (*destroy)(void *))
{
    if (node.key)
    {
        free(node.key);         //!< Liberta a chave do elemento
        destroy(node.data);     //!< Liberta a data do elemento
    }
}

/// @brief A função debugPrintNode imprime uma node.
/**
 * A função debugPrintNode imprime a estrutura de uma node
 * para propósitos de debugging.
 * 
 * @param node A node a ser imprensa.
 * @param keyPrinter A função que imprime uma chave do node.
 * @param elemPrinter A função que imprime um elemento do node.
 */
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
    for (int i = 0; i < HASHMAP_SIZE; i++)
        hashmap->map[i] = createNode(NULL, NULL, INACTIVE);
    
    hashmap->size = 0;
    hashmap->max = HASHMAP_SIZE;

    return hashmap;
}

/// @brief A função resizeHashmap redimensiona um hashmap.
/**
 * A função resizeHashmap redimensiona um hashmap, e é normalmente
 * chamada quando este está a 80% da sua capacidade ou caso
 * não conseguia encontrar uma posição para inserir um elemento.
 * 
 * Uma vez redimensionado o hashmap, este irá ser percorrido
 * de forma a reposicionar os seus elementos de forma a
 * respeitar as regras das novas dimensões do hashmap.
 * 
 * Para tal será usado o identificador de status de
 * cada node.
 * 
 * @param hashmap O hashmap a ser redimensionado.
 * @param hashFunc A função de hash a ser usada para o reposionamento dos elementos.
 */
void resizeHashmap(Hashmap hashmap, int (*hashFunc)(void*,int))
{
    int ini = hashmap->max;

    for (int i = 0; i < hashmap->max; i++)
        if (hashmap->map[i].key) hashmap->map[i].status = INACTIVE;

    hashmap->max = hashmap->max * 2;

    while (!isPrime(hashmap->max)) hashmap->max++;

    hashmap->map = realloc(hashmap->map, sizeof(HashmapNode) * hashmap->max);

    for (int i = ini; i < hashmap->max; i++)
        hashmap->map[i] = createNode(NULL, NULL, INACTIVE);
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
 * o espaço reservado por cada elemento do mesmo.
 * 
 * @param hashmap O Hashmap a ser destruído.
 */ 
void destroyHashmap(Hashmap hashmap, void (*destroy)(void*))
{
    if (hashmap)
    {
        for (int i = 0; i < hashmap->max; i++)
            destroyNode(hashmap->map[i], destroy);
        free(hashmap->map);
        free(hashmap);
    }
}

/// @brief A função debugPrintHashmap imprime um hashmap.
/**
 * A função debugPrintHashmap imprime um hashmap
 * e todos os seus elementos para fins de debugging.
 * 
 * @param hashmap O hashmap a ser imprenso.
 * @param keyPrinter A função que imprime as chaves de cada elemento do hashmap.
 * @param elemPrinter A função que imprime cada elemento do hashmap.
 */
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

/// @brief A função put insere um elemento no hashmap.
/**
 * A função put insere um elemento no hashmap, usando a função hashFunc
 * para saber em que posição inserir o mesmo.
 * 
 * Após descobrir a posição, esta irá verificar se ocorreu alguma
 * colisão. Caso não tenha ocorrido, insere o elemento numa nova
 * node nesta posição. Caso contrário, irá utilizar a estratégia
 * de quadric probing para procurar uma nova posição adequada
 * que esteja livre.
 * 
 * @param hashmap O hashmap onde irá ser inserido o elemento.
 * @param key O void pointer da chave do elemento a ser inserido.
 * @param data O void pointer do elemento a ser inserido.
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
 * Encontrando a posição desejada, irá precorrer as várias posições obtidas através
 * do quadric probing (se necessário) até encontrar a chave,
 * e respetivamente o elemento, desejada.
 * 
 * @param hashmap O hashmap onde será feita a procura.
 * @param key O void pointer com uma chave igual à do elemento desejado.
 * @param equal A função de igualdade para o tipo de chave fornecido.
 * @param hashFunc A função de hash para o tipo de chave fornecido.
 * 
 * @return O void pointer do elemento desejado.
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

/// @brief A função map irá aplicar uma função a todos os elementos de um hashmap.
/**
 * A função map irá percorrer um hashmap inteiro e
 * aplicar a função fornecida a todos os seus elementos
 * existentes.
 * 
 * @param hashmap O hashmap onde as mudanças irão ocorrer.
 * @param mapper A função que mapeia cada elemento do hashmap, caso seja mapeável.
 * @param function A função que irá ser aplicada.
 * @param second O segundo parâmetro da função que irá ser aplicada.
 * 
 * @return O número de operações executadas.
 */
int map(Hashmap hashmap, int (*mapper)(void*, void (*)(void*,void*), void*), void (*function)(void*,void*), void * second)
{
    int count = 0;

    for (int i = 0; i < hashmap->max; i++)
        if(hashmap->map[i].key)
            count += mapper(hashmap->map[i].data, function, second);

    return count;
}