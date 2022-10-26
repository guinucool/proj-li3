#include <stdlib.h>

#include "../include/drivers.h"
#include "../include/hashmap.h"


Drivers * createDrivers() {
	return createHashmap();
}

void putDriver(Drivers* drivers, Driver* driver) {

	if (drivers != NULL) {

		put((Hashmap*)drivers, (void*)&driver->id, (void*)driver);

	} 

}

Driver* getDriver(Drivers *drivers, int key,  int (*equal)(void*, void*)) {
	return (Driver*) get((Hashmap*)drivers, (void*) &key, equal);
}

void destroyDrivers(Drivers* drivers) {
	destroyHashmap(drivers);
}  

Drivers *loadFromFile(char* filename) {

	// TODO:

	return NULL;
}