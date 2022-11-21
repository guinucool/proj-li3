#ifndef _CITY_H_
#define _CITY_H_

#define MAX_STR_NAME 50

typedef struct _CITY_ City;

City * createCity(char * str, int key, char type);
void destroyCity(City * city);
void city_City(char * dest, City * city);
int city_Key(City * city);
char city_Char(City * city);

#endif