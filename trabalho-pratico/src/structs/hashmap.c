#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/hashmap.h"

/// @brief A função createNode cria uma node do Hashmap.
/**
 * A função createNode cria uma node do Hashmap, alocando
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

/// @brief A função destroyNode destroí uma node do Hashmap.
/**
 * A função destroyNode destroí uma node do Hashmap,
 * libertando o espaço ocupado por esta na memória.
 * 
 * Desta forma, irá também destruir todas as nodes que estam,
 * posteriormente, ligadas a esta.
 * 
 * @param node A node a ser destruída.
 */ 
void destroyNode(HashmapNode * node)
{
    HashmapNode * hold = node;

    while (hold != NULL)
    {
        HashmapNode * temp = hold->next;    //!< Encontra o próximo elemento na ligação
        free(hold);                         //!< Liberta o atual
        hold = temp;                        //!< Passa o processo para o próximo elemento
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

/// @brief A função hashKey_Int cria uma hash de procura, cuja chave é um Int.
/**
 * A função hashKey_Int cria uma hash de procura, cuja chave é um Int, usando
 * o módulo (chave mod tamanho do hashmap) para criar a hash que
 * corresponderá à posição do elemento na hashmap.
 * 
 * @param key O void pointer da chave do elemento pretendido.
 */
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
void put(Hashmap *hashmap, void *key, void *data, int (*hashFunc)(void*))
{
    if (hashmap != NULL)
    {
        int pos = hashFunc(key);                                                //!< Devolve a hash (posição) do elemento

        if (hashmap->array[pos] == NULL)                                        //!< Não existe nada na posição
            hashmap->array[pos] = createNode(key, data, NULL);                  //!< Cria node com ligação a null
        else                                                                    //!< Existe algo na posição
            hashmap->array[pos] = createNode(key, data, hashmap->array[pos]);   //!< Cria node com ligação às já existentes
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
 * @param mode O modo desejado (devolver o void pointer do elemento ou da cabeça da lista ligada de nodes).
 * 
 * @return O void pointer do elemento/cabeça da lista desejado.
 */
void * get(Hashmap *hashmap, void *key, int (*equal)(void*, void*), int (*hashFunc)(void*), char mode)
{
    if (hashmap != NULL)
    {
        int pos = hashFunc(key);                    //!< Devolve a possível hash (posição) onde pode estar o elemento desejado

        HashmapNode * node = hashmap->array[pos];   //!< Encontra a node presente na posição desejada

        while (node != NULL)                        //!< Enquanto existir algo na posição
        {
            if(equal(node->key, key))               //!< Verifica se a key da node é a do elemento desejado
            {
                if(mode)                            //!< Caso o modo do elemento esteja ativo
                    return(node->data);             //!< Devolve o pointer do elemento
                else                                //!< Caso não esteja ativo
                    return((void*)node);            //!< Devolve o pointer da cabeça da lista de nodes (onde a key já é a desejada)
            }
            
            node = node->next;                      //!< Passa à próxima node (ligada à atual) na posição desejada
        }
    }

    return NULL;
}