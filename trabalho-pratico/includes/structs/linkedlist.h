#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

// Estrutura
typedef struct _LINKED_NODE_ *LinkedList;

// Tratamentos
LinkedList createList(void * element, LinkedList next);
LinkedList addOrdList(void * element, LinkedList list, int (*)(void*, void*));
int check_element(LinkedList list, void * elem);
void destroyList(LinkedList list);
void debugPrintList(LinkedList list, void (*)(void*));

// Devoluções
void * list_element(LinkedList list);
LinkedList list_next(LinkedList list);

#endif