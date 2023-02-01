#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#define UNORDERED 0
#define ORDERED 1

// Estrutura
typedef struct _LIST_ *List;

// Tratamentos
List createList();
void addList(void * element, List list);
void sortList(List list, int (*)(void*, void*));
void destroyList(List list, void (*)(void*), char mode);
void debugPrintList(List list, void (*)(void*));
int listMap(List list, void(*)(void*,void*), void * second);
char ** listOut(List list, char* (*)(void*), int N);

// Verificações
int listEmpty(List list);
int listOrd(List list);

#endif