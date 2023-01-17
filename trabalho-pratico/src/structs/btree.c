#include <stdio.h>
#include <stdlib.h>

/// \struct Estrutura que define uma arvore usada na querie 7
typedef struct _BINARY_TREE7_ {
	int id;
    char* name;
    int count;
    int total;
    struct _BINARY_TREE7_ * leftChild;
    struct _BINARY_TREE7_ * rightChild;
} BinaryTree7;

/// @brief A função createTree cria uma arvore.
/**
 * A função createTree cria uma arvore binaria, alocando
 * a memória necessária a sua criação.
 * 
 * Uma vez alocada a memória, associa os inputs da função às
 * propriedades da node criada.
 * 
 * @param tree Localização onde a nova arvore será adicionada;
 * 
 * @param id Id do Driver a ser adicionado.
 * 
 * @param name Nome do Driver a ser adicionado.
 * 
 * @param total Score que o Driver teve numa ride que vai ser adicionado.
 * 
 * @param lc A left child da data.
 * 
 * @param rc A right child da data.
 */ 
void createTree(BinaryTree7* tree,int id, char* name, int total, BinaryTree7 * lc, BinaryTree7 * rc){

    BinaryTree7 * newTree = (BinaryTree7*) malloc(sizeof(BinaryTree7));

    newTree->id = id;
    newTree->name = name;
    newTree->count = 1;
    newTree->total = total;
    newTree->leftChild = lc;
    newTree->rightChild = rc;

    tree = newTree;
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

/// @brief Esta função insere no array nodos da arvore que têm maior avaliação media
/**
 *  Esta função insere no array nodos da arvore que têm maior avaliação media
 *  percorrendo a arvore contendo todos os drivers e seus respetivos scores totais 
 *  e numero de viagens realizadas. Com esta informação é realizada a avaliação media 
 *  e caso o resultado seja maior que a valiação media de algum elemento do array é 
 *  adicionado de maneira ordenada.
 * 
 *  Ao percorrer a arvore é feito um mecanismo de semaforo para que não haja conflitos
 *  ao verificar qual dos drivers tem maior avaliação media 
 * 
 *  @param tree Arvore que será percorrida.
 * 
 *  @param N Tamanho do array.
 * 
 *  @param max Array de nodos de arvore.
 * 
 *  @param tree_mutex Localização do integer auxiliar ao semaforo.
*/ 
void maxN(BinaryTree7 * tree, int N, BinaryTree7* max[N],int * tree_mutex)
{
    // Semaforo a vermelho ate que seja a vez de processar a informação
    while (__sync_lock_test_and_set(tree_mutex, 1));

    // Inicialização de variaveis que serão usadas
    BinaryTree7* auxTree;
    double avMed = 0.f, avMedAux = 0.f;

    if(tree != NULL){
        // Estração da informação da arvore necessaria 
        int id = tree->id;
        int count = tree->count;
        int total = tree->count;
        int i;

        // Calculo das medias a serem comparadas
        avMed = (double)(total/count);
        auxTree = max[N-1];
        avMedAux = (double)(auxTree->total/auxTree->count);
        
        // Verificar se é menor que o ultimo elemento 
        if(avMed < avMedAux)return;

        // Localização do indice onde deverá ser adicionado o nodo da arvore
        for (i = 0; i < N; i++){
            // Se ainda existir espaço vazio é adicionado no primeiro espaço vazio
            if(max[i] != NULL){
                // Aquisição da avaliação media do elemento do array a comparar
                auxTree = max[i];
                avMedAux = (double)(auxTree->total/auxTree->count);

                // Em caso de empate fica com a posição o maior id, senão passa para a proxima
                if(avMed == avMedAux){
                    if(tree->id > auxTree->id)break;
                    else{i++;break;}
                }
                // Se a avaliação media for maior que a da posição atual encontramos a posição de inserção
                if(avMed > avMedAux)break;
            }else break;
        }

        // Empurrar todos os elementos ate ao i uma posição para a direita 
        for (int j = N-1; j > i; j--)
        {
            max[j] = max[j-1];
        }

        // Adição do nodo da arvore ao array
        max[i] = tree;

        // Liberação para outros nodos serem processados e processamento dos filhos deste nodo
        __sync_lock_release(tree_mutex);
        maxN(tree->leftChild,N,max,tree_mutex);
        maxN(tree->rightChild,N,max,tree_mutex);
    }else{
        // Liberação para outros nodos caso a arvore seja NULL 
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
