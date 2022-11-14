#include <stdlib.h>
#include <stdio.h>

#include "../../inc/drivers/drivers.h"
#include "../../inc/utils/hashmap.h"

Drivers * createDrivers() {
	return createHashmap();
}

void putDriver(Drivers* drivers, Driver* driver) {

	if (drivers != NULL) {
		put((Hashmap*)drivers, (void*)&driver->id, (void*)driver,hashKey_Int);
	} 
}

int compareKeys(void * keyA, void * keyB) {
	return *((int*) keyA) == *((int*) keyB);
}

Driver* getDriver(Drivers *drivers, int key) {
	return (Driver*) get((Hashmap*)drivers, (void*) &key, compareKeys,hashKey_Int);
}

void destroyDrivers(Drivers* drivers) {
	destroyHashmap(drivers);
}  

Drivers *loadFromFile(char* filename) {

	FILE *file;
	Drivers *drivers = createDrivers();
	char buffer[1024];

	if ((file = fopen(filename, "r")) == NULL) {
		return NULL;
	}

	// Discard first line (with columns headers).
	fgets(buffer, 1024, file);

	while( fgets(buffer, 1024, file) != NULL ) {
		Driver *driver = parseDriver(buffer);
		putDriver(drivers, driver);
	}

	return drivers;
}