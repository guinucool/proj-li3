#include <stdio.h>
#include <stdlib.h>

/// \struct Estrutura que define uma binary tree de void pointers.
typedef struct _BINARY_TREE7_ {
	int id;
    char* name;
    int count;
    int total;
    struct _BINARY_TREE7_ * leftChild;
    struct _BINARY_TREE7_ * rightChild;
} BinaryTree7;

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
BinaryTree7 * createTree(int id, char* name, int total, BinaryTree7 * lc, BinaryTree7 * rc){

    BinaryTree7 * tree = (BinaryTree7*) malloc(sizeof(BinaryTree7));

    tree->id = id;
    tree->name = name;
    tree->count = 1;
    tree->total = total;
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
void destroyTree(BinaryTree7 * tree)
{
    if(tree->leftChild != NULL)destroyTree(tree->leftChild);
    if(tree->rightChild != NULL)destroyTree(tree->rightChild);
    free(tree);
}

/// @brief Esta função procura pelo local da arvore binaria onde o id do driver esta.
/**
 * Esta função procura pelo local da arvore binaria onde o id do driver esta e caso não
 * exista retorna o local onde deve ser inserido. Usando um algoritmo basico de procura
 * a função percorre a arvore comoparando o id dado com o id de cada data[0].
 * 
 * @param tree Arvore bínaria onde pretendemos procurar
 * 
 * @param id Id que pretendemos encontrar
 * 
 * @return returna a tree onde se encontra o Id ou onde este deve ser adicionado
*/
BinaryTree7 * insertTreeOrd_7(BinaryTree7 * tree, int id){
    while (tree != NULL)
    {
        int driverId = tree->id;

        if(id < driverId)tree = tree->leftChild;
        else if(id > driverId)tree = tree->rightChild;
        else return tree;
    }
    return tree;
    
}

void maxN(BinaryTree7 * tree, int N, BinaryTree7* max[N],int * tree_mutex)
{
    while (__sync_lock_test_and_set(tree_mutex, 1));
    BinaryTree7* auxTree;
    double avMed = 0.f, avMedAux = 0.f;

    if(tree != NULL){
        int id = tree->id;
        int count = tree->count;
        int total = tree->count;
        int i;
        avMed = (double)(total/count);
        auxTree = max[N-1];
        avMedAux = (double)(auxTree->total/auxTree->count);
        if(avMed < avMedAux)return;
        for (i = 0; i < N; i++){
            if(max[i] != NULL){
                auxTree = max[i];
                avMedAux = (double)(auxTree->total/auxTree->count);
                if(avMed == avMedAux){
                    if(tree->id > auxTree->id)break;
                }
                if(avMed > avMedAux)break;
            }else break;
        }
        for (int j = N-1; j > i; j--)
        {
            max[j] = max[j-1];
        }
        max[i] = tree;
        __sync_lock_release(tree_mutex);
        maxN(tree->leftChild,N,max,tree_mutex);
        maxN(tree->rightChild,N,max,tree_mutex);
    }else{
        __sync_lock_release(tree_mutex);
        return;
    }
}

void incrementCount(BinaryTree7 * tree){
    tree->id++;
}

void addScore(BinaryTree7 * tree, int score){
    tree->total += score;
}

int bTree_id(BinaryTree7 * tree){
    return tree->id;
}

char * bTree_name(BinaryTree7 * tree){
    return tree->name;
}

int bTree_count(BinaryTree7 * tree){
    return tree->count;
}

int bTree_total(BinaryTree7 * tree){
    return tree->total;
}

BinaryTree7 * bTree_left(BinaryTree7 * tree){
    return tree->leftChild;
}

BinaryTree7 * bTree_right(BinaryTree7 * tree){
    return tree->rightChild;
}
