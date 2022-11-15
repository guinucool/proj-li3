#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/structs/city.h"

City * createCity(char * str, int key, char type)
{
    City * city = (City *)malloc(sizeof(City));

    city->city = (char *)malloc(sizeof(char));
    strcpy(city->city, str);
    city->key = key;
    city->type = type;

    return(city);
}

void destroyCity(City * city)
{
    free(city);
}