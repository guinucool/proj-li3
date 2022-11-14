#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/city.h"

City * createCity(char * str, void * key, char type)
{
    City * city = (City *)malloc(sizeof(City));

    strcpy(city->city, str);
    city->key = key;
    city->type = type;

    return(city);
}

void destroyCity(City * city)
{
    free(city);
}