#ifndef _CITY_H_
#define _CITY_H_

typedef struct _CITY_
{
    char * city;
    void * key;
    char type;
}City;

City * createCity(char * str, void * key, char type);
void destroyCity(City * city);

#endif