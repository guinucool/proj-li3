#ifndef _CITY_H_
#define _CITY_H_

#define MAX_STR_NAME 50

typedef struct _CITY_
{
    char city[MAX_STR_NAME];
    int key;
    char type;
}City;

City * createCity(char * str, int key, char type);
void destroyCity(City * city);

#endif