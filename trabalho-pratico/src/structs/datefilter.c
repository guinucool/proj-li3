#include <stdlib.h>

#include "../../includes/structs/date.h"
#include "../../includes/structs/datefilter.h"

/// \struct Estrutura que define as variáveis do tipo Filtro de Data.
typedef struct _DATE_FILTER_{
    Date date;          //!< Data a ser considerada
    void* keyRef;       //!< Chave associada à data {username(user) ou id(riders && drivers)}
    char type;          //!< Tipo de data {a - birth_date(driver) ou b - account_creation(driver) ou c - date(rides) ou d - birth_date(users) ou e - account_creation(users)}
}DateFilter;

/// @brief A função createDateFilter cria uma variável do tipo DateFilter.
/**
 * A função createDateFilter cria uma variável do tipo DateFilter, alocando
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
 * @return A variável do tipo DateFilter criada e alocada.
 */ 
DateFilter * createDateFilter(Date date, void * key, char type)
{
    DateFilter* d = (DateFilter*) malloc(sizeof(DateFilter));

    d->date[0] = date[0];
    d->date[1] = date[1];
    d->date[2] = date[2];
    d->keyRef = key;
    d->type = type;
    
    return d;
}

/// @brief A função destroyDateFilter destroí uma variável do tipo DateFilter.
/**
 * A função destroyDateFilter destroí uma variável do tipo DateFilter, libertando
 * o espaço ocupado por esta e pela suas propriedades.
 * 
 * @param filter A variável DateFilter a ser destruída.
 */
void destroyDateFilter(DateFilter * filter)
{
    free(filter->keyRef);
    free(filter);
}

void filter_Date(Date dest, DateFilter * filter)
{
    dest[0] = filter->date[0];
    dest[1] = filter->date[1];
    dest[2] = filter->date[2];
}

void * filter_Key(DateFilter * filter)
{
    return(filter->keyRef);
}

char filter_Type(DateFilter * filter)
{
    return(filter->type);
}