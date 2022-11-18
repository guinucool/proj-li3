#include <stdlib.h>

#include "../../includes/structs/date.h"

/// @brief A função createDate cria uma variável do tipo Date.
/**
 * A função createDate cria uma variável do tipo Date, alocando
 * o espaço necessário para a mesma na memória.
 * 
 * De seguida, irá associar a cada propriedade deste tipo
 * de variável um valor do input da função.
 * 
 * @param date O array de shorts com a data.
 * 
 * @param key A chave a qual a data esta associada.
 * 
 * @param type O tipo de id fornecido na propriedade anterior.
 * 
 * @return A variável do tipo Date criada e alocada.
 */ 
Date * createDate(short * date, void * key, char type)
{
    Date* d = (Date*) malloc(sizeof(Date));

    d->date[0] = date[0];
    d->date[1] = date[1];
    d->date[2] = date[2];
    d->keyRef = key;
    d->type = type;
    
    return d;
}

/// @brief A função destroyDate destroí uma variável do tipo Date.
/**
 * A função destroyDate destroí uma variável do tipo Date, libertando
 * o espaço ocupado por esta e pela suas propriedades.
 * 
 * @param date A variável Date a ser destruída.
 */
void destroyDate(Date * date)
{
    free(date);
}