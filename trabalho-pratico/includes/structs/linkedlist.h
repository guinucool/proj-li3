#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

// Estrutura
typedef struct _LINKED_NODE_ *LinkedList;

// Tratamentos
LinkedList createList(void * element, LinkedList next);
LinkedList addOrdList(void * element, LinkedList list, int (*)(void*, void*));
LinkedList addUniqueList(void * element, LinkedList list);
void destroyList(LinkedList list, void (*)(void*));
void debugPrintList(LinkedList list, void (*)(void*));
void listMap(LinkedList list, void(*)(void*));

// Devoluções
void * list_element(LinkedList list);
LinkedList list_next(LinkedList list);

#endif