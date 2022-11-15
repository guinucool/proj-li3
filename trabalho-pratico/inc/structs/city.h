#ifndef _CITY_H_
#define _CITY_H_

typedef struct _CITY_
{
    char * city;
    int key;
    char type;
}City;

City * createCity(char * str, int key, char type);
void destroyCity(City * city);

#endif