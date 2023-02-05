#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#define UNORDERED 0
#define ORDERED 1

#define PAGES 10

// Estrutura
typedef struct _LIST_ *List;

// Tratamentos
List createList();
int addList(void * element, List list);
void sortList(List list, int (*)(void*, void*, void*), void * second);
void destroyList(List list, void (*)(void*), char mode);
void debugPrintList(List list, void (*)(void*));
int listMap(List list, void(*)(void*,void*), void * second);
void listOut(List list, void (*)(void*,void*,int*,FILE*), int pos, int N, void * second, FILE * file);

// Verificações
int listEmpty(List list);

// Devoluções
int list_size(List list);

#endif