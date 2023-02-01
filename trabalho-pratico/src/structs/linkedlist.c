#include <stdio.h>
#include <stdlib.h>
#include "../../includes/structs/linkedlist.h"

/// \struct Estrutura que define as nodes das listas de ligadas
typedef struct _LINKED_NODE_ {
    void * element;                 //!< Elemento de uma posição da lista
    struct _LINKED_NODE_ * next;    //!< Apontador para a próxima posição da lista
}*LinkedNode, NPLinkedNode;

/// \struct Estrutura que define as listas ligadas
typedef struct _LINKED_LIST_ {
    LinkedNode head;                //!< Apontador para a cabeça da lista
}*LinkedList, NPLinkedList;

/// @brief A função createNode cria uma node de lista ligada.
/** 
 * A função createList cria uma node de lista ligada
 * alocando o espaço necessário para mesma.
 * 
 * Dentro desta posição alocada insere um elemento, e anexa (ou não)
 * a continuação/o final(NULL) da lista.
 * 
 * @param element Elemento a ser guardado nesta posição da lista.
 * @param next Lista a qual esta se liga.
 * 
 * @return A nova node criada.
 */
LinkedNode createListNode(void * element, LinkedNode next) 
{
    LinkedNode node = (LinkedNode) malloc(sizeof(NPLinkedNode));

    node->element = element;
    node->next = next;

    return node;
}

/// @brief A função createList cria uma lista ligada.
/** 
 * A função createList cria uma lista ligada
 * alocando o espaço necessário para mesma.
 * 
 * Dentro desta posição alocada irá guardar a cabeça da
 * lista.
 * 
 * @return A nova lista criada.
 */
LinkedList createList()
{
    LinkedList list = (LinkedList) malloc(sizeof(NPLinkedList));

    list->head = NULL;

    return list;
}

/// @brief A função addOrdList adiciona um elemento a uma lista ligada ordenada.
/**
 * A função addOrdList adiciona um elemento a uma lista ligada ordenada,
 * usando uma função compare fornecida para decidir a melhor posição para
 * colocar este novo elemento.
 * 
 * A função compare fornecida deverá seguir as seguintes regras:
 * - return >0 se o elemento 1 for maior que o elemento 2;
 * - return =0 se o elemento 1 for igual ao elemento 2;
 * - return <0 se o elemento 1 for menor que o elemento 2;
 * 
 * @param element O elemento a ser adicionado.
 * @param list A lista à qual vai ser adicionado o elemento.
 * @param compare A função compare adequada ao processo.
 */
void addOrdList(void * element, LinkedList list, int (*compare)(void*,void*))
{
    if (!list->head)
    {
        list->head = createListNode(element, NULL);
        return;
    }

    LinkedNode previous = list->head;
    LinkedNode holder = list->head;
    int first = 1;

    while (compare(element, holder->element) < 0 && holder->next)
    {
        previous = holder;    
        holder = holder->next;
        first = 0;
    }

    if (!first && compare(element, holder->element) > 0)
        previous->next = createListNode(element, holder);
    else if(!first && compare(element, holder->element) < 0)
        holder->next = createListNode(element, NULL);

    if (first) list->head = createListNode(element, list->head);
}

/// @brief A função addList adiciona um elemento a uma lista.
/**
 * A função addList adiciona um elemento a uma lista
 * ligada.
 * 
 * @param element O elemento a ser adicionado.
 * @param list A lista à qual vai ser adicionado o elemento.
 */   
void addList(void * element, LinkedList list)
{
    list->head = createListNode(element, list->head);
}

/// @brief A função destroyList destroí a lista.
/**
 * A função destroyList destroí a estrutura da lista,
 * destruíndo ou não os seus elementos.
 * 
 * @param list A lista a ser destruída.
 * @param destroy A função que destroí os elementos da lista.
 */
void destroyList(LinkedList list, void (*destroy)(void*))
{
    while (list->head)
    {
        LinkedNode holder = list->head;
        list->head = holder->next;
        destroy(holder->element);
        free(holder);
    }

    free(list);
}

/// @brief A função debugPrintListNode imprime uma node.
/**
 * A função debugPrintListNode imprime uma node e os seus elementos
 * para propósitos de debugging.
 * 
 * @param node A node a ser impresa.
 * @param elemPrinter A impresora do tipo de elementos da lista.
 */
void debugPrintListNode(LinkedNode node, void (*elemPrinter)(void*))
{
    if (node)
    {
        printf("[%p](LinkedNode) {\n    (element) - ", node);
        elemPrinter(node->element);
        printf("\n    (next) - ");
        debugPrintList(node->next, elemPrinter);
        printf("}\n");
    }
    else
        printf("NULL\n");
}

/// @brief A função debugPrintList imprime uma lista.
/**
 * A função debugPrintList imprime uma lista ligada
 * para propósitos de debugging.
 * 
 * @param list A lista a ser impresa.
 * @param elemPrinter A impresora do tipo de elementos da lista.
 */
void debugPrintList(LinkedList list, void (*elemPrinter)(void*))
{
    if (list)
    {
        printf("[%p](LinkedList) {\n    (head) - ", list);
        debugPrintListNode(list->head, elemPrinter);
        printf("}\n");
    }
}

/// @brief A função listMap faz uma mudança em todos os elementos de uma Lista.
/**
 * A função listMap mapeia uma lista ligada, aplicando
 * a todos os seus elementos uma função fornecida como
 * input.
 * 
 * @param list A lista a ser mapeada.
 * @param function A função que será aplicada aos elementos da lista.
 * @param second O segundo parâmetro da função que será aplicada.
 * 
 * @return O número de operações executadas.
 */
int listMap(LinkedList list, void (*function)(void*, void*), void * second)
{
    int count = 0;

    for (LinkedNode holder = list->head; holder; holder = holder->next)
    {
        function(holder->element, second);
        count++;
    }

    return count;
}

/// @brief A função listOut cria um output de N elementos de uma lista.
/**
 * A função listOut cria um output de N elementos de uma lista,
 * colocando-o numa array de strings que serão criadas
 * de acordo com uma função fornecida como argumento.
 * 
 * @param list A lista a ser exportada.
 * @param function A função de conversão para string.
 * @param N O número de elementos a serem exportados.
 * 
 * @return O apontador do array de strings criado.
 */
char ** listOut(LinkedList list, char* (*printer)(void*), int N)
{
    char ** res = malloc(sizeof(char*) * N);

    LinkedNode holder = list->head;

    for (int i = 0; i < N && holder; i++)
    {
        res[i] = printer(holder->element);
        holder = holder->next;
    }

    return res;
}

/// @brief A função listEmpty verifica se uma lista é vazia. 
int listEmpty(LinkedList list)
{
    return list->head == NULL;
}