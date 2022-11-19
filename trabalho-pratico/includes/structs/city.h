#ifndef _CITY_H_
#define _CITY_H_

#define MAX_STR_NAME 50

/// \struct Estrutura que define as variáveis do tipo cidade.
typedef struct _CITY_
{
    char city[MAX_STR_NAME];    //!< Nome (string) da cidade
    int key;                    //!< Id do elemento (ride/driver) que contém esta cidade
    char type;                  //!< Tipo da key (ride/driver)
}City;

City * createCity(char * str, int key, char type);
void destroyCity(City * city);

#endif