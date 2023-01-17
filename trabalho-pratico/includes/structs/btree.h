#ifndef _BTREE_H_
#define _BTREE_H_

typedef struct _BINARY_TREE7_ BinaryTree7;

void createTree(BinaryTree7* tree,int id, char* name, int total, BinaryTree7 * lc, BinaryTree7 * rc);
void destroyTree(BinaryTree7 * tree);
BinaryTree7 * insertTreeOrd_7(BinaryTree7 * tree, int id);
void incrementCount(BinaryTree7 * tree);
void addScore(BinaryTree7 * tree, int score);
void maxN(BinaryTree7 * tree, int N, BinaryTree7* max[N],int * tree_mutex);
int bTree_id(BinaryTree7 * tree);
char * bTree_name(BinaryTree7 * tree);
int bTree_count(BinaryTree7 * tree);
int bTree_total(BinaryTree7 * tree);
BinaryTree7 * bTree_left(BinaryTree7 * tree);
BinaryTree7 * bTree_right(BinaryTree7 * tree);

#endif