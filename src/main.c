#include <stdio.h>

#include "../include/Drivers.h";
#include "../include/Driver.h";



int main() {

	Drivers * drivers = NULL;
	char name[] = "Fernando Fonseca";

	Driver *dA = createDriver(1001, name);


	drivers = createDrivers();

	putDriver(&drivers, &dA->id, dA);


	return 0;
}