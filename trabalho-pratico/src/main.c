#include <stdio.h>

#include "../inc/drivers/drivers.h";
#include "../inc/drivers/driver.h";



int main() {

	Drivers * drivers = NULL; // estrutura de drivers
	char name[] = "Fernando Fonseca";

	Driver *dA = createDriver(1001, name); 


	drivers = createDrivers();

	putDriver(&drivers, &dA->id, dA);


	return 0;
}