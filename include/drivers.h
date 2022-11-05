#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include "../include/driver.h"
#include "../include/hashmap.h"

typedef Hashmap Drivers;


Drivers * createDrivers();
void destroyDrivers(Drivers*);
void putDriver(Drivers*, Driver*);
Driver* getDriver(Drivers *, int,  int (*)(void*, void*));
Drivers *loadFromFile(char*);

#endif