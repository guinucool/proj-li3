#ifndef _BTREE_H_
#define _BTREE_H_

typedef struct _BINARY_TREE_ BinaryTree;

BinaryTree * createTree(void * data, BinaryTree * lc, BinaryTree * rc);
void destroyTree(BinaryTree * tree);

#endif