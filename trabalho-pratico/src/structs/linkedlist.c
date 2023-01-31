#include <stdio.h>
#include <stdlib.h>

/// \struct Estrutura que define as listas de ligadas
typedef struct _LINKED_NODE_ {
    void * element;                 //!< Elemento de uma posição da lista
    struct _LINKED_NODE_ * next;    //!< Apontador para a próxima posição da lista
}*LinkedList, NPLinkedList;

/// @brief A função createList cria uma lista ligada.
/** 
 * A função createList cria uma lista ligada alocando uma posição
 * da mesma.
 * 
 * Dentro desta posição aloca insere um elemento, e anexa (ou não)
 * a continuação/o final(NULL) da lista.
 * 
 * @param element Elemento a ser guardado nesta posição da lista.
 * @param next Lista a qual esta se liga.
 * 
 * @return A nova lista criada.
 */
LinkedList createList(void * element, LinkedList next)
{
    LinkedList node = (LinkedList) malloc(sizeof(NPLinkedList));

    node->element = element;
    node->next = next;

    return node;
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
 * 
 * @return A lista com o novo elemento.
 */
LinkedList addOrdList(void * element, LinkedList list, int (*compare)(void*,void*))
{
    LinkedList holder = list;
    int first = 1;

    while (compare(element, list->element) < 0 && list->next)
    {    
        list = list->next;
        first = 0;
    }

    if (compare(element, list->element) > 0)
        list = createList(element, list);
    else if(compare(element, list->element) < 0)
        list->next = createList(element, NULL);

    if (first) holder = list;

    return holder;
}

/// @brief A função addUniqueList adiciona um elemento a uma lista sem repetições.
/**
 * A função addUniqueList adiciona um elemento a uma lista
 * averiguando que na mesma não existe já o elemento
 * que se quer adicionar.
 * 
 * @param element O elemento a ser adicionado.
 * @param list A lista à qual vai ser adicionado o elemento.
 * 
 * @return A lista com a adição caso tenha sido autorizada.
 */   
LinkedList addUniqueList(void * element, LinkedList list)
{
    int res = 0;

    for(LinkedList holder = list; holder; holder = holder->next)
        if(holder->element == element) res = 1;

    if (!res) list = createList(element, list);

    return list;
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
    while (list)
    {
        LinkedList holder = list;
        list = list->next;
        destroy(holder->element);
        free(holder);
    }
}

/// @brief A função debugPrintList imprime a lista e os seus elementos.
/**
 * A função debugPrintList imprime a lista e os seus elementos
 * para propósitos de debugging.
 * 
 * @param list A lista a ser impresa.
 * @param elemPrinter A impresora do tipo de elementos da lista.
 */
void debugPrintList(LinkedList list, void (*elemPrinter)(void*))
{
    if (list)
    {
        printf("[%p](LinkedList) {\n    (element) - ", list);
        elemPrinter(list->element);
        printf("\n    (next) - ");
        debugPrintList(list->next, elemPrinter);
        printf("}\n");
    }
    else
        printf("NULL\n");
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
 */
void listMap(LinkedList list, void (*function)(void*, void*), void * second)
{
    int count;
    for (LinkedList holder = list; holder; holder = holder->next){
        function(holder->element, second);
        count++;
    }
    return count;
}

/// @brief A função list_element devolve um elemento da lista.
/**
 * A função list_element devolve o apontador
 * do elemento da posição atual da lista.
 * 
 * @param list A lista na posição onde é pretendida a devolução.
 * 
 * @return O apontador do elemento.
 */
void * list_element(LinkedList list)
{
    return list->element;
}

/// @brief A função list_next devolve uma posição da lista.
/**
 * A função list_next devolve o apontador da próxima
 * posição da lista, relativamente à atual.
 * 
 * @param list A lista na posição onde é pretendida a devolução.
 * 
 * @return O apontador do próximo elemento.
 */
LinkedList list_next(LinkedList list)
{
    return list->next;
}