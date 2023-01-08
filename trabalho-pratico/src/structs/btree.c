#include <stdio.h>
#include <stdlib.h>

/// \struct Estrutura que define uma binary tree de void pointers.
typedef struct _BINARY_TREE_ {
	void * data;
    struct _BINARY_TREE_ * leftChild;
    struct _BINARY_TREE_ * rightChild;
} BinaryTree;

/// @brief A função createTree cria uma arvore binaria.
/**
 * A função createTree cria uma arvore binaria, alocando
 * a memória necessária a sua criação.
 * 
 * Uma vez alocada a memória, associa os inputs da função às
 * propriedades da node criada.
 * 
 * @param data O void pointer da informação que será guardada na tree.
 * 
 * @param lc A left child da data.
 * 
 * @param rc A right child da data.
 * 
 * @return A tree criada e alocada.
 */ 
BinaryTree * createTree(void * data, BinaryTree * lc, BinaryTree * rc){

    BinaryTree * tree = (BinaryTree*) malloc(sizeof(BinaryTree));

    tree->data = data;
    tree->leftChild = lc;
    tree->rightChild = rc;
}

/// @brief A função destroyTree destroí uma arvore binaria.
/**
 * A função destroyTree destroí uma arvore binaria,
 * libertando o espaço ocupado por esta na memória.
 * 
 * Desta forma, irá também destruir todas as Trees que estão,
 * posteriormente, ligadas a esta.
 * 
 * @param tree A Tree a ser destruída.
 * 
 */ 
void destroyTree(BinaryTree * tree)
{
    if(tree->leftChild != NULL)destroyTree(tree->leftChild);
    if(tree->rightChild != NULL)destroyTree(tree->rightChild);
    free(tree);
}

int procuraTreeOrd(BinaryTree* tree, int x){
    int data = tree->data;
    if(tree->data == x)
}