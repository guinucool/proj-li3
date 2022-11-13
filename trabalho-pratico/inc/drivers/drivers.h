#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include "../../inc/drivers/driver.h"
#include "../../inc/utils/hashmap.h"

typedef Hashmap Drivers;

Drivers * createDrivers();
void destroyDrivers(Drivers*);
void putDriver(Drivers*, Driver*);
Driver* getDriver(Drivers *, int);
Drivers *loadFromFile(char*);
int compareKeys(void*, void*);

#endif