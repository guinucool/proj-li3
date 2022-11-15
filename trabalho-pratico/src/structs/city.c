#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/city.h"

/// @brief A função createCity cria uma variável do tipo city.
/**
 * A função createCity cria uma variável do tipo city, alocando
 * o espaço necessário para a mesma na memória.
 * 
 * De seguida, irá associar a cada propriedade deste tipo
 * de variável um valor do input da função.
 * 
 * @param cty O nome da cidade da city.
 * 
 * @param key O id de driver/ride da city.
 * 
 * @param type O tipo de id fornecido na propriedade anterior.
 * 
 * @return A variável do tipo city criada e alocada.
 */ 
City * createCity(char * cty, int key, char type)
{
    City * city = (City *)malloc(sizeof(City));

    strncpy(city->city, cty, MAX_STR_NAME);
    city->key = key;
    city->type = type;

    return(city);
}

/// @brief A função destroyCity destroí uma variável do tipo city.
/**
 * A função destroyCity destroí uma variável do tipo city, libertando
 * o espaço ocupado por esta e pela suas propriedades.
 * 
 * @param city A variável city a ser destruída.
 */
void destroyCity(City * city)
{
    free(city);
}