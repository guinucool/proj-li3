#include <stdio.h>

#include "../inc/drivers/drivers.h"
#include "../inc/drivers/driver.h"

int equal(void* key1, void* key2) {
    return *((int*) key1) == *((int*) key2);
}

int main() {

    char nameA[] = "Fernando Fonseca", nameB[] = "Joana Monteiro";
	Driver *dA = createDriver(1001, nameA);
    Driver *dB = createDriver(1002, nameB);
    Driver *d = NULL;
    Drivers *drivers = createDrivers();

    printf("Foram criados os drivers: ");
    printDriver(dA);
    printDriver(dB);


    putDriver(drivers, dA);
    putDriver(drivers, dB);

    printf("Tamanho dos drivers = %d\n", drivers->size);

    d = getDriver(drivers, 1002, equal);

    printDriver(d);


    destroyDrivers(drivers);
    destroyDriver(dA);
    destroyDriver(dB);

    return 0;
}