#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../inc/drivers/driver.h"

Driver *createDriver(int id, char *name) {
	
	Driver *driver = (Driver*) malloc(sizeof(Driver));

	driver->id = id;
	strncpy(driver->name, name, MAX_NAME_STR);

	return driver;

}

void destroyDriver(Driver *driver) {
	free(driver);
}

void printDriver(Driver* driver) {
	printf("Driver {id: %d, name: %s}", driver->id, driver->name);
}