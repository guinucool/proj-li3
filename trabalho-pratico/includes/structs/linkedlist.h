#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

// Estrutura
typedef struct _LINKED_LIST_ *LinkedList;

// Tratamentos
LinkedList createList();
void addOrdList(void * element, LinkedList list, int (*)(void*, void*));
void addList(void * element, LinkedList list);
void destroyList(LinkedList list, void (*)(void*));
void debugPrintList(LinkedList list, void (*)(void*));
int listMap(LinkedList list, void(*)(void*,void*), void * second);
char ** listOut(LinkedList list, char* (*)(void*), int N);
int listEmpty(LinkedList list);

#endif