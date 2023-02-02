#include <stdio.h>
#include <stdlib.h>
#include "../../includes/structs/list.h"

/// \struct Estrutura que define as listas
typedef struct _LIST_ {
    void ** list;               //!< Apontador para o array das listas
    int size;                   //!< Tamanho do array das listas
    char ord;                   //!< Define se a lista está ou não ordenada
}*List, NPList;

/// @brief A função createList cria uma lista.
/** 
 * A função createList cria uma lista alocando o espaço
 * necessário para mesma e para as suas propriedades.
 * 
 * @return A nova lista criada.
 */
List createList()
{
    List list = (List) malloc(sizeof(NPList));

    list->list = malloc(sizeof(void*));
    list->size = 0;
    list->ord = UNORDERED;

    return list;
}

/// @brief A função addList adiciona um elemento a uma lista.
/**
 * A função addList adiciona um elemento ao fim de uma lista,
 * alocando o espaço necessário ao mesmo.
 * 
 * @param element O elemento a ser adicionado.
 * @param list A lista à qual vai ser adicionado o elemento.
 */   
void addList(void * element, List list)
{
    list->ord = UNORDERED;
    list->size++;

    if (list->size > 1) list->list = realloc(list->list, list->size * sizeof(void*));

    list->list[list->size-1] = element;
}

/// @brief A função swap troca a posição de dois elementos de uma lista.
void swap(int a, int b, void ** array)
{
    void * holder = array[a];
    array[a] = array[b];
    array[b] = holder;
}

/// @brief A função partition irá partir uma lista de forma ordenada.
/**
 * A função partition irá partir uma lista em dois, colocando todos
 * os elementos maiores do que um pivot de um lado da lista (a primeira
 * metade) e todos os elementos menores do outro lado da lista
 * (a segunda metade).
 * 
 * @param array A lista a ser partida.
 * @param bottom A posição do primeiro elemento da lista a ser partida.
 * @param top A posição do último elemento da lista a ser partida.
 * @param compare A função de comparação de elementos.
 * 
 * @return A posição que divide as partes da lista.
 */
int partition(void ** array, int bottom, int top, int (*compare)(void*,void*))
{
    void * pivot = array[top];
    int j = (bottom - 1);

    for (int i = bottom; i < top; i++)
    {
        if (compare(array[i], pivot) > 0)
        {
            j++;
            swap(i, j, array);
        }
    }

    j++;
    swap(j, top, array);

    return j;
}

/// @brief A função quickSort irá ordernar (por ordem decrescente) uma lista.
/**
 * A função quickSort irá ordernar (por ordem decrescente) uma lista, dividindo
 * sucessivamente as lista em duas partes (usando a partition) até que a lista fique
 * ordenada.
 * 
 * @param array A lista a ser ordenada.
 * @param bottom A posição de origem da parte da lista.
 * @param top A posição do topo da parte da lista.
 * @param compare A função de comparação de elementos da lista.
 */
void quickSort(void ** array, int bottom, int top, int (*compare)(void*,void*))
{
    if (bottom < top)
    {
        int index = partition(array, bottom, top, compare);

        quickSort(array, bottom, index - 1, compare);
        quickSort(array, index + 1, top, compare);
    }
}

/// @brief A função sortList ordena uma lista.
/**
 * A função sortList ordena uma lista por ordem decrescente
 * usando o algoritmo de quickSort.
 * 
 * @param list A lista a ser ordenada.
 * @param compare A função de comparação de elementos da lista.
 */
void sortList(List list, int (*compare)(void*,void*))
{
    if (list->ord == UNORDERED)
    {
        quickSort(list->list, 0, (list->size - 1), compare);
        list->ord = ORDERED;
    }
}

/// @brief A função destroyList destroí a lista.
/**
 * A função destroyList destroí a estrutura da lista,
 * destruíndo ou não os seus elementos.
 * 
 * @param list A lista a ser destruída.
 * @param destroy A função que destroí os elementos da lista.
 */
void destroyList(List list, void (*destroy)(void*), char mode)
{
    if (list)
    {
        for (int i = 0; i < list->size && mode; i++)
        destroy(list->list[i]);

        free(list->list);
        free(list);
    }
}

/// @brief A função debugPrintList imprime uma lista.
/**
 * A função debugPrintListNode imprime uma lista e todos
 * os seus elementos para propósitos de debugging.
 * 
 * @param list A lista a ser impressa.
 * @param elemPrinter A impresora do tipo de elementos da lista.
 */
void debugPrintList(List list, void (*elemPrinter)(void*))
{
    printf("[%p](List) {\n    ord: %d\n    size: %d\n    elements: \n",
        list,
        list->ord,
        list->size
    );
    for (int i = 0; i < list->size; i++)
    {
        printf("    [%p](%d): ", list->list[i], i);
        elemPrinter(list->list[i]);
        printf("\n");
    }
    printf("}\n");
}

/// @brief A função listMap faz uma mudança em todos os elementos de uma Lista.
/**
 * A função listMap mapeia uma lista, aplicando a todos os seus
 * elementos uma função fornecida como input.
 * 
 * @param list A lista a ser mapeada.
 * @param function A função que será aplicada aos elementos da lista.
 * @param second O segundo parâmetro da função que será aplicada.
 * 
 * @return O número de operações executadas.
 */
int listMap(List list, void (*function)(void*, void*), void * second)
{
    for (int i = 0; i < list->size; i++)
        function(list->list[i], second);

    return list->size;
}

/// @brief[OUTDATED] A função listOut cria um output de N elementos de uma lista.
/**
 * A função listOut cria um output de N elementos de uma lista,
 * colocando-o numa array de strings que serão criadas
 * de acordo com uma função fornecida como argumento.
 * 
 * @param list A lista a ser exportada.
 * @param function A função de conversão para string.
 * @param N O número de elementos a serem exportados.
 * @param second O segundo parâmetro da função de conversão.
 * 
 * @return O apontador do array de strings criado.
 */
void listOut(List list, void (*printer)(void*,void*,int*,FILE*), int pos, int N, void * second, FILE * file)
{
    int pag = PAGES;

    if (list->size == 0) return NULL;

    if (N > list->size) N = list->size;
    
    if (pos == 0) pag = N;
    pos--;

    if (pos * PAGES > N) pos -= ((pos * PAGES) - N) / PAGES;
    if (pos * PAGES == N) pos--;

    int ignore = pos * PAGES;

    for (int i = 0; i < N && i < list->size && pag > 0; i++)
    {
        if (ignore <= 0) pag--;
        printer(list->list[i], second, &ignore, file);
    }
}

/// @brief A função listEmpty verifica se uma lista é vazia. 
int listEmpty(List list)
{
    return list->size == 0;
}