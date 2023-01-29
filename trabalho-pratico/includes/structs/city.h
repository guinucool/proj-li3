#ifndef _CITY_H_
#define _CITY_H_

#define MAX_STR_NAME 50

// Estrutura
typedef struct _CITY_ *City;

// Tratamentos
City createCity(char * name, double money_spent, void * driver);
void updateCity(City city, double money_spent, void * driver);
void destroyCity(City city);
void debugPrintCity(City city, void (*elemPrinter)(void*));

// Devoluções
double city_averageMoney(City city);
void * city_drivers(City city);

#endif